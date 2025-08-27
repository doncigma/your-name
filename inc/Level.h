#pragma once
#include <string>
#include <vector>

struct ObjectData {
    std::string type;
    int x;
    int y;
    int width;
    int height;
};

class Level {
public:
    Level() : name(""), path(""), objects(std::vector<ObjectData>()) {}
    Level(const std::string& name, const std::string& path, const std::vector<ObjectData>& objects)
        : name(name), path(path), objects(objects) {}
    ~Level() {}

    inline std::string getName() const { return this->name; }
    inline std::string getPath() const { return this->path; }
    inline std::vector<ObjectData> getObjects() const { return this->objects; }

private:
    std::string name;
    std::string path;
    std::vector<ObjectData> objects;
};
