
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../list/list.hpp"
#include "../../queue/queue.hpp" 
#include "../../stack/stack.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data>{ // Must extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  struct NodeLnk : virtual public BinaryTree<Data>::Node{ // Must extend Node

  private:
  protected:

  public:
    Data data;
    NodeLnk* left = nullptr;
    NodeLnk* right = nullptr;

      inline ~NodeLnk(){
        if(HasLeftChild()){
          delete left;
        }
        if(HasRightChild()){
          delete right;
        }
      }

      /* ********************************************************************** */
      inline NodeLnk(const Data& dat){
        data = dat;
        left = right = nullptr;
      }

      inline NodeLnk(Data&& dat){
        data = std::move(dat);
        left = right = nullptr;
      }
      
      // Copy assignment
      inline NodeLnk& operator=(const NodeLnk& node){
        data = node.data;
        left = node.left;
        right = node.right;

        return *this;
      }

      // Move assignment
      inline NodeLnk& operator=(NodeLnk&& node) noexcept{
        std::swap(data ,node.data);
        std::swap(left ,node.left);
        std::swap(right ,node.right);

        return *this;
      }

      /* ********************************************************************** */

      // Specific member functions

      inline Data& Element() noexcept{
        return data;
      }

      inline const Data& Element() const noexcept{
        return data;
      }
      
      inline bool IsLeaf() const noexcept{
        return (!HasLeftChild() && !HasRightChild());
      }

      inline bool HasLeftChild() const noexcept{
        return (left != nullptr);
      }

      inline bool HasRightChild() const noexcept{
        return (right != nullptr);
      }
      
      inline NodeLnk& LeftChild() const{
        if(left != nullptr)
          return *left;
        else
          throw std::length_error("Non c'e` figlio sinistro");
      }

      inline NodeLnk& RightChild() const{
        if(right != nullptr)
          return *right;
        else
          throw std::length_error("Non c'e` figlio destro");
      }
    friend class BinaryTreeLnk<Data>;
  };

  NodeLnk* root = nullptr;

public:


  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk &operator=(const BinaryTreeLnk &);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
   inline bool operator==(const BinaryTreeLnk& Btlnk) const{
    return (Root() == Btlnk.Root());
  }

   inline bool operator!=(const BinaryTreeLnk& Btlnk) const{
    return !(Root() == Btlnk.Root());
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  inline NodeLnk& Root() const override{
    if(size > 0)
      return *root;
    else
      throw std::length_error("Albero vuoto");
  }
  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  void BTFromContainer(unsigned long , NodeLnk*, const LinearContainer<Data>&);
  void TreeCopy(const NodeLnk&, NodeLnk*);

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
