
#include <chrono>
#include <string>
#include <algorithm>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "matrix.cpp"

pid_t criar_filho() {
    pid_t pid = fork();
    if (pid < 0) {
        printf("Erro ao criar processo\n");
        exit(1);
    }
    return pid;
}

void calcular_elemento_i_j(Matrix& A, Matrix& B, Matrix& C, size_t i, size_t j) {
    double value = 0;
    for (size_t k = 0; k < B.getLinhas(); ++k){
        value += A.get(i, k) * B.get(k, j);
    }
    C.set(i, j, value);
}

void proc_function(Matrix& A, Matrix& B, Matrix& C, size_t el_inicial, size_t el_final){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    size_t i_inicial = el_inicial / C.getColunas();
    size_t j_inicial = el_inicial % C.getColunas() - 1;
    if (j_inicial == -1) {
        j_inicial = C.getColunas()-1;
        i_inicial -= 1;
    }
    size_t i_final = el_final / C.getColunas();
    size_t j_final = el_final % C.getColunas() - 1;
    if (j_final == -1) {
        j_final = C.getColunas()-1;
        i_final -= 1;
    }
    for (size_t i = i_inicial; i <= i_final; ++i) {
        for (size_t j = j_inicial; j <= j_final; ++j) {
            calcular_elemento_i_j(A, B, C, i, j);
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::ofstream outdata;
    outdata.open("resultado_processos_" + std::to_string(el_inicial) + "_" + std::to_string(el_final) +".data");
    if( !outdata ) {
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }
    outdata << C.getLinhas() << " " << C.getColunas() << std::endl;
    for (size_t i = i_inicial; i <= i_final; ++i) {
        for (size_t j = j_inicial; j <= j_final; ++j) {
            outdata << "c" << i+1 << j+1 << " " << std::fixed << std::setprecision(5) << C.get(i, j) << std::endl;
        }
    }
    outdata << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    outdata.close();
}

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        std::cout << "O programa deve receber exatamente os seguintes argumentos: m1, m2 e p" << std::endl << "m1 é o caminho para a 1ª matriz, m2 o da 2ª matriz e p a quantidade de elementos por processo." << std::endl;
        exit(1);
    }
    Matrix A = Matrix(argv[1]);
    Matrix B = Matrix(argv[2]);
    size_t p = std::stol(argv[3]);

    Matrix C = Matrix(A.getLinhas(), B.getColunas());

    size_t n_filhos = 0;
    pid_t pid = -1;
    for (size_t i = 1; i <= C.getLinhas()*C.getColunas(); i+=p) {
        if (pid != 0) {
            pid = criar_filho();
            ++n_filhos;
        }
        if(pid == 0) {
            proc_function(A, B, C, i, std::min(i+p-1, C.getLinhas()*C.getColunas()));
            break;
        }
    }
    if (pid != 0) {
        for (size_t i = 0; i < n_filhos; ++i) {
            wait(NULL);
        }
    }
    return 0;
}