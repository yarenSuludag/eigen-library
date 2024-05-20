#include <iostream>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

using namespace std;
using namespace cv;

int main() {
    // PGM dosyasını oku
    Mat img = imread("yeni_dunya.pgm", IMREAD_GRAYSCALE);

    // Matris boyutlarını al
    int rows = img.rows;
    int cols = img.cols;

    // Gri renkli bölgeleri siyah ve beyaz renklere dönüştürmek için yeni bir matris oluştur
    Eigen::MatrixXd binaryMatrix(rows, cols);

    // Eşik değeri belirle (örneğin 128)
    int threshold = 128;

    // Gri renkli bölgeleri siyah ve beyaz renklere dönüştür
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (img.at<uchar>(i, j) > threshold) {
                binaryMatrix(i, j) = 255; // Beyaz renk
            } else {
                binaryMatrix(i, j) = 0; // Siyah renk
            }
        }
    }

    // Yeni matrisi ekrana yazdır
    cout << "Binary Matrix:\n" << binaryMatrix << endl;

    // Gri renkten siyah veya beyaza geçiş yapan indis değerlerini bul
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            if (binaryMatrix(i, j) != binaryMatrix(i - 1, j - 1) ||
                binaryMatrix(i, j) != binaryMatrix(i - 1, j) ||
                binaryMatrix(i, j) != binaryMatrix(i - 1, j + 1) ||
                binaryMatrix(i, j) != binaryMatrix(i, j - 1) ||
                binaryMatrix(i, j) != binaryMatrix(i, j + 1) ||
                binaryMatrix(i, j) != binaryMatrix(i + 1, j - 1) ||
                binaryMatrix(i, j) != binaryMatrix(i + 1, j) ||
                binaryMatrix(i, j) != binaryMatrix(i + 1, j + 1)) {
                cout << "Gri renkten siyah veya beyaza geçiş: " << i << ". satır, " << j << ". sütun\n";
            }
        }
    }

    // Gri renkten siyah veya beyaza geçiş yapan bloğu yeni bir matriste sakla
    Eigen::MatrixXd transitionBlock(rows, cols);
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            if (binaryMatrix(i, j) != binaryMatrix(i - 1, j - 1) ||
                binaryMatrix(i, j) != binaryMatrix(i - 1, j) ||
                binaryMatrix(i, j) != binaryMatrix(i - 1, j + 1) ||
                binaryMatrix(i, j) != binaryMatrix(i, j - 1) ||
                binaryMatrix(i, j) != binaryMatrix(i, j + 1) ||
                binaryMatrix(i, j) != binaryMatrix(i + 1, j - 1) ||
                binaryMatrix(i, j) != binaryMatrix(i + 1, j) ||
                binaryMatrix(i, j) != binaryMatrix(i + 1, j + 1)) {
                transitionBlock(i, j) = binaryMatrix(i, j);
            }
        }
    }

    // Yeni matrisi ekrana yazdır
    cout << "Transition Block:\n" << transitionBlock << endl;

     // Gri, siyah ve beyaz renklere karşılık gelen tam sayı değerlerini yazdır
    for (int i = 0; i < transitionBlock.rows(); ++i) {
        for (int j = 0; j < transitionBlock.cols(); ++j) {
            int pixelValue = static_cast<int>(transitionBlock(i, j));
            if (pixelValue == 0) {
                cout << "Siyah renkli değerlerden birisi " << i << ". satır " << j << ". sütunda transitionBlock[" << i << "][" << j << "]=" << pixelValue << endl;
            } else if (pixelValue == 255) {
                cout << "Beyaz renkli değerlerden birisi " << i << ". satır " << j << ". sütunda transitionBlock[" << i << "][" << j << "]=" << pixelValue << endl;
            } else {
                cout << "Gri renkli değerlerden birisi " << i << ". satır " << j << ". sütunda transitionBlock[" << i << "][" << j << "]=" << pixelValue << endl;
            }
        }
    }


    // Dışa doğru genişletme (dilate) işlemi
    int dilationSize = 10; // Şişirme miktarı (parametre)
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * dilationSize + 1, 2 * dilationSize + 1),
                                        Point(dilationSize, dilationSize));
    Mat dilatedImg;
    dilate(transitionBlock, dilatedImg, element);

    // Genişletilmiş matrisi ekrana yazdır
    cout << "Dilated Matrix:\n" << dilatedImg << endl;

    // Genişletilmiş matrisi yeni bir PGM dosyasına kaydet
    Mat newImg(rows, cols, CV_8U);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            newImg.at<uchar>(i, j) = static_cast<uchar>(dilatedImg.at<double>(i, j));
        }
    }

    imwrite("yeni_dunya_sisirilmis.pgm", newImg);

    return 0;
}
