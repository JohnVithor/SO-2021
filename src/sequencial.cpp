
#include <chrono>

#include "matrix.cpp"

void calcular_elemento_i_j(Matrix& A, Matrix& B, Matrix& C, size_t i, size_t j) {
    double value = 0;
    for (size_t k = 0; k < B.getLinhas(); ++k){
        value += A.get(i, k) * B.get(k, j);
    }
    C.set(i, j, value);
}

void multiply_matrix(Matrix& A, Matrix& B, Matrix& C){
    for (size_t i = 0; i < A.getLinhas(); ++i) {
        for (size_t j = 0; j < B.getColunas(); ++j) {
            calcular_elemento_i_j(A, B, C, i, j);
        }
    }
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cout << "O programa deve receber exatamente os seguintes argumentos: m1 e m2" << std::endl << "m1 é o caminho para a 1ª matriz e m2 o da 2ª matriz." << std::endl;
        exit(1);
    }
    Matrix m1 = Matrix(argv[1]);
    Matrix m2 = Matrix(argv[2]);
    Matrix r = Matrix(m1.getLinhas(), m2.getColunas());

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    multiply_matrix(m1, m2, r);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::ofstream outdata;
    outdata.open("resultado_sequencial.data");
    if( !outdata ) {
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }

    outdata << r.getLinhas() << " " << r.getColunas() << std::endl;
    for (size_t i = 0; i < m1.getLinhas(); ++i) {
        for (size_t j = 0; j < m2.getColunas(); ++j) {
            outdata << "c" << i+1 << j+1 << " " << std::fixed << std::setprecision(5) << r.get(i, j) << std::endl;
        }
    }
    
    outdata << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    outdata.close();
}