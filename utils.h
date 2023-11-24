
#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "glm/glm.hpp"

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Face {
    std::vector<std::array<int, 3>> vertexIndices;
};

std::string getCurrentPath() {
    return std::filesystem::current_path().string();
}

std::string getParentDirectory(const std::string& path) {
    std::filesystem::path filePath(path);
    return filePath.parent_path().string();
}
