#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "FilePaths.hpp"

/** Represents an object within a level. */
class LevelObject {
 public:
 /** The name of this level object. */
  std::string name;
  /** The x coordinate of this level object. */
  int x;
  /** The y coordinate of this level object. */
  int y;
  /** The width of this level object. */
  int w;
  /** The height of this level object. */
  int h;
  /** Whether or not this object is permanent */
  bool permanent;
  /** The name of the script attached to this level object. */
  std::string scriptName;
  /** The class of the script attached to this level object. */
  std::string className;
  /** The sprite attached to this level object. */
  std::string spriteName;
};

void LevelExport(const std::string path, const std::vector<LevelObject>& objs) {
  std::ofstream lvlFile(path,
                        std::ios::out | std::ios::trunc | std::ios::binary);
  if (!lvlFile.is_open()) {
    std::cout << "Failed to save level to " << path << std::endl;
    return;
  }

  int numObjs = objs.size();
  lvlFile.write((char*)&numObjs, sizeof(int));

  for (auto it = objs.begin(); it != objs.end(); it++) {
    // save name
    int nameLength = it->name.length() + 1;  //+1 for null terminator
    lvlFile.write((char*)&nameLength, sizeof(int));
    lvlFile.write(it->name.c_str(), nameLength);
    // save data
    lvlFile.write((char*)&it->x, sizeof(int));
    lvlFile.write((char*)&it->y, sizeof(int));
    lvlFile.write((char*)&it->w, sizeof(int));
    lvlFile.write((char*)&it->h, sizeof(int));
    lvlFile.write((char*)&it->permanent, sizeof(bool));
    // save script
    int scriptNameLength = it->scriptName.length() + 1;
    lvlFile.write((char*)&scriptNameLength, sizeof(int));
    lvlFile.write(it->scriptName.c_str(), scriptNameLength);
    int classNameLength = it->className.length() + 1;
    lvlFile.write((char*)&classNameLength, sizeof(int));
    lvlFile.write(it->className.c_str(), classNameLength);
    // save sprite
    int spriteNameLength = it->spriteName.length() + 1;
    lvlFile.write((char*)&spriteNameLength, sizeof(int));
    lvlFile.write(it->spriteName.c_str(), spriteNameLength);
  }
  lvlFile.close();
  std::cout << "Saved " << numObjs << " GameObjects to " << path << std::endl;
}

std::vector<LevelObject> LevelImport(const std::string path) {
  std::ifstream lvlFile(path, std::ios::in | std::ios::binary);

  std::vector<LevelObject> objs;
  if (!lvlFile.is_open()) {
    std::cout << "Could not load " << path << std::endl;
    return objs;
  }

  int numObjs;
  lvlFile.read((char*)&numObjs, sizeof(int));

  for (int i = 0; i < numObjs; i++) {
    LevelObject o;

    int nameLength;
    lvlFile.read((char*)&nameLength, sizeof(int));
    char name[nameLength];
    lvlFile.read(&name[0], nameLength);
    o.name = std::string(name);

    lvlFile.read((char*)&o.x, sizeof(int));
    lvlFile.read((char*)&o.y, sizeof(int));
    lvlFile.read((char*)&o.w, sizeof(int));
    lvlFile.read((char*)&o.h, sizeof(int));
    lvlFile.read((char*)&o.permanent, sizeof(bool));

    int scriptNameLength;
    lvlFile.read((char*)&scriptNameLength, sizeof(int));
    char scriptName[scriptNameLength];
    lvlFile.read(&scriptName[0], scriptNameLength);
    o.scriptName = std::string(scriptName);

    int classNameLength;
    lvlFile.read((char*)&classNameLength, sizeof(int));
    char className[classNameLength];
    lvlFile.read(&className[0], classNameLength);
    o.className = std::string(className);

    int spriteNameLength;
    lvlFile.read((char*)&spriteNameLength, sizeof(int));
    char spriteName[spriteNameLength];
    lvlFile.read(&spriteName[0], spriteNameLength);
    o.spriteName = std::string(spriteName);

    objs.push_back(o);
  }
  std::cout << "Loaded " << numObjs << " GameObjects from " << path
            << std::endl;
  return objs;
}

  //================================================================

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

PYBIND11_MODULE(exporter, m) {
  pybind11::class_<LevelObject, std::shared_ptr<LevelObject>>(m, "LevelObject")
      .def(pybind11::init<>())
      .def_readwrite("name", &LevelObject::name)
      .def_readwrite("x", &LevelObject::x)
      .def_readwrite("y", &LevelObject::y)
      .def_readwrite("w", &LevelObject::w)
      .def_readwrite("h", &LevelObject::h)
      .def_readwrite("permanent", &LevelObject::permanent)
      .def_readwrite("scriptName", &LevelObject::scriptName)
      .def_readwrite("className", &LevelObject::className)
      .def_readwrite("spriteName", &LevelObject::spriteName);
  m.def("ExportLevel", &LevelExport);
  m.def("ImportLevel", &LevelImport);
}
