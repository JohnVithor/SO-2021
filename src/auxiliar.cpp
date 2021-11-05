
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <cstdlib>
#include <ctime>

double** createEmptyMatrix(size_t linhas, size_t colunas) {
    double** data = new double*[linhas];
    data[0] = new double[linhas * colunas];
    std::fill(data[0], data[0] + linhas * colunas, 0);
    for (size_t i = 1; i < linhas; ++i) {
        data[i] = data[0] + i * colunas;
    }
    return data;
}

double random_double() {
    return (double) rand() / RAND_MAX;

}

int main(int argc, char const *argv[]) {
    if (argc != 5) {
        std::cout << "O programa deve receber exatamente os seguintes argumentos: n1, m1, n2, m2" << std::endl << "n1 x m1 são as dimensões da 1ª matriz e n2 x m2 as da 2ª matriz." << std::endl;
        exit(1);
    }
    std::string::size_type sz;
    size_t n1 = std::stol(argv[1],&sz);
    size_t m1 = std::stol(argv[2],&sz);
    size_t n2 = std::stol(argv[3],&sz);
    size_t m2 = std::stol(argv[4],&sz);

    std::ofstream outdata;
    {
        std::srand(std::time(0));
        double** A = createEmptyMatrix(n1, m1);
        for (size_t i = 0; i < n1; ++i) {
            for (size_t j = 0; j < m1; ++j) {
                A[i][j] = random_double();
            }
        }
        outdata.open("matrix1.data");
        if( !outdata ) {
            std::cerr << "Error: file could not be opened" << std::endl;
            exit(1);
        }
        outdata << n1 << " " << m1 << std::endl;
        for (size_t i = 0; i < n1; ++i) {
            for (size_t j = 0; j < m1; ++j) {
                outdata << std::fixed << std::setprecision(5) << A[i][j] << " ";
            }
            outdata << std::endl;
        }
        outdata.close();
        delete [] A[0];
        delete [] A;
    }
    {
        std::srand(std::time(0)+1);
        double** B = createEmptyMatrix(n2, m2);
        for (size_t i = 0; i < n2; ++i) {
            for (size_t j = 0; j < m2; ++j) {
                B[i][j] = random_double();
            }
        }
        outdata.open("matrix2.data");
        if( !outdata ) {
            std::cerr << "Error: file could not be opened" << std::endl;
            exit(1);
        }
        outdata << n2 << " " << m2 << std::endl;
        for (size_t i = 0; i < n2; ++i) {
            for (size_t j = 0; j < m2; ++j) {
                outdata << std::fixed << std::setprecision(5) << B[i][j] << " ";
            }
            outdata << std::endl;
        }
        outdata.close();
        delete [] B[0];
        delete [] B;
    }

    return 0;
}