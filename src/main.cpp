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
            image[i][j].x = i;
            image[i][j].y = j;
        }
    }

    // Aplicar o Algoritmo 3
    Algorithm3(image);

    // Criar uma imagem de resultado com o mapa de rótulos
    Mat result(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.at<uchar>(i, j) = static_cast<uchar>(image[i][j].label % 256); // Escalar o rótulo para 0-255
        }
    }

    // Salvar a imagem resultante
    imwrite("result_image.jpg", result);

    // Mostrar a imagem resultante
    imshow("Resultado", result);
    waitKey(0);

    return 0;
}
