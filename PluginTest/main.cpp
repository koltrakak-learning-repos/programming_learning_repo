#include "plugin_api.h"
#include <dlfcn.h> // dlopen, dlsym, dlclose
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// ─── Registry globale ───────────────────────────────────────────────────────
// Mappa nome-plugin → PluginInfo.
// Ogni plugin, al caricamento, si registra qui.
// Analogo al meccanismo di LLVM con
// PassBuilder::registerPipelineParsingCallback.
struct PluginRegistry {
  std::unordered_map<std::string, PluginInfo> plugins;
  std::vector<void *> handles; // tenere i handle aperti finché servono

  void registerPlugin(const PluginInfo &info) {
    std::cout << "[registry] registrato plugin: " << info.name << " v"
              << info.version << "\n";
    plugins[info.name] = info;
  }

  // Carica un .so, chiama il suo entry point, registra il plugin.
  bool load(const std::string &path) {
    // RTLD_LAZY: risolve i simboli solo quando vengono chiamati.
    // RTLD_LOCAL: i simboli del .so non inquinano il namespace globale.
    void *handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
    if (!handle) {
      std::cerr << "[host] errore dlopen: " << dlerror() << "\n";
      return false;
    }

    // A questo punto ho caricato la libreria dinamica in memoria. Se conoscessi
    // l'indirizzo delle funzioni al suo interno potrei invocarle

    // dlsym cerca un simbolo per nome. In questo caso cerchiamo il simbolo
    // relativo alla funzione che ci permette di ottenere le informazioni del
    // plugin (la struct PluginInfo).
    //
    // dlsym() restituisce un void* che convertiamo al tipo function pointer
    // appropriato (non so perchè c++ deve avere mille varianti di cast)
    auto *fn =
        reinterpret_cast<GetPluginInfoFn>(dlsym(handle, PLUGIN_ENTRY_POINT));

    if (!fn) {
      std::cerr << "[host] simbolo '" << PLUGIN_ENTRY_POINT
                << "' non trovato: " << dlerror() << "\n";
      dlclose(handle);
      return false;
    }

    // Chiama l'entry point: il plugin si auto-descrive.
    PluginInfo info = fn();
    registerPlugin(info);
    // salvo la handle al .so aperto in modo da poterlo chiudere in futuro
    // (distruttore)
    handles.push_back(handle);
    return true;
  }

  ~PluginRegistry() {
    for (void *h : handles)
      dlclose(h);
  }
};

// ─── main ────────────────────────────────────────────────────────────────────

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "uso: " << argv[0]
              << " <plugin.so> [<plugin2.so> ...] -- <testo>\n"
              << "     i plugin vengono applicati in ordine\n";
    return 1;
  }

  // Separa i .so dall'input testuale (separatore "--")
  std::vector<std::string> pluginPaths;
  std::string inputText;
  bool separator = false;
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "--") {
      separator = true;
      continue;
    }
    if (!separator)
      pluginPaths.push_back(argv[i]);
    else
      inputText = argv[i];
  }

  if (!separator || inputText.empty()) {
    std::cerr << "errore: manca il separatore -- o il testo\n";
    return 1;
  }

  PluginRegistry registry;

  std::cout << "\n── caricamento plugin ──────────────────────\n";
  for (const auto &path : pluginPaths) {
    std::cout << "[host] carico: " << path << "\n";
    if (!registry.load(path))
      return 1;
  }

  std::cout << "\n── applicazione pipeline ───────────────────\n";
  std::cout << "input:  \"" << inputText << "\"\n";

  std::string result = inputText;

  // Scorro i plugin nell'ordine di registrazione (ordine di caricamento)
  for (const auto &path : pluginPaths) {
    // gang, this is a map why are you iterating? use the key

    // Recupera il nome dal path: ./plugin_upper.so → cerca "upper"
    for (auto &[name, info] : registry.plugins) {
      // Controlla se il path contiene il nome del plugin
      if (path.find(name) != std::string::npos) {
        // applico la trasformazione del plugin
        result = info.transform(result);
        std::cout << "dopo [" << name << "]: \"" << result << "\"\n";
        break;
      }
    }
  }

  std::cout << "\nrisultato finale: \"" << result << "\"\n";
  return 0;
}
