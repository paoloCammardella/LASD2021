#include "test.hpp"

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <iomanip>

void mytest()
{
    std::cout << "Benvenuti nel mio test" << std::endl;
    matrixTest();

    std::cout << "Arrivederci." << std::endl;
}

/* *****************************************Matrix***************************************** */
void matrixTest()
{
    int scelta;
scelta:
    std::cout << "Quale tipo vuoi utilizzare?" << std::endl
              << "1- matrixVec" << std::endl
              << "2- matrixCSR" << std::endl;
    std::cin >> scelta;

    switch (scelta)
    {
    case 1:
    {
        std::cout << "Inizio test su matrixVec;" << std::endl;
        matrixVecTest();
        break;
    }
    case 2:
    {
        std::cout << "Inizio test su matrixCSR;" << std::endl;
        matrixCSRTest();
        break;
    }
    case 0:
    {
        std::cout << "uscita dal menu" << std::endl;
        return;
    }
    default:
        goto scelta;
        break;
    }
}

/* ****************************************MatrixVec**************************************** */
void matrixVecTest()
{
    int scelta;
scelta:
    std::cout << "Quale tipo vuoi utilizzare?" << std::endl
              << "1- Int" << std::endl
              << "2- Double" << std::endl
              << "3- String" << std::endl
              << "0- uscita" << std::endl;
    std::cin >> scelta;

    std::cout << "Inserire la dimensione delle righe della matrice da popolare" << std::endl;
    unsigned long dimRow;
    std::cin >> dimRow;

    std::cout << "Inserire la dimensione delle colonne della matrice da popolare" << std::endl;
    unsigned long dimColumn;
    std::cin >> dimColumn;

    switch (scelta)
    {
    case 1:
    {
        std::cout << "Inizio test su MatrixVec<int>;" << std::endl;

        lasd::MatrixVec<int> matrix(dimRow, dimColumn);
        int n = 50;
        int acc = 1;
        popolateMatrix(matrix);
        void (*fun)(const int &, void *) = printElement;
        std::cout << "\x1B[33mEseguo la map sulla matrice\033[0m" << std::endl;
        matrix.MapPreOrder(fun, nullptr);

        std::cout << std::endl
                  << "\x1B[33mEseguo la fold sulla matrice\033[0m" << std::endl;
        matrix.FoldPreOrder(&foldProduct, &n, &acc);
        std::cout << "\x1B[32mIl risultato della fold e`: \033[0m" << acc << std::endl;
        unsigned long riga, colonna;
        std::cout << "Inserire l'indice di riga: ";
        std::cin >> riga;
        std::cout << "Inserire l'indice della colonna: ";
        std::cin >> colonna;
        std::string risposta = matrix.ExistsCell(riga, colonna) ? " " : "non ";
        std::cout << "La cella: " << riga << " " << colonna << risposta << "esiste" << std::endl;
        matrix.MapPreOrder(&doubleIt, nullptr);
    }
    break;
    case 2:
    {
        std::cout << "Inizio test su MatrixVec<double>;" << std::endl;
        lasd::MatrixVec<double> matrix(dimRow, dimColumn);
        double n = 0.5;
        double acc = 1;
        popolateMatrix(matrix);
        void (*fun)(const double &, void *) = printElement;
        std::cout << "\x1B[33mEseguo la map sulla matrice\033[0m" << std::endl;
        matrix.MapPreOrder(fun, nullptr);
        std::cout << std::endl
                  << "\x1B[33mEseguo la fold sulla matrice\033[0m" << std::endl;
        matrix.FoldPreOrder(&foldSum, &n, &acc);
        std::cout << "\x1B[32mIl risultato della fold e`: \033[0m" << acc << std::endl;
        unsigned long riga, colonna;
        std::cout << "Inserire l'indice di riga: ";
        std::cin >> riga;
        std::cout << "Inserire l'indice della colonna: ";
        std::cin >> colonna;
        std::string risposta = matrix.ExistsCell(riga, colonna) ? " " : "non ";
        std::cout << "La cella: " << riga << " " << colonna << risposta << "esiste" << std::endl;
        matrix.MapPreOrder(&negativePowerOfThree, nullptr);
    }
    break;

    case 3:
    {
        std::cout << "Inizio test su MatrixVec<std::string>;" << std::endl;
        lasd::MatrixVec<std::string> matrix(dimRow, dimColumn);
        int n = 5;
        std::string acc = "";
        popolateMatrix(matrix);
        void (*fun)(const std::string &, void *) = printElement;
        std::cout << "\x1B[33mEseguo la map sulla matrice\033[0m" << std::endl;
        matrix.MapPreOrder(fun, nullptr);
        std::cout << std::endl
                  << "\x1B[33mEseguo la fold sulla matrice\033[0m" << std::endl;
        matrix.FoldPreOrder(&foldStringConcat, &n, &acc);
        std::cout << "\x1B[32mIl risultato della fold e`: \033[0m" << acc << std::endl;
        std::cout << "Il risultato della fold e`: " << acc << std::endl;
        unsigned long riga, colonna;
        std::cout << "Inserire l'indice di riga: ";
        std::cin >> riga;
        std::cout << "Inserire l'indice della colonna: ";
        std::cin >> colonna;
        std::string risposta = matrix.ExistsCell(riga, colonna) ? " " : "non ";
        std::cout << "La cella: " << riga << " " << colonna << risposta << "esiste" << std::endl;
        matrix.MapPreOrder(&addString, nullptr);
    }
    break;

    case 0:
    {
        std::cout << "uscita dal menu" << std::endl;
        return;
    }
    default:
        goto scelta;
        break;
    }
}

template <typename Data>
void popolateMatrix(lasd::MatrixVec<Data> &mat)
{
    if (std::is_same<Data, int>::value)
    {
        for (unsigned long i = 0; i < mat.RowNumber(); ++i)
        {
            for (unsigned long j = 0; j < mat.ColumnNumber(); ++j)
            {
                std::default_random_engine generator(std::random_device{}());
                std::uniform_int_distribution<int> distribution(0, 100);
                mat(i, j) = distribution(generator);
            }
        }
    }
    else if (std::is_same<Data, double>::value)
    {
        for (unsigned long i = 0; i < mat.RowNumber(); ++i)
        {
            for (unsigned long j = 0; j < mat.ColumnNumber(); ++j)
            {
                std::default_random_engine generator(std::random_device{}());
                std::uniform_real_distribution<double> distribution(0.0, 1.0);
                mat(i, j) = distribution(generator);
            }
        }
    }
    else if (std::is_same<Data, std::string>::value)
    {
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> distribution(0, 13);
        for (unsigned long i = 0; i < mat.RowNumber(); ++i)
        {
            for (unsigned long j = 0; j < mat.ColumnNumber(); ++j)
            {
                // mat(i, j) = generateString(distribution(generator));
            }
        }
    }
}

void foldProduct(const int &dat, const void *par, void *acc)
{
    if (dat < *(int *)par)
        *((int *)acc) *= dat;
}

void foldSum(const double &dat, const void *par, void *acc)
{
    if (dat > *(double *)par)
        *((double *)acc) += dat;
}

void foldStringConcat(const std::string &dat, const void *par, void *acc)
{
    if (dat.length() <= *(int *)par)
        *((std::string *)acc) += dat;
}

template <typename Data>
void printElement(const Data &dat, void *_)
{
    std::cout << dat << " ";
}

void doubleIt(int& data, void*_){
        std::cout<< data*2 << " ";
}

void negativePowerOfThree(double& data, void*_){
    std::cout << data*data*data << " ";
}

void addString(std::string& data, void* stringToAdd){
    std::cout << *((std::string *)stringToAdd) + data << " ";
}

std::string generateString(unsigned long len)
{

    std::default_random_engine generator(len);
    std::uniform_int_distribution<char> distribution('a', 'z');

    char str[len + 1];
    for (unsigned int i = 0; i < len; ++i)
    {
        str[i] = distribution(generator);
    }
    str[len] = '\0';
    return str;
}

void matrixCSRTest()
{
    int scelta;
scelta:
    std::cout << "Quale tipo vuoi utilizzare?" << std::endl
              << "1- Int" << std::endl
              << "2- Double" << std::endl
              << "3- String" << std::endl
              << "0- uscita" << std::endl;
    std::cin >> scelta;

    std::cout << "Inserire la dimensione delle righe della matrice da popolare" << std::endl;
    unsigned long dimRow;
    std::cin >> dimRow;

    std::cout << "Inserire la dimensione delle colonne della matrice da popolare" << std::endl;
    unsigned long dimColumn;
    std::cin >> dimColumn;

    switch (scelta)
    {
    case 1:
    {
        std::cout << "Inizio test su MatrixCSR<int>;" << std::endl;

        lasd::MatrixCSR<int> matrix(dimRow, dimColumn);
        int n = 50;
        int acc = 1;
        popolateMatrix(matrix);
        void (*fun)(const int &, void *) = printElement;
        std::cout << "\x1B[33mEseguo la map sulla matrice\033[0m" << std::endl;
        matrix.MapPreOrder(fun, nullptr);

        std::cout << std::endl
                  << "\x1B[33mEseguo la fold sulla matrice\033[0m" << std::endl;
        matrix.FoldPreOrder(&foldProduct, &n, &acc);
        std::cout << "\x1B[32mIl risultato della fold e`: \033[0m" << acc << std::endl;
        std::cout << std::endl
                  << "\x1B[33mControllo dell'esistenza di un valore\033[0m" << std::endl;
        unsigned long riga, colonna;
        std::cout << "Inserire l'indice di riga: ";
        std::cin >> riga;
        std::cout << "Inserire l'indice della colonna: ";
        std::cin >> colonna;
        std::string risposta = matrix.ExistsCell(riga, colonna) ? " " : "non ";
        std::cout << "La cella: " << riga << " " << colonna << risposta << "esiste" << std::endl;
        matrix.MapPreOrder(&doubleIt, nullptr);
    }
    break;
    case 2:
    {
        std::cout << "Inizio test su MatrixCSR<double>;" << std::endl;
        lasd::MatrixCSR<double> matrix(dimRow, dimColumn);
        double n = 0.5;
        double acc = 1;
        popolateMatrix(matrix);
        void (*fun)(const double &, void *) = printElement;
        std::cout << "\x1B[33mEseguo la map sulla matrice\033[0m" << std::endl;
        matrix.MapPreOrder(fun, nullptr);
        std::cout << std::endl
                  << "\x1B[33mEseguo la fold sulla matrice\033[0m" << std::endl;
        matrix.FoldPreOrder(&foldSum, &n, &acc);
        std::cout << "\x1B[32mIl risultato della fold e`: \033[0m" << acc << std::endl;
        unsigned long riga, colonna;
        std::cout << "Inserire l'indice di riga: ";
        std::cin >> riga;
        std::cout << "Inserire l'indice della colonna: ";
        std::cin >> colonna;
        std::string risposta = matrix.ExistsCell(riga, colonna) ? " " : "non ";
        std::cout << "La cella: " << riga << " " << colonna << risposta << "esiste" << std::endl;
        matrix.MapPreOrder(&negativePowerOfThree, nullptr);
    }
    break;

    case 3:
    {
        std::cout << "Inizio test su MatrixCSR<std::string>;" << std::endl;
        lasd::MatrixCSR<std::string> matrix(dimRow, dimColumn);
        int n = 5;
        std::string acc = "";
        popolateMatrix(matrix);
        void (*fun)(const std::string &, void *) = printElement;
        std::cout << "\x1B[33mEseguo la map sulla matrice\033[0m" << std::endl;
        matrix.MapPreOrder(fun, nullptr);
        std::cout << std::endl
                  << "\x1B[33mEseguo la fold sulla matrice\033[0m" << std::endl;
        matrix.FoldPreOrder(&foldStringConcat, &n, &acc);
        std::cout << "\x1B[32mIl risultato della fold e`: \033[0m" << acc << std::endl;
        std::cout << "Il risultato della fold e`: " << acc << std::endl;
        unsigned long riga, colonna;
        std::cout << "Inserire l'indice di riga: ";
        std::cin >> riga;
        std::cout << "Inserire l'indice della colonna: ";
        std::cin >> colonna;
        std::string risposta = matrix.ExistsCell(riga, colonna) ? " " : "non ";
        std::cout << "La cella: " << riga << " " << colonna << risposta << "esiste" << std::endl;
        matrix.MapPreOrder(&addString, nullptr);
    }
    break;

    case 0:
    {
        std::cout << "uscita dal menu" << std::endl;
        return;
    }
    default:
        goto scelta;
        break;
    }
}

template <typename Data>
void popolateMatrix(lasd::MatrixCSR<Data> &mat)
{
    if (std::is_same<Data, int>::value)
    {
        for (unsigned long i = 0; i < mat.RowNumber(); ++i)
        {
            for (unsigned long j = 0; j < mat.ColumnNumber(); ++j)
            {
                std::default_random_engine generator(std::random_device{}());
                std::uniform_int_distribution<int> distribution(0, 100);
                mat(i, j) = distribution(generator);
            }
        }
    }
    else if (std::is_same<Data, double>::value)
    {
        for (unsigned long i = 0; i < mat.RowNumber(); ++i)
        {
            for (unsigned long j = 0; j < mat.ColumnNumber(); ++j)
            {
                std::default_random_engine generator(std::random_device{}());
                std::uniform_real_distribution<double> distribution(0.0, 1.0);
                mat(i, j) = distribution(generator);
            }
        }
    }
    else if (std::is_same<Data, std::string>::value)
    {
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> distribution(0, 13);
        for (unsigned long i = 0; i < mat.RowNumber(); ++i)
        {
            for (unsigned long j = 0; j < mat.ColumnNumber(); ++j)
            {
                // mat(i, j) = generateString(distribution(generator));
            }
        }
    }
}