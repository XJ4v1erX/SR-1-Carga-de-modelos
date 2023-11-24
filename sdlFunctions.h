#include <fstream>
#include <vector>
#include "glm/glm.hpp"
#include <array>
#include <SDL.h>
#include <sstream>
#include <filesystem>
#include <iostream>
#include "utils.h"
#pragma once


// Declaración de variables globales
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Color currentColor = {255, 255, 255, 255}; // Color actual, inicialmente blanco
Color clearColor = {0, 0, 0, 255}; // Color de fondo, inicialmente negro

// Función para inicializar SDL y crear la ventana y el renderizador
void init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

// Función para borrar la pantalla con el color de fondo
void clear() {
    SDL_SetRenderDrawColor(renderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    SDL_RenderClear(renderer);
}


// Función para dibujar un punto en las coordenadas (x, y)
void point(int x, int y) {
    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
    SDL_RenderDrawPoint(renderer, x, y);
}

// Función para dibujar una línea desde 'start' hasta 'end' usando el algoritmo de Bresenham
void line(glm::vec3 start, glm::vec3 end) {
    int x1 = static_cast<int>(round(start.x));
    int y1 = static_cast<int>(round(start.y));
    int x2 = static_cast<int>(round(end.x));
    int y2 = static_cast<int>(round(end.y));

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        point(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Función para dibujar un triángulo dado por sus vértices A, B y C
void triangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C) {
    line(A, B);
    line(B, C);
    line(C, A);
}

// Este archivo contiene funciones para la inicialización y dibujo en una ventana SDL.