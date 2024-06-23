#include "image_foresting_transform.h"
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <queue>

const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool Compare::operator()(Pixel* a, Pixel* b) {
    if (a->cost == b->cost) {
        return a < b;
    }
    return a->cost > b->cost;
}

double cost(Pixel* a, Pixel* b) {
    return std::abs(a->intensity - b->intensity);
}

void Algorithm3(std::vector<std::vector<Pixel>>& image) {
    std::priority_queue<Pixel*, std::vector<Pixel*>, Compare> Q;
    std::unordered_set<Pixel*> in_queue;

    int rows = image.size();
    int cols = image[0].size();

    // Inicializar pixels e adicionar pixels de borda à fila de prioridade
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Pixel& p = image[i][j];
            p.cost = (i == 0 || j == 0 || i == rows - 1 || j == cols - 1) ? 0 : INF;
            p.predecessor = nullptr;
            p.label = p.cost == 0 ? i * cols + j : -1; // Rótulos únicos para pixels de borda
            Q.push(&p);
            in_queue.insert(&p);
        }
    }

    while (!Q.empty()) {
        Pixel* s = Q.top();
        Q.pop();
        in_queue.erase(s);

        for (auto& dir : directions) {
            int nx = s->x + dir.first;
            int ny = s->y + dir.second;

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                Pixel* t = &image[nx][ny];

                if (in_queue.find(t) != in_queue.end()) {
                    double new_cost = s->cost + cost(s, t);
                    if (new_cost < t->cost) {
                        t->cost = new_cost;
                        t->predecessor = s;
                        t->label = s->label;
                        
                        // Atualiza a fila de prioridade
                        Q.push(t);
                    }
                }
            }
        }
    }
}
