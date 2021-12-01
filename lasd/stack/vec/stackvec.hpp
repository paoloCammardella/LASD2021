
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class StackVec : virtual public Stack<Data>,
                   virtual protected Vector<Data> //estendo Data * perche` risulta piu efficiente in memoria ma piu lenta in esecuzione.
  {                                               // Must extend Stack<Data> and Vector<Data>

  private:
    // ...

  protected:
    using Vector<Data>::size;
    using Vector<Data>::elements;
    unsigned long firstFree = 0;

  public:
    // Default constructor
    StackVec();

    /* ************************************************************************ */

    // Specific constructor
    StackVec(const LinearContainer<Data> &); // A stack obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    StackVec(const StackVec<Data> &);

    // Move constructor
    StackVec(StackVec<Data> &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    ~StackVec();

    /* ************************************************************************ */

    // Copy assignment
    StackVec<Data> &operator=(const StackVec<Data> &);

    // Move assignment
    StackVec<Data> &operator=(StackVec<Data> &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const StackVec<Data> &) const;
    bool operator!=(const StackVec<Data> &) const;

    /* ************************************************************************ */

    // Specific member functions (inherited from Stack)

    void Push(const Data &) override;     // Override Stack member (copy of the value)
    void Push(Data &&) noexcept override; // Override Stack member (move of the value)
    Data &Top() const override;           // Override Stack member (must throw std::length_error when empty)
    void Pop() override;                  // Override Stack member (must throw std::length_error when empty)
    Data TopNPop() override;              // Override Stack member (must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    inline bool Empty() const noexcept
    {
      return (firstFree == 0);
    } // Override Container member

    inline unsigned long Size() const noexcept
    {
      return firstFree;
    }// Override Container member

    void Clear() override; // Override Container member

  protected:
    // Auxiliary member functions

    void Expand();
    void Reduce();
  };

  /* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
