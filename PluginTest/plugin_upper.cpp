#include "./plugin_api.h"
#include <algorithm>
#include <cctype>
#include <string>

// La trasformazione concreta del plugin
static std::string toUpper(const std::string &input) {
  std::string out = input;
  std::transform(out.begin(), out.end(), out.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return out;
}

// extern "C" è FONDAMENTALE:
//   senza di esso g++ rinomina la funzione con il name mangling C++
//   (qualcosa come _Z13getPluginInfov) e dlsym("getPluginInfo") fallisce.
extern "C" PluginInfo getPluginInfo() {
  return PluginInfo{
      .name = "upper",
      .version = "1.0",
      .transform = toUpper,
  };
}
