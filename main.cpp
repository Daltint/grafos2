#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "image_foresting_transform.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <caminho_para_imagem>" << endl;
        return -1;
    }

    srand(time(0));

    // Carregar a imagem
    Mat img = imread(argv[1], IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "Erro ao carregar a imagem!" << endl;
        return -1;
    }

    int rows = img.rows;
    int cols = img.cols;

    // Inicializar a matriz de pixels
    vector<vector<Pixel>> image(rows, vector<Pixel>(cols));

    // Preencher a matriz de pixels com intensidades da imagem
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            image[i][j].intensity = img.at<uchar>(i, j);
            image[i][j].label = i * cols + j; // Inicializar com rótulos únicos
            image[i][j].x = i;
            image[i][j].y = j;
            image[i][j].cost = INF;
        }
    }

    // Aplicar o Algoritmo 3
    Algorithm3(image);

    // Criar uma imagem de resultado mantendo a intensidade original
    Mat result(rows, cols, CV_8UC1);

    // Manter as intensidades originais das regiões
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int label = image[i][j].label;
            result.at<uchar>(i, j) = img.at<uchar>(image[i][j].x, image[i][j].y);
        }
    }

    // Salvar a imagem resultante
    imwrite("result_image.jpg", result);

    // Mostrar a imagem resultante
    imshow("Resultado", result);
    waitKey(0);

    return 0;
}
