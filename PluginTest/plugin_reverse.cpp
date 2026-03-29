#include "./plugin_api.h"
#include <string>

static std::string reverseStr(const std::string &input) {
  return std::string(input.rbegin(), input.rend());
}

extern "C" PluginInfo getPluginInfo() {
  return PluginInfo{
      .name = "reverse",
      .version = "1.0",
      .transform = reverseStr,
  };
}
