#include <vector>
#include <array>
#include <SDL.h>
#include <sstream>
#include <iostream>
#include "utils.h"
#include "sdlFunctions.h"
#include "glm/gtc/matrix_transform.hpp"

// Función para cargar un archivo OBJ y extraer vértices y caras
bool loadOBJ(const std::string& path, std::vector<glm::vec3>& out_vertices, std::vector<Face>& out_faces) {
    out_vertices.clear();
    out_faces.clear();

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: No es posible abrir el archivo " << path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            out_vertices.push_back(vertex);
        } else if (type == "f") {
            std::string lineHeader;
            Face face;
            while (iss >> lineHeader)
            {
                std::istringstream tokenstream(lineHeader);
                std::string token;
                std::array<int, 3> vertexIndices{};

                // Lee los tres valores separados por '/' para cada vértice de la cara
                for (int i = 0; i < 3; ++i) {
                    std::getline(tokenstream, token, '/');
                    vertexIndices[i] = std::stoi(token) - 1; // Resta 1 para convertir a índices basados en 0
                }

                face.vertexIndices.push_back(vertexIndices);
            }
            out_faces.push_back(face);
        }
    }

    file.close();
    return true;
}

// Función para construir un arreglo de vértices a partir de vértices y caras
std::vector<glm::vec3> setupVertexArray(const std::vector<glm::vec3>& vertices, const std::vector<Face>& faces) {
    std::vector<glm::vec3> vertexArray;

    // Para cada cara
    for (const auto& face : faces) {
        for (const auto& vertexIndices : face.vertexIndices) {
            glm::vec3 vertexPosition = vertices[vertexIndices[0]]; // Toma la posición del vértice
            vertexArray.push_back(vertexPosition);
        }
    }

    return vertexArray;
}

// Función para rotar un vértice dado por sus coordenadas usando una matriz de rotación
glm::vec3 rotateVertex(const glm::vec3& vertex, const glm::vec3& rotation) {
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));

    glm::mat4 rotationMatrix = rotX * rotY * rotZ;
    glm::vec4 rotatedVertex = rotationMatrix * glm::vec4(vertex, 1.0f);

    return {rotatedVertex.x, rotatedVertex.y, rotatedVertex.z};
}
