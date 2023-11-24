#include <vector>
#include <SDL.h>
#include <iostream>
#include "utils.h"
#include "sdlFunctions.h"
#include "objLoader.h"
#include "glm/gtc/matrix_transform.hpp"


std::vector<glm::vec3> setupVertexArray(const std::vector<glm::vec3>& vertices, const std::vector<Face>& faces) {
    std::vector<glm::vec3> vertexArray;

    // For each face
    for (const auto& face : faces) {
        // For each vertex in the face
        for (const auto& vertexIndices : face.vertexIndices) {
            // Get the vertex position from the input array using the indices from the face
            glm::vec3 vertexPosition = vertices[vertexIndices[0]];

            // Add the vertex position to the vertex array
            vertexArray.push_back(vertexPosition);
        }
    }

    return vertexArray;
}
glm::vec3 rotateVertex(const glm::vec3& vertex, const glm::vec3& rotation) {
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));

    glm::mat4 rotationMatrix = rotX * rotY * rotZ;
    glm::vec4 rotatedVertex = rotationMatrix * glm::vec4(vertex, 1.0f);

    return {rotatedVertex.x, rotatedVertex.y, rotatedVertex.z};
}




int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    init();
    bool running = true;

    std::vector<Face> faces;
    std::vector<glm::vec3> vertices;
    std::string fileName = "spaceship.obj";
    std::string currentPath = getCurrentPath();
    std::string filePath = getParentDirectory(currentPath) + "\\" + fileName;

    bool success = loadOBJ(filePath, vertices, faces);

    if (!success) {
        std::cout << "El archivo OBJ fallo al cargarse." << std::endl;
        return 1;
    }
    glm::vec3 rotationAngles = glm::vec3(125, 120, 50); // Ajusta estos ángulos para la orientación deseada
    for (auto& vertex : vertices) {
        vertex = rotateVertex(vertex, rotationAngles);
    }

    for (auto& vertex : vertices) {
        vertex.x *= 80;
        vertex.y *= 80;
        vertex.z *= 80;

        vertex.x += 300;
        vertex.y += 320;
        vertex.z += 300;
    }

    std::vector<glm::vec3> vertexArray = setupVertexArray(vertices, faces);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        clear();

        setColor(); // Set color to white
        for (size_t i = 0; i < vertexArray.size(); i += 3) {
            triangle(vertexArray[i], vertexArray[i + 1], vertexArray[i + 2]);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}