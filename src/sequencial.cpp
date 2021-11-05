
#include <chrono>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

double** A;
size_t A_linhas;
size_t A_colunas;
double** B;
size_t B_linhas;
size_t B_colunas;
double** C;

double** createEmptyMatrix(size_t linhas, size_t colunas) {
    double** data = new double*[linhas];
    data[0] = new double[linhas * colunas];
    std::fill(data[0], data[0] + linhas * colunas, 0);
    for (size_t i = 1; i < linhas; ++i) {
        data[i] = data[0] + i * colunas;
    }
    return data;
}

void calcular_elemento_i_j(size_t i, size_t j) {
    double value = 0;
    for (size_t k = 0; k < B_linhas; ++k){
        value += A[i][k] * B[k][j];
    }
    C[i][j] = value;
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cout << "O programa deve receber exatamente os seguintes argumentos: A e B" << std::endl << "A é o caminho para a 1ª matriz e B o da 2ª matriz." << std::endl;
        exit(1);
    }
    {
        std::ifstream fileSource(argv[1]);
        if (!fileSource) {
            std::cerr << "Erro: Arquivo não pode ser aberto - " << argv[1] << std::endl;
            exit(-1);
        } else {
            fileSource >> A_linhas;
            fileSource >> A_colunas;
            A = createEmptyMatrix(A_linhas, A_colunas);
            for (size_t i = 0; i < A_linhas; ++i) {
                for (size_t j = 0; j < A_colunas; ++j) {
                    fileSource >> A[i][j];
                }
            }
            fileSource.close();
        }
    }
    {
        std::ifstream fileSource(argv[2]);
        if (!fileSource) {
            std::cerr << "Erro: Arquivo não pode ser aberto - " << argv[2] << std::endl;
            exit(-1);
        } else {
            fileSource >> B_linhas;
            fileSource >> B_colunas;
            B = createEmptyMatrix(B_linhas, B_colunas);
            for (size_t i = 0; i < B_linhas; ++i) {
                for (size_t j = 0; j < B_colunas; ++j) {
                    fileSource >> B[i][j];
                }
            }
            fileSource.close();
        }
    }
    C = createEmptyMatrix(A_linhas, B_colunas);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < A_linhas; ++i) {
        for (size_t j = 0; j < B_colunas; ++j) {
            calcular_elemento_i_j(i, j);
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::ofstream outdata;
    outdata.open("resultado_sequencial_"+std::to_string(A_linhas*B_colunas)+".data");
    if( !outdata ) {
        std::cerr << "Erro: Arquivo não pode ser criado." << std::endl;
        exit(1);
    }

    outdata << A_linhas << " " << B_colunas << std::endl;
    for (size_t i = 0; i < A_linhas; ++i) {
        for (size_t j = 0; j < B_colunas; ++j) {
            outdata << "c" << i+1 << j+1 << " " << std::fixed << std::setprecision(5) << C[i][j] << std::endl;
        }
    }
    
    outdata << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    outdata.close();
    delete [] A[0];
    delete [] A;
    delete [] B[0];
    delete [] B;
    delete [] C[0];
    delete [] C;
    return 0;
}