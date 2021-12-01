
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Stack : virtual public Container{ // Must extend Container

  private:
    // ...

  protected:
  public:
    // Destructor
    virtual ~Stack() = default;

    /* ************************************************************************ */

    // Copy assignment
    virtual Stack &operator=(const Stack &) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual Stack &operator=(Stack &&) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(const Stack &) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(const Stack &) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    virtual void Push(const Data &) = 0;     // Copy of the value
    virtual void Push(Data &&) noexcept = 0; // Move of the value
    virtual Data &Top() const = 0;           // (concrete function must throw std::length_error when empty)
    virtual void Pop() = 0;                  // (concrete function must throw std::length_error when empty)
    virtual Data TopNPop() = 0;              // (concrete function must throw std::length_error when empty)
  };

  /* ************************************************************************** */

}

#endif
