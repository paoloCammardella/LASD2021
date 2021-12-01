
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../iterator/iterator.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../stack/lst/stacklst.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BinaryTree : virtual public InOrderMappableContainer<Data>,
                     virtual public InOrderFoldableContainer<Data>,
                     virtual public BreadthMappableContainer<Data>,
                     virtual public BreadthFoldableContainer<Data>
  { // Must extend InOrder/BreadthMappableContainer<Data> and InOrder/BreadthFoldableContainer<Data>

  private:
    // ...

  protected:
    using BreadthMappableContainer<Data>::size;

  public:
    struct Node
    {

    private:
    protected:
      // Comparison operators
      virtual bool operator==(const Node &) const noexcept; // Comparison of abstract types is possible, but should not be visible.
      virtual bool operator!=(const Node &) const noexcept; // Comparison of abstract types is possible, but should not be visible.

    public:
      friend class BinaryTree<Data>;

      /* ********************************************************************** */

      // Destructor
      virtual ~Node() = default;

      /* ********************************************************************** */

      // Copy assignment
      virtual Node &operator=(const Node &) = delete; // Copy assignment of abstract types should not be possible.

      // Move assignment
      virtual Node &operator=(Node &&) noexcept = delete; // Move assignment of abstract types should not be possible.

      /* ********************************************************************** */

      // Specific member functions

      virtual inline Data &Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)

      virtual const Data &Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

      virtual bool IsLeaf() const noexcept = 0; // (concrete function should not throw exceptions)

      virtual bool HasLeftChild() const noexcept = 0;  // (concrete function should not throw exceptions)
      virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

      virtual Node &LeftChild() const = 0;  // (concrete function must throw std::out_of_range when not existent)
      virtual Node &RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    };

    /* ************************************************************************ */

    // Destructor
    ~BinaryTree() = default;

    /* ************************************************************************ */

    // Copy assignment
    virtual BinaryTree &operator=(const BinaryTree &) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual BinaryTree &operator=(BinaryTree &&) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(const BinaryTree &) const noexcept; // Comparison of abstract binary tree is possible.
    virtual bool operator!=(const BinaryTree &) const noexcept; // Comparison of abstract binary tree is possible.

    /* ************************************************************************ */

    // Specific member functions

    virtual Node &Root() const = 0; // (concrete function must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFunctor;

    void MapPreOrder(const MapFunctor, void *) override;  // Override MappableContainer member
    void MapPostOrder(const MapFunctor, void *) override; // Override MappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    using typename FoldableContainer<Data>::FoldFunctor;

    void FoldPreOrder(const FoldFunctor, const void *, void *) const override;  // Override FoldableContainer member
    void FoldPostOrder(const FoldFunctor, const void *, void *) const override; // Override FoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from InOrderMappableContainer)

    void MapInOrder(const MapFunctor, void *) override; // Override InOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from InOrderFoldableContainer)

    void FoldInOrder(const FoldFunctor, const void *, void *) const override; // Override InOrderFoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthMappableContainer)

    void MapBreadth(const MapFunctor, void *) override; // Override BreadthMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthFoldableContainer)

    void FoldBreadth(const FoldFunctor, const void *, void *) const override; // Override BreadthFoldableContainer member
  protected:
    // Auxiliary member functions (for MappableContainer)

    void MapPreOrder(const MapFunctor, void *, Node *);  // Accessory function executing from one node of the tree
    void MapPostOrder(const MapFunctor, void *, Node *); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for FoldableContainer)

    void FoldPreOrder(const FoldFunctor, const void *, void *, Node *) const;  // Accessory function executing from one node of the tree
    void FoldPostOrder(const FoldFunctor, const void *, void *, Node *) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for InOrderMappableContainer)

    void MapInOrder(const MapFunctor, void *, Node *); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for InOrderFoldableContainer)

    void FoldInOrder(const FoldFunctor, const void *, void *, Node *) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for BreadthMappableContainer)

    void MapBreadth(const MapFunctor, void *, Node *); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for BreadthFoldableContainer)

    void FoldBreadth(const FoldFunctor, const void *, void *, Node *) const; // Accessory function executing from one node of the tree
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTPreOrderIterator : virtual public ForwardIterator<Data>
  { // Must extend ForwardIterator<Data>

  private:
  protected:
    typename BinaryTree<Data>::Node *curr;
    StackLst<typename BinaryTree<Data>::Node *> savedNodes;

  public:
    // Specific constructors
    BTPreOrderIterator(const BinaryTree<Data> &BT)
    {
      curr = &BT.Root();
    } // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    inline BTPreOrderIterator(const BTPreOrderIterator &IT)
    {
      curr = IT.curr;
      savedNodes = IT.savedNodes;
    }

    // Move constructor
    inline BTPreOrderIterator(BTPreOrderIterator &&IT) noexcept
    {
      std::swap(curr, IT.curr);
      std::swap(savedNodes, IT.savedNodes);
    }

    /* ************************************************************************ */

    // Destructor
    ~BTPreOrderIterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    BTPreOrderIterator &operator=(const BTPreOrderIterator &IT)
    {
      curr = IT.curr;
      savedNodes = IT.savedNodes;

      return *this;
    }

    // Move assignment
    inline BTPreOrderIterator &operator=(BTPreOrderIterator &&IT) noexcept
    {
      std::swap(curr, IT.curr);
      std::swap(savedNodes, IT.savedNodes);

      return *this;
    }

    /* ************************************************************************ */

    // Comparison operators
    inline bool operator==(const BTPreOrderIterator &IT) const
    {
      return (curr == IT.curr && savedNodes == IT.savedNodes);
    }

    inline bool operator!=(const BTPreOrderIterator &IT) const
    {
      return !(*this == IT);
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    inline Data &operator*() const override
    {
      if (Terminated())
        throw std::length_error("Albero terminato");
      else
        return curr->Element();
    } // (throw std::out_of_range when terminated)

    bool Terminated() const noexcept override
    {
      return (curr == nullptr);
    } // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    BTPreOrderIterator &operator++(); // (throw std::out_of_range when terminated)
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTPostOrderIterator : virtual public ForwardIterator<Data>
  { // Must extend ForwardIterator<Data>

  private:
  protected:
    typename BinaryTree<Data>::Node *curr;
    StackLst<typename BinaryTree<Data>::Node *> savedNodes;

  public:
    // Specific constructors
    inline BTPostOrderIterator(const BinaryTree<Data> &BT)
    {
      if(BT.Size() > 0){
        curr = mostLeftLeaf(&BT.Root());
      }
    } // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    inline BTPostOrderIterator(const BTPostOrderIterator &IT)
    {
      curr = IT.curr;
      savedNodes = IT.savedNodes;
    }

    // Move constructor
    inline BTPostOrderIterator(BTPostOrderIterator &&IT) noexcept
    {
      std::swap(curr, IT.curr);
      std::swap(savedNodes, IT.savedNodes);
    }

    /* ************************************************************************ */

    // Destructor
    ~BTPostOrderIterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    inline BTPostOrderIterator &operator=(const BTPostOrderIterator &IT)
    {
      curr = IT.curr;
      savedNodes = IT.savedNodes;

      return *this;
    }

    // Move assignment
    inline BTPostOrderIterator &operator=(BTPostOrderIterator &&IT) noexcept
    {
      std::swap(curr, IT.curr);
      std::swap(savedNodes, IT.savedNodes);

      return *this;
    }

    /* ************************************************************************ */

    // Comparison operators
    inline bool operator==(const BTPostOrderIterator &IT) const
    {
      return (curr == IT.curr && savedNodes == IT.savedNodes);
    }

    inline bool operator!=(const BTPostOrderIterator &IT) const
    {
      return !(*this == IT);
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    inline Data &operator*() const override
    {
      if (Terminated())
        throw std::length_error("Albero terminato");
      else
        return curr->Element();
    } // (throw std::out_of_range when terminated)

    inline bool Terminated() const noexcept override
    {
      return (curr == nullptr);
    } // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    BTPostOrderIterator &operator++() override; // (throw std::out_of_range when terminated)

    //Auxiliary

    typename BinaryTree<Data>::Node *mostLeftLeaf(typename BinaryTree<Data>::Node *node)
    {

      if (node->HasLeftChild())
      {
        savedNodes.Push(node);
        node = mostLeftLeaf(&node->LeftChild());
      }

      if (node->HasRightChild())
      {
        savedNodes.Push(node);
        node = mostLeftLeaf(&node->RightChild());
      }
      return node;
    }
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTInOrderIterator : virtual public ForwardIterator<Data>
  { // Must extend ForwardIterator<Data>

  private:
  protected:
    typename BinaryTree<Data>::Node *curr;
    StackLst<typename BinaryTree<Data>::Node *> savedNodes;

  public:
    // Specific constructors
    inline BTInOrderIterator(const BinaryTree<Data> &BT)
    {
      curr = mostLeftNode(&BT.Root());
    } // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    inline BTInOrderIterator(const BTInOrderIterator &IT)
    {
      curr = IT.curr;
      savedNodes = IT.savedNodes;
    }

    // Move constructor
    inline BTInOrderIterator(BTInOrderIterator &&IT) noexcept
    {
      std::swap(curr, IT.curr);
      std::swap(savedNodes, IT.savedNodes);
    }

    /* ************************************************************************ */

    // Destructor
    ~BTInOrderIterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    inline BTInOrderIterator &operator=(const BTInOrderIterator &IT)
    {
      curr = IT.curr;
      savedNodes = IT.savedNodes;

      return *this;
    }

    // Move assignment
    inline BTInOrderIterator &operator=(BTInOrderIterator &&IT) noexcept
    {
      std::swap(curr, IT.curr);
      std::swap(savedNodes, IT.savedNodes);

      return *this;
    }

    /* ************************************************************************ */

    // Comparison operators
    inline bool operator==(const BTInOrderIterator &IT) const
    {

      return (curr == IT.curr && savedNodes == IT.savedNodes);
    }

    inline bool operator!=(const BTInOrderIterator &IT) const
    {
      return !(*this == IT);
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    inline Data &operator*() const override
    {
      if (Terminated())
        throw std::length_error("Albero terminato");
      else
        return curr->Element();
    } // (throw std::out_of_range when terminated)

    inline bool Terminated() const noexcept override
    {
      return (curr == nullptr);
    } // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    BTInOrderIterator &operator++(); // (throw std::out_of_range when terminated)

        //Auxiliary
            typename BinaryTree<Data>::Node *mostLeftNode(typename BinaryTree<Data>::Node *node)
    {
      if (node->HasLeftChild())
      {
        savedNodes.Push(node);
        node = mostLeftNode(&node->LeftChild());
      }
      return node;
    }
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTBreadthIterator : virtual public ForwardIterator<Data>
  { // Must extend ForwardIterator<Data>

  private:
  protected:
    typename BinaryTree<Data>::Node *curr;
    QueueLst<typename BinaryTree<Data>::Node *> savedNodes;

  public:
    // Specific constructors
    inline BTBreadthIterator(BinaryTree<Data> &BT)
    {
      curr = &BT.Root();
    } // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    inline BTBreadthIterator(const BTBreadthIterator &IT)
    {
      curr = IT.curr;
      savedNodes = IT.savedNodes;
    }

    // Move constructor
    inline BTBreadthIterator(BTBreadthIterator &&IT) noexcept
    {
      std::swap(curr, IT.curr);
      std::swap(savedNodes, IT.savedNodes);
    }

    /* ************************************************************************ */

    // Destructor
    ~BTBreadthIterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    inline BTBreadthIterator &operator=(const BTBreadthIterator &IT)
    {
      curr = IT.curr;
      savedNodes = IT.savedNodes;
    }

    // Move assignment
    inline BTBreadthIterator &operator=(BTBreadthIterator &&IT) noexcept
    {

      std::swap(curr, IT.curr);
      std::swap(savedNodes, IT.savedNodes);

      return *this;
    }

    /* ************************************************************************ */

    // Comparison operators
    inline bool operator==(const BTBreadthIterator &IT) const
    {
      return (curr == IT.curr && savedNodes == IT.savedNodes);
    }

    inline bool operator!=(const BTBreadthIterator &IT) const
    {
      return !(*this == IT);
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    inline Data &operator*() const override
    {
      if (Terminated())
        throw std::length_error("Albero terminato");
      else
        return curr->Element();
    } // (throw std::out_of_range when terminated)

    inline bool Terminated() const noexcept override
    {
      return (curr == nullptr);
    } // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    BTBreadthIterator &operator++() override; // (throw std::out_of_range when terminated)


  };

  /* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
