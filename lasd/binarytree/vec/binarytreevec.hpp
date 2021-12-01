
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BinaryTreeVec : virtual public BinaryTree<Data>
  { // Must extend BinaryTree<Data>

  private:
    // ...

  protected:
    struct NodeVec : virtual public BinaryTree<Data>::Node
    { // Must extend Node

    private:
    protected:
      Data data;
      unsigned long index = 0;
      Vector<NodeVec *> *ref = nullptr;
    public:

      friend class BinaryTreeVec<Data>;

      NodeVec(unsigned long, Vector<NodeVec *> *, const Data &);
      NodeVec(unsigned long, Vector<NodeVec *> *, Data &&) noexcept;

      /* ********************************************************************** */

      // Copy assignment
      NodeVec &operator=(const NodeVec &);

      // Move assignment
      NodeVec &operator=(NodeVec &&) noexcept;

      /* ********************************************************************** */
      // bool operator==(const NodeVec &) const;
      // bool operator!=(const NodeVec &) const;

      // Specific member functions

      inline Data &Element() noexcept
      {
        return data;
      }

      inline const Data &Element() const noexcept
      {
        return data;
      }

      inline bool IsLeaf() const noexcept
      {
        return (!HasLeftChild() && !HasRightChild());
      }

      inline bool HasLeftChild() const noexcept
      {
        if((index * 2) + 1 < ref->Size()){
          if((*ref)[(index * 2) + 1] != nullptr)
            return true;
        }
        return false;
      }

      inline bool HasRightChild() const noexcept
      {

        if((index * 2) + 2 < ref->Size()){
          if((*ref)[(index * 2) + 2] != nullptr)
            return true;
        }
        return false;
      }

      inline NodeVec &LeftChild() const
      {
        if (index * 2 + 1 < ref->Size())
          return *(*ref)[index * 2 + 1];
        else
          throw std::length_error("Non c'e` figlio sinistro");
      }

      inline NodeVec &RightChild() const
      {
        if (index * 2 + 2 < ref->Size())
          return *(*ref)[index * 2 + 2];
        else
          throw std::length_error("Non c'e` figlio destro");
      }

    };

    using BinaryTree<Data>::size;
    Vector<NodeVec *> elements;

  public:
    // Default constructor
    BinaryTreeVec() = default;

    /* ************************************************************************ */

    // Specific constructors
    BinaryTreeVec(const LinearContainer<Data> &); // A binary tree obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    BinaryTreeVec(const BinaryTreeVec &);

    // Move constructor
    BinaryTreeVec(BinaryTreeVec &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    ~BinaryTreeVec();

    /* ************************************************************************ */

    // Copy assignment
    BinaryTreeVec &operator=(const BinaryTreeVec &);

    // Move assignment
    BinaryTreeVec &operator=(BinaryTreeVec &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BinaryTreeVec &) const;
    bool operator!=(const BinaryTreeVec &) const;

    /* ************************************************************************ */

    // Specific member functions (inherited from BinaryTree)

    inline NodeVec &Root() const override
    {
      if (size > 0)
        return *elements[0];
      else
        throw std::length_error("L'albero e` vuoto");
    } // Override BinaryTree member (throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    inline void Clear() override
    {
      if(size > 0){
        for (unsigned long i = 0; i < size; ++i)
        {
          delete elements[i];
          elements[i] = nullptr;
        }
        size = 0;
      }
    } // Override Container member
  };

  /* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
