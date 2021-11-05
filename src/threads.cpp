#include <chrono>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

#include <pthread.h>

double** A;
size_t A_linhas;
size_t A_colunas;
double** B;
size_t B_linhas;
size_t B_colunas;
double** C;
size_t p;

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

void* thread_multiply(void* tid) {
    size_t el_inicial = (size_t)tid;
    size_t el_final = std::min(el_inicial+p-1, A_linhas*B_colunas);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    size_t i_inicial = el_inicial / B_colunas;
    size_t j_inicial = el_inicial % B_colunas - 1;
    if (j_inicial == (size_t) -1) {
        j_inicial = B_colunas-1;
        i_inicial -= 1;
    }
    size_t i_final = el_final / B_colunas;
    size_t j_final = el_final % B_colunas - 1;
    if (j_final == (size_t) -1) {
        j_final = B_colunas-1;
        i_final -= 1;
    }

    for (size_t i = i_inicial; i <= i_final; ++i) {
        for (size_t j = j_inicial; j <= j_final; ++j) {
            calcular_elemento_i_j(i, j);
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::ofstream outdata;
    outdata.open("resultado_threads_" + std::to_string(el_inicial) + "_" + std::to_string(el_final) +".data");
    if( !outdata ) {
        std::cerr << "Erro: Arquivo não pode ser criado." << std::endl;
        exit(1);
    }
    outdata << A_linhas << " " <<B_colunas << std::endl;
    for (size_t i = i_inicial; i <= i_final; ++i) {
        for (size_t j = j_inicial; j <= j_final; ++j) {
            outdata << "c" << i+1 << j+1 << " " << std::fixed << std::setprecision(5) << C[i][j] << std::endl;
        }
    }
    outdata << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    outdata.close();
    pthread_exit(NULL);
}

    
int main(int argc, char const *argv[]) {
    if (argc != 4) {
        std::cout << "O programa deve receber exatamente os seguintes argumentos: m1, m2 e p" << std::endl << "m1 é o caminho para a 1ª matriz, m2 o da 2ª matriz e p a quantidade de elementos por thread." << std::endl;
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
    p = std::stol(argv[3]);

    std::vector<pthread_t> threads;

    int status = 0;
    size_t count = 0;
    for (size_t i = 1; i <= A_linhas*B_colunas; i+=p) {
        threads.push_back(0);
        status = pthread_create(&threads[count], NULL, thread_multiply, (void *)i);
        ++count;
		if(status != 0) {
			std::cerr << "Erro na criação da thread. Codigo de Erro: "<< status << std::endl;
			return 1;
		}
    }
    void *thread_return = NULL;

    for (size_t i = 0; i < threads.size(); ++i) {
        pthread_join(threads[i], &thread_return);
    }

    delete [] A[0];
    delete [] A;
    delete [] B[0];
    delete [] B;
    delete [] C[0];
    delete [] C;
    return 0;
}