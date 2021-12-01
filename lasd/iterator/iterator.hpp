
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Iterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  virtual Iterator& operator=(const Iterator&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual Iterator& operator=(Iterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const Iterator&) const = delete; // Comparison of abstract types might not be possible.
  virtual bool operator!=(const Iterator&) const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& operator*() const = 0; // (concrete function must throw std::out_of_range when terminated)

  virtual bool Terminated() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator : virtual public Iterator<Data>{ // Must extend Iterator

private:

  // ...

protected:

  // ...

public:

  // Destructor
  ~ForwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
   ForwardIterator& operator=(const ForwardIterator&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
   ForwardIterator& operator=(ForwardIterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
   bool operator==(const ForwardIterator&) const = delete; // Comparison of abstract types might not be possible.
   bool operator!=(const ForwardIterator&) const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual ForwardIterator& operator++() = 0; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BackwardIterator : virtual public Iterator<Data>{ // Must extend Iterator

private:

  // ...

protected:

  // ...

public:

  // Destructor
   ~BackwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
   BackwardIterator& operator=(const BackwardIterator&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
   BackwardIterator& operator=(BackwardIterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
   bool operator==(const BackwardIterator&) const = delete; // Comparison of abstract types might not be possible.
   bool operator!=(const BackwardIterator&) const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual BackwardIterator& operator--() = 0; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BidirectionalIterator : virtual public Iterator<Data>, virtual public BackwardIterator<Data>{ // Must extend ForwardIterator and BackwardIterator

private:

  // ...

protected:

  // ...

public:

  // Destructor
  ~BidirectionalIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
   BidirectionalIterator& operator=(const BidirectionalIterator&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
   BidirectionalIterator& operator=(BidirectionalIterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
   bool operator==(const BidirectionalIterator&) const = delete; // Comparison of abstract types might not be possible.
   bool operator!=(const BidirectionalIterator&) const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  bool Terminated() override; // Override Iterator member

  virtual bool ForwardTerminated() const noexcept = 0; // (concrete function should not throw exceptions)

  virtual bool BackwardTerminated() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif
