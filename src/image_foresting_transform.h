#ifndef IMAGE_FORESTING_TRANSFORM_H
#define IMAGE_FORESTING_TRANSFORM_H

#include <vector>
#include <queue>
#include <limits>

const double INF = std::numeric_limits<double>::infinity();

struct Pixel {
    int x, y; // Coordenadas do pixel
    int intensity; // Intensidade do pixel
    int label; // Rótulo do pixel
    double cost; // Custo do pixel
    Pixel* predecessor; // Predecessor no caminho mínimo

    Pixel() : x(0), y(0), intensity(0), label(-1), cost(INF), predecessor(nullptr) {}
};

struct Compare {
    bool operator()(Pixel* a, Pixel* b);
};

double cost(Pixel* a, Pixel* b);
void Algorithm3(std::vector<std::vector<Pixel>>& image);

#endif // IMAGE_FORESTING_TRANSFORM_H
