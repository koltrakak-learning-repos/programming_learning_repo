#pragma once
#include <string>

// Ogni plugin deve esportare una funzione con questo nome esatto.
// Il dynamic linker la trova via dlsym().
#define PLUGIN_ENTRY_POINT "getPluginInfo"

// Struttura dati che ogni plugin restituisce al momento della registrazione.
// Simile a llvm::PassPluginLibraryInfo.
struct PluginInfo {
  const char *name;    // nome del plugin, es. "upper"
  const char *version; // versione, es. "1.0"

  // La funzione che il plugin vuole registrare.
  // Riceve una stringa, restituisce una stringa trasformata.
  std::string (*transform)(const std::string &input);
};

// Tipo della funzione entry point che ogni .so deve esportare.
// extern "C" evita il name mangling del C++ — fondamentale per dlsym().
using GetPluginInfoFn = PluginInfo (*)();
