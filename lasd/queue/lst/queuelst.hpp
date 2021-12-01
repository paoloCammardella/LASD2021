
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class QueueLst : virtual public Queue<Data>,
                   virtual protected List<Data>
  { // Must extend Queue<Data> and List<Data>

  private:
    // ...

  protected:
    using List<Data>::size;
    using typename List<Data>::Node;
    Node *head = nullptr;
    Node *rear = nullptr;

  public:
    // Default constructor
    QueueLst();

    /* ************************************************************************ */

    // Specific constructor
    QueueLst(const LinearContainer<Data>&); // A queue obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    QueueLst(const QueueLst<Data> &);

    // Move constructor
    QueueLst(QueueLst<Data> &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    ~QueueLst();

    /* ************************************************************************ */

    // Copy assignment
    QueueLst<Data> &operator=(const QueueLst<Data> &);

    // Move assignment
    QueueLst<Data> &operator=(QueueLst<Data> &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const QueueLst<Data> &) const;
    bool operator!=(const QueueLst<Data> &) const;

    /* ************************************************************************ */

    // Specific member functions (inherited from Queue)

    void Enqueue(const Data &) override;     // Override Queue member (copy of the value)
    void Enqueue(Data &&) noexcept override; // Override Queue member (move of the value)
    Data &Head() const override;                   // Override Queue member (must throw std::length_error when empty)
    void Dequeue() override;                 // Override Queue member (must throw std::length_error when empty)
    Data HeadNDequeue() override;            // Override Queue member (must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member
  };

  /* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
