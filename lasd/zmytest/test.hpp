
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../matrix/matrix.hpp"
#include "../matrix/vec/matrixvec.hpp"
#include "../matrix/csr/matrixcsr.hpp"

/* *****************************************Matrix***************************************** */
void matrixTest();
/* ****************************************MatrixVec**************************************** */
void matrixVecTest();

template <typename Data>
void matrixVec(lasd::MatrixVec<Data>&);

template <typename Data>
void popolateMatrix(lasd::MatrixVec<Data>& );
std::string generateString(unsigned long);

template <typename Data>
void printElement(const Data&, void* _);

void foldProduct(const int&, const void*, void*);
void foldSum(const double &, const void *, void *);
void foldStringConcat(const std::string &, const void *, void *);
void doubleIt(int&, void*_);
void negativePowerOfThree(double&, void*_);
void addString(std::string&, void*);

void matrixCSRTest();

template <typename Data>
void popolateMatrix(lasd::MatrixCSR<Data>& );
/* ***************************************Test******************************************** */
void mytest();
/* ************************************************************************** */

#endif
