#include "LocaleManager.hpp"

#include "ConfigParser.hpp"

LocaleManager& LocaleManager::instance() {
  static LocaleManager inst(ConfigParser::DefaultLocale());
  return inst;
}

LocaleManager::LocaleManager(const std::string& locale)
    : strings_(ConfigParser::ParseLocale(locale)){};
LocaleManager::~LocaleManager() {}

std::string LocaleManager::Lookup(const std::string& key) {
  if (instance().strings_.count(key) > 0) {
    return instance().strings_[key];
  } else {
    return "Missing translation: " + key;
  }
}