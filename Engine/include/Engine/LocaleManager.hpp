#ifndef LOCALE_MANAGER_HPP
#define LOCALE_MANAGER_HPP

#include <string>
#include <unordered_map>

/**
 * This class manages the localization of our game as a
 * singleton.
 */
class LocaleManager {
 public:
  /** The singleton instance of the LocaleManager */
  static LocaleManager& instance();

  /**
   * Looks up the given key in the translation map
   * @return The value of the given key
   */
  static std::string Lookup(/** The key to be looked up */
                            const std::string& key);

  /** Stop the compiler from generating methods to copy the object */
  LocaleManager(const LocaleManager&) = delete;

  /** Stop the compiler from generating methods to copy the object */
  LocaleManager& operator=(const LocaleManager&) = delete;

 private:
  /** Constructs a LocaleManager */
  LocaleManager(/** The localization language */
                const std::string& locale);

  /** Destructs a LocaleManager */
  ~LocaleManager();

  /** The translation key map */
  std::unordered_map<std::string, std::string> strings_;
};

#endif
