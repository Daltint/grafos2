#include "image_foresting_transform.h"
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <queue>

const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool Compare::operator()(Pixel* a, Pixel* b) {
    return a->cost > b->cost;
}

double cost(Pixel* a, Pixel* b) {
    return std::abs(a->intensity - b->intensity);
}

void Algorithm3(std::vector<std::vector<Pixel>>& image) {
    std::priority_queue<Pixel*, std::vector<Pixel*>, Compare> Q;
    int rows = image.size();
    int cols = image[0].size();

    // Inicializar pixels e adicionar pixels de borda à fila de prioridade
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Pixel& p = image[i][j];
            p.x = i;
            p.y = j;
            if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1) {
                p.cost = 0;
                p.label = i * cols + j; // Rótulos únicos para pixels de borda
                Q.push(&p);
            }
        }
    }

    int label_counter = 1;

    while (!Q.empty()) {
        Pixel* s = Q.top();
        Q.pop();

        for (auto& dir : directions) {
            int nx = s->x + dir.first;
            int ny = s->y + dir.second;

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                Pixel* t = &image[nx][ny];

                double new_cost = s->cost + cost(s, t);
                if (new_cost < t->cost) {
                    t->cost = new_cost;
                    t->predecessor = s;
                    t->label = s->label; // Propagar o mesmo rótulo do predecessor
                    Q.push(t);
                }
            }
        }
    }
}
