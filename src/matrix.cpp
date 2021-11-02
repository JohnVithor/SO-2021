
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <cstdlib>

class Matrix {
  private:
    size_t linhas;
    size_t colunas;
    int seed;
    double** data;

    void createEmptyMatrix() {
        data = new double*[linhas];
        data[0] = new double[linhas * colunas];
        std::fill(data[0], data[0] + linhas * colunas, 0);
        for (size_t i = 1; i < linhas; ++i) {
            data[i] = data[0] + i * colunas;
        }
    }

    double random_double() {
        return (double) rand() / RAND_MAX;

    }

    void fillMatrix() {
        std::srand(seed);
        for (size_t i = 0; i < linhas; ++i) {
            for (size_t j = 0; j < colunas; ++j) {
                data[i][j] = random_double();
            }
        }
    }
  public:
    Matrix (size_t linhas, size_t colunas) {
        this->linhas = linhas;
        this->colunas = colunas;
        createEmptyMatrix();
    }
    Matrix (size_t linhas, size_t colunas, int seed) {
        this->linhas = linhas;
        this->colunas = colunas;
        this->seed = seed;
        createEmptyMatrix();
        fillMatrix();
    }

    Matrix (std::string filename) {
        std::ifstream fileSource(filename);
        if (!fileSource) {
            std::cerr << "Error: file could not be opened: " << filename << std::endl;
            exit(-1);
        }
        else {
            fileSource >> linhas;
            fileSource >> colunas;
            createEmptyMatrix();
            for (size_t i = 0; i < linhas; ++i) {
                for (size_t j = 0; j < colunas; ++j) {
                    fileSource >> data[i][j];
                }
            }
            fileSource.close();
        }
    }

    ~Matrix() {
        delete [] data[0];
        delete [] data;
    }

    size_t getLinhas() {
        return linhas;
    }

    size_t getColunas() {
        return colunas;
    }

    void set(size_t i, size_t j, double value) {
        data[i][j] = value;
    }

    double get(size_t i, size_t j) {
        return data[i][j];
    }

    friend std::ostream & operator<<(std::ostream &os, const Matrix& matrix) {
        os << matrix.linhas << " " << matrix.colunas << std::endl;
        for (size_t i = 0; i < matrix.linhas; ++i) {
            for (size_t j = 0; j < matrix.colunas; ++j) {
                os << std::fixed << std::setprecision(5) << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};