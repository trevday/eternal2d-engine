#ifndef PYTHON_MANAGER_HPP
#define PYTHON_MANAGER_HPP

/**
 * This class manages the python scripts of our game as a singleton.
 */
class PythonManager {
 public:
  /** The singleton instance of the PythonManager */
  static PythonManager& instance();

  /** Initializes the python manager */
  void init();

  /** Shuts down the python manager */
  void shutdown();

  /** Stop the compiler from generating methods to copy the object */
  PythonManager(const PythonManager&) = delete;

  /** Stop the compiler from generating methods to copy the object */
  PythonManager& operator=(const PythonManager&) = delete;

 private:
  /** Constructs a PythonManager */
  PythonManager();

  /** Destructs a PythonManager */
  ~PythonManager();
};

#endif