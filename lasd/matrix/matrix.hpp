
#ifndef MATRIX_HPP
#define MATRIX_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Matrix : virtual public MappableContainer<Data>,
               virtual public FoldableContainer<Data>{ // Must extend MappableContainer<Data> and FoldableContainer<Data>

private:

  // ...

protected:

  unsigned long rowsNumber = 0;
  unsigned long columnsNumber = 0;
  using MappableContainer<Data>::size;

public:

  // Destructor
  ~Matrix() = default;

  /* ************************************************************************ */

  // Copy assignment
  Matrix& operator=(const Matrix&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Matrix& operator=(Matrix&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const Matrix&) const noexcept = delete; // Comparison of abstract types might not be possible.
  virtual bool operator!=(const Matrix&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  unsigned long inline RowNumber() const noexcept{
    return rowsNumber;
  } // (concrete function should not throw exceptions)
  unsigned long inline ColumnNumber() const noexcept{
    return columnsNumber;
  } // (concrete function should not throw exceptions)

  virtual void RowResize(const unsigned long) = 0;
  virtual void ColumnResize(const unsigned long) = 0;

  virtual bool inline ExistsCell(const unsigned long row, const unsigned long col) const noexcept{
    return (row < rowsNumber && col < columnsNumber);
  } // (concrete function should not throw exceptions)

  virtual Data& operator()(const unsigned long, const unsigned long) = 0; // Mutable access to the element (concrete function should throw exceptions only when out of range)
  virtual const Data& operator()(const unsigned long, const unsigned long) const = 0; // Immutable access to the element (concrete function should throw exceptions when not present)

};

/* ************************************************************************** */

}

#include "matrix.cpp"

#endif
