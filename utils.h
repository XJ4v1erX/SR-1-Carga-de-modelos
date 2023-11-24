// Incluye las bibliotecas necesarias
#include <string>
#include <vector>
#include <filesystem>
#include "glm/glm.hpp"
#pragma once

// Define una estructura para representar colores RGBA
struct Color {
    uint8_t r; // Componente rojo
    uint8_t g; // Componente verde
    uint8_t b; // Componente azul
    uint8_t a; // Componente alfa (transparencia)
};

// Define una estructura para representar una cara (triángulo en este caso)
struct Face {
    std::vector<std::array<int, 3>> vertexIndices; // Índices de vértices que forman la cara
};

// Función para obtener la ruta del directorio actual
std::string getCurrentPath() {
    return std::filesystem::current_path().string();
}

// Función para obtener el directorio padre de una ruta dada
std::string getParentDirectory(const std::string& path) {
    std::filesystem::path filePath(path);
    return filePath.parent_path().string();
}

// Este archivo de encabezado proporciona estructuras y funciones útiles para trabajar con gráficos en 3D.
