
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <cstdlib>
#include <ctime>

#include "matrix.cpp"

int main(int argc, char const *argv[]) {
    if (argc != 5) {
        std::cout << "O programa deve receber exatamente os seguintes argumentos: n1, m1, n2, m2" << std::endl << "n1 x m1 são as dimensões da 1ª matriz e n2 x m2 as da 2ª matriz." << std::endl;
        exit(1);
    }
    std::string::size_type sz;
    long n1 = std::stol(argv[1],&sz);
    long m1 = std::stol(argv[2],&sz);
    long n2 = std::stol(argv[3],&sz);
    long m2 = std::stol(argv[4],&sz);

    std::ofstream outdata;
    {
        outdata.open("matrix1.data");
        if( !outdata ) {
            std::cerr << "Error: file could not be opened" << std::endl;
            exit(1);
        }
        std::srand(std::time(0));
        Matrix matrix1 = Matrix(n1,m1,std::rand());
        outdata << matrix1;
        outdata.close();
    }
    {
        outdata.open("matrix2.data");
        if( !outdata ) {
            std::cerr << "Error: file could not be opened" << std::endl;
            exit(1);
        }
        
        std::srand(std::time(0)+1);
        Matrix matrix2 = Matrix(n2,m2,std::rand());
        outdata << matrix2;
        outdata.close();
    }
    return 0;
}