
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class QueueVec : virtual public Queue<Data>,
                   virtual protected Vector<Data>
  { // Must extend Queue<Data> and Vector<Data>

  private:
    // ...

  protected:
    using Vector<Data>::size;
    using Vector<Data>::elements;
    unsigned long front = 0,  rear = 0;

  public:
    // Default constructor
    QueueVec();

    /* ************************************************************************ */

    // Specific constructor
    QueueVec(const LinearContainer<Data> &); // A queue obtained from a LinearContainer
    /* ************************************************************************ */
    // Copy constructor
    QueueVec(const QueueVec<Data> &);

    // Move constructor
    QueueVec(QueueVec<Data> &&) noexcept;
    /* ************************************************************************ */

    // Destructor
    ~QueueVec();
    /* ************************************************************************ */

    // Copy assignment
    QueueVec<Data> &operator=(const QueueVec<Data> &);

    // Move assignment
    QueueVec<Data> &operator=(QueueVec<Data> &&) noexcept;
    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const QueueVec<Data> &) const;
    bool operator!=(const QueueVec<Data> &) const;

    /* ************************************************************************ */

    // Specific member functions (inherited from Queue)

    void Enqueue(const Data &) override;     // Override Queue member (copy of the value)
    void Enqueue(Data &&) noexcept override; // Override Queue member (move of the value)
    Data &Head() const override;             // Override Queue member (must throw std::length_error when empty)
    void Dequeue() override;                 // Override Queue member (must throw std::length_error when empty)
    Data HeadNDequeue() override;            // Override Queue member (must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    inline bool Empty() const noexcept
    {
      return (Size() == 0);
    }; // Override Container member

    inline unsigned long Size() const noexcept
    {
      return (((rear + (size + 1)) - front + 1) % (size + 1));
    }; // Override Container member

    void Clear() override; // Override Container member

  protected:
    // Auxiliary member functions

    void Expand();
    void Reduce();
    void SwapVectors(const unsigned long &);
  };

  /* ************************************************************************** */
}

#include "queuevec.cpp"

#endif
