#ifndef CFG_PARSER_HPP
#define CFG_PARSER_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * This class parses the configuration files within our Assets folder
 */
class ConfigParser {
 public:
  /** Puts the list of all level paths into the give list */
  static void ParseLevelPaths(/** The list of level paths to be filled */
                              std::vector<std::string>& levelPaths);

  /**
   * Gets the map of localization texts and keys from the given locale
   * @return The map of localization texts and keys
   */
  static std::unordered_map<std::string, std::string>
  ParseLocale(/** The name of the locale */
              std::string locale);

  /** 
   *  The name of the file that holds the list of level names 
   */
  static std::string LEVELS_PATH;

  /**
   * Gets the default localization from the default locale file
   * @return The default localization language
   */
  static std::string DefaultLocale();
};

#endif
