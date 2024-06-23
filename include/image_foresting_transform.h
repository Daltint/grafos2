#ifndef IMAGE_FORESTING_TRANSFORM_H
#define IMAGE_FORESTING_TRANSFORM_H

#include <vector>
#include <queue>
#include <opencv2/opencv.hpp>
#include <limits>

struct Pixel {
    int x, y;
    int intensity;
    int label;
    double cost;
    Pixel* predecessor;
};

struct Compare {
    bool operator()(Pixel* a, Pixel* b);
};

const double INF = std::numeric_limits<double>::infinity();

double cost(Pixel* a, Pixel* b);
void Algorithm3(std::vector<std::vector<Pixel>>& image);

#endif // IMAGE_FORESTING_TRANSFORM_H
