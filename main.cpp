#include <vector>
#include <SDL.h>
#include <iostream>
#include "utils.h"
#include "sdlFunctions.h"
#include "objLoader.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    init(); // Inicializa SDL y crea la ventana
    bool running = true;

    std::vector<Face> faces;
    std::vector<glm::vec3> vertices;
    std::string fileName = "spaceship.obj"; // Nombre del archivo OBJ a cargar
    std::string currentPath = getCurrentPath(); // Obtiene el directorio actual
    std::string filePath = getParentDirectory(currentPath) + "\\" + fileName; // Ruta completa del archivo OBJ

    bool success = loadOBJ(filePath, vertices, faces); // Carga el archivo OBJ y obtiene vértices y caras

    if (!success) {
        std::cout << "El archivo OBJ falló al cargarse." << std::endl;
        return 1;
    }

    glm::vec3 rotationAngles = glm::vec3(120, 120, 60); // Ajusta estos ángulos para la orientación deseada

    // Aplica la rotación a los vértices cargados
    for (auto& vertex : vertices) {
        vertex = rotateVertex(vertex, rotationAngles);
    }

    // Escala y traslada los vértices para ajustar la posición y escala deseada
    for (auto& vertex : vertices) {
        vertex.x *= 80;
        vertex.y *= 80;
        vertex.z *= 80;

        vertex.x += 275;
        vertex.y += 300;
        vertex.z += 300;
    }

    // Crea un arreglo de vértices a partir de los vértices y caras cargados
    std::vector<glm::vec3> vertexArray = setupVertexArray(vertices, faces);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        clear(); // Limpia la pantalla

        // Dibuja los triángulos formados por el arreglo de vértices
        for (size_t i = 0; i < vertexArray.size(); i += 3) {
            triangle(vertexArray[i], vertexArray[i + 1], vertexArray[i + 2]);
        }

        SDL_RenderPresent(renderer); // Actualiza la ventana
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
