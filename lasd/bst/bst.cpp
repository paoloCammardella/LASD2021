
namespace lasd
{

    /* ****************************Costruttori e operatori di uguaglianza**************************** */
    template <typename Data>
    BST<Data>::BST(const LinearContainer<Data> &containter)
    {
        for (unsigned long i = 0; i < containter.Size(); ++i)
        {
            Insert(containter[i]);
        }
        size = containter.Size();
    }

    // Copy constructor
    template <typename Data>
    BST<Data>::BST(const BST &bst) : BinaryTreeLnk<Data>::BinaryTreeLnk(bst) {}

    // Move constructor
    template <typename Data>
    BST<Data>::BST(BST &&bst) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(bst)) {}

    template <typename Data>
    BST<Data> &BST<Data>::operator=(const BST &BST)
    {
        BinaryTreeLnk<Data>::operator=(BST);

        return *this;
    }

    template <typename Data>
    BST<Data> &BST<Data>::operator=(BST &&BST) noexcept
    {
        BinaryTreeLnk<Data>::operator=(std::move(BST));

        return *this;
    }

    template <typename Data>
    bool BST<Data>::operator==(const BST &BST) const
    {
        if (size == BST.size)
        {
            BTInOrderIterator<Data> iterator(*this);
            BTInOrderIterator<Data> iterator2(BST);

            while (!iterator.Terminated())
            {
                if (*iterator != *iterator2)
                {
                    return false;
                }
                ++iterator;
                ++iterator2;
            }
            return true;
        }
        return false;
    }

    template <typename Data>
    bool BST<Data>::operator!=(const BST &BST) const
    {
        return !(*this == BST);
    }

    /* *********************************Funzioni specifiche************************************** */

    template <typename Data>
    void BST<Data>::Insert(const Data &dato)
    {
        NodeLnk *&pointer = FindPointerTo(root, dato);
        if (pointer == nullptr)
        {
            pointer = new NodeLnk(dato);
            ++size;
        }
    }

    template <typename Data>
    void BST<Data>::Insert(Data &&dato) noexcept
    {
        NodeLnk *&pointer = FindPointerTo(root, dato);
        if (pointer == nullptr)
        {
            pointer = new NodeLnk(std::move(dato));
            ++size;
        }
    }

    template <typename Data>
    void BST<Data>::Remove(const Data &dato)
    {
        delete Detach(FindPointerTo(root, dato));
    }

    template <typename Data>
    const Data &BST<Data>::Min() const
    {
        if (root != nullptr)
        {
            return FindPointerToMin(root)->Element();
        }
        else
        {
            throw std::length_error("Minimo non trovato");
        }
    }

    template <typename Data>
    Data BST<Data>::MinNRemove()
    {
        if (root != nullptr)
        {
            return DataNDelete(DetachMin(root));
        }
        else
        {
            throw std::length_error("Minimo non trovato");
        }
    }

    template <typename Data>
    void BST<Data>::RemoveMin()
    {
        if (root != nullptr)
        {
            delete DetachMin(root);
        }
        else
        {
            throw std::length_error("Minimo non trovato");
        }
    }

    template <typename Data>
    const Data &BST<Data>::Max() const
    {
        if (root != nullptr)
        {
            return FindPointerToMax(root)->Element();
        }
        else
        {
            throw std::length_error("Massimo non trovato");
        }
    }

    template <typename Data>
    Data BST<Data>::MaxNRemove()
    {
        if (root != nullptr)
        {
            return DataNDelete(DetachMax(root));
        }
        else
        {
            throw std::length_error("Massimo non trovato");
        }
    }

    template <typename Data>
    void BST<Data>::RemoveMax()
    {
        if (root != nullptr)
        {
            delete DetachMax(root);
        }
        else
        {
            throw std::length_error("Massimo non trovato");
        }
    }

    template <typename Data>
    const Data &BST<Data>::Predecessor(const Data &dato) const
    {
        NodeLnk *const *pointer = FindPointerToPredecessor(root, dato);
        if (pointer != nullptr)
        {
            return (*pointer)->data;
        }
        else
        {
            throw std::length_error("Predecessor non trovato");
        }
    }

    template <typename Data>
    Data BST<Data>::PredecessorNRemove(const Data &dato)
    {
        NodeLnk **pointer = FindPointerToPredecessor(root, dato);
        if (pointer != nullptr)
        {
            return DataNDelete(Detach(*pointer));
        }
        else
        {
            throw std::length_error("Predecessor non trovato");
        }
    }

    template <typename Data>
    void BST<Data>::RemovePredecessor(const Data &dato)
    {
        NodeLnk **pointer = FindPointerToPredecessor(root, dato);
        if (pointer != nullptr)
        {
            delete Detach(*pointer);
        }
        else
        {
            throw std::length_error("Predecessor non trovato");
        }
    }

    template <typename Data>
    const Data &BST<Data>::Successor(const Data &dato) const
    {
        NodeLnk *const *pointer = FindPointerToSuccessor(root, dato);
        if (pointer != nullptr)
        {
            return (*pointer)->Element();
        }
        else
        {
            throw std::length_error("Successor non trovato");
        }
    }

    template <typename Data>
    Data BST<Data>::SuccessorNRemove(const Data &dato)
    {
        NodeLnk **pointer = FindPointerToSuccessor(root, dato);
        if (pointer != nullptr)
        {
            return DataNDelete(Detach(*pointer));
        }
        else
        {
            throw std::length_error("Successor non trovato");
        }
    }

    template <typename Data>
    void BST<Data>::RemoveSuccessor(const Data &dato)
    {
        NodeLnk **pointer = FindPointerToSucccessor(root, dato);
        if (pointer != nullptr)
        {
            delete Detach(*pointer);
        }
        else
        {
            throw std::length_error("Successor non trovato");
        }
    }

    template <typename Data>
    bool BST<Data>::Exists(const Data &dato) const noexcept
    {
        return (FindPointerTo(root, dato) != nullptr);
    }

    template <typename Data>
    Data BST<Data>::DataNDelete(NodeLnk *pointer)
    {
        Data dato{};
        std::swap(dato, pointer->Element());
        delete pointer;
        return dato;
    }

    /* *********************************************Detach********************************************** */
    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::Detach(NodeLnk *&node) noexcept
    {
        if (node != nullptr)
        {
            if (!node->HasLeftChild())
            {
                return SkipOnRight(node);
            }
            else if (!node->HasRightChild())
            {
                return SkipOnLeft(node);
            }
            else
            {
                NodeLnk *max = DetachMax(node->left);
                std::swap(node->Element(), max->Element());
                return max;
            }
        }
        return nullptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::DetachMin(NodeLnk *&node) noexcept
    {
        return SkipOnRight(FindPointerToMin(node));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::DetachMax(NodeLnk *&node) noexcept
    {
        return SkipOnLeft(FindPointerToMax(node));
    }

    /* *********************************************SkipOn********************************************** */
    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::SkipOnLeft(NodeLnk *&node) noexcept
    {
        NodeLnk *sLeft;
        if (node != nullptr)
        {
            std::swap(sLeft, node->left);
            std::swap(sLeft, node);
            --size;

            return sLeft;
        }

        return nullptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::SkipOnRight(NodeLnk *&node) noexcept
    {
        NodeLnk *sRight;
        if (node != nullptr)
        {
            std::swap(sRight, node->right);
            std::swap(sRight, node);
            --size;

            return sRight;
        }

        return nullptr;
    }

    /* ****************************************Ricerca puntatore**************************************** */
    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerToMin(NodeLnk *&node) noexcept
    {
        return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(node));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerToMin(NodeLnk *const &node) const noexcept
    {
        NodeLnk *const *pointer = &node;
        NodeLnk *curr = node;

        if (curr != nullptr)
        {
            while (curr->HasLeftChild())
            {
                pointer = &curr->left;
                curr = curr->left;
            }
        }
        return *pointer;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerToMax(NodeLnk *&node) noexcept
    {
        return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerToMax(NodeLnk *const &node) const noexcept
    {
        NodeLnk *const *pointer = &node;
        NodeLnk *curr = node;

        if (curr != nullptr)
        {
            while (curr->HasRightChild())
            {
                pointer = &curr->right;
                curr = curr->right;
            }
        }
        return *pointer;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerTo(NodeLnk *&node, const Data &dato) noexcept
    {
        return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerTo(node, dato));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerTo(NodeLnk *const &node, const Data &dato) const noexcept
    {
        NodeLnk *curr = node;
        NodeLnk *const *ptr = &node;
        if (curr != nullptr)
        {
            if (dato != curr->data)
            {
                if (dato < curr->data)
                    return FindPointerTo(curr->left, dato);
                else if (dato > curr->data)
                    return FindPointerTo(curr->right, dato);
            }
        }
        return *ptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk **BST<Data>::FindPointerToPredecessor(NodeLnk *&node, const Data &dato) noexcept
    {
        return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, dato));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const *BST<Data>::FindPointerToPredecessor(NodeLnk *const &node, const Data &dato) const noexcept
    {
        NodeLnk *const *predecessorPointer = nullptr;
        NodeLnk *const *curr = &node;

        while ((*curr) != nullptr && (*curr)->data != dato)
        {
            if (dato > (*curr)->data)
            {
                predecessorPointer = curr;
                curr = &(*curr)->right;
            }
            else if (dato < (*curr)->data)
            {
                curr = &(*curr)->left;
            }
        }

        if ((*curr) != nullptr && (*curr)->left != nullptr)
        {
            return &FindPointerToMax((*curr)->left);
        }

        return predecessorPointer;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk **BST<Data>::FindPointerToSuccessor(NodeLnk *&node, const Data &dato) noexcept
    {
        return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, dato));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const *BST<Data>::FindPointerToSuccessor(NodeLnk *const &node, const Data &dato) const noexcept
    {
        NodeLnk *const *successorPointer = nullptr;
        NodeLnk *const *curr = &node;

        while ((*curr) != nullptr && (*curr)->data != dato)
        {
            if (dato > (*curr)->data)
            {
                curr = &(*curr)->right;
            }
            else if (dato < (*curr)->data)
            {
                successorPointer = curr;
                curr = &(*curr)->left;
            }
        }

        if ((*curr) != nullptr && (*curr)->right != nullptr)
        {
            return &FindPointerToMin((*curr)->right);
        }

        return successorPointer;
    }
}