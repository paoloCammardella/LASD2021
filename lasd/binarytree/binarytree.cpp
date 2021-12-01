
#include "binarytree.hpp"

namespace lasd
{

    /* ************************************************************************** */

    /* ********************************Node************************************** */
    template <typename Data>
    bool BinaryTree<Data>::Node::operator==(const Node &comp) const noexcept
    {

        if (Element() == comp.Element())
        {
            if (HasLeftChild() != comp.HasLeftChild() && HasRightChild() != comp.HasRightChild())
            {
                return false;
            }
            else
            {
                if (HasLeftChild())
                {
                    return (LeftChild() == comp.LeftChild());
                }
                if (HasRightChild())
                {
                    return (RightChild() == comp.RightChild());
                }
                return true;
            }
        }
        return false;
    }

    template <typename Data>
    bool BinaryTree<Data>::Node::operator!=(const Node &comp) const noexcept
    {
        return !(*this == comp);
    }

    /* ******************************BinaryTree********************************** */
    template <typename Data>
    bool BinaryTree<Data>::operator==(const BinaryTree &BT) const noexcept
    {
        if(size == BT.size){
            if (Root() == BT.Root())
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        return false;
    }

    template <typename Data>
    bool BinaryTree<Data>::operator!=(const BinaryTree &BT) const noexcept
    {
        return !(*this == BT);
    }

    template <typename Data>
    void BinaryTree<Data>::MapPreOrder(const MapFunctor mf, void *par)
    {
        if (size > 0)
        {
            MapPreOrder(mf, par, &Root());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapPreOrder(const MapFunctor mf, void *par, Node *node)
    {

        if (node != nullptr)
        {
            mf(node->Element(), par);

            if (node->HasLeftChild())
                MapPreOrder(mf, par, &(node->LeftChild()));
            if (node->HasRightChild())
                MapPreOrder(mf, par, &(node->RightChild()));
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPreOrder(const FoldFunctor ff, const void *par, void *acc) const
    {
        FoldPreOrder(ff, par, acc, &(Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPreOrder(const FoldFunctor ff, const void *par, void *acc, Node *node) const
    {
        if (size > 0)
        {
            if (node != nullptr)
            {
                ff(node->Element(), par, acc);

                if (node->HasLeftChild())
                    FoldPreOrder(ff, par, acc, &(node->LeftChild()));

                if (node->HasRightChild())
                    FoldPreOrder(ff, par, acc, &(node->RightChild()));
            }
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapPostOrder(const MapFunctor mf, void *par)
    {
        MapPostOrder(mf, par, &(Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::MapPostOrder(const MapFunctor mf, void *par, Node *node)
    {
        if (size > 0)
        {
            if (node != nullptr)
            {
                if (node->HasLeftChild())
                    MapPostOrder(mf, par, &(node->LeftChild()));

                if (node->HasRightChild())
                    MapPostOrder(mf, par, &(node->RightChild()));

                mf(node->Element(), par);
            }
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPostOrder(const FoldFunctor ff, const void *par, void *acc) const
    {
        FoldPostOrder(ff, par, acc, &(Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPostOrder(const FoldFunctor ff, const void *par, void *acc, Node *node) const
    {
        if (size > 0)
        {
            if (node != nullptr)
            {

                if (node->HasLeftChild())
                    FoldPostOrder(ff, par, acc, &(node->LeftChild()));

                if (node->HasRightChild())
                    FoldPostOrder(ff, par, acc, &(node->RightChild()));
                ff(node->Element(), par, acc);
            }
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapInOrder(const MapFunctor mf, void *par)
    {
        MapInOrder(mf, par, &(Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::MapInOrder(const MapFunctor mf, void *par, Node *node)
    {
        if (size > 0)
        {
            if (node != nullptr)
            {
                if (node->HasLeftChild())
                    MapInOrder(mf, par, &(node->LeftChild()));

                mf(node->Element(), par);

                if (node->HasRightChild())
                    MapInOrder(mf, par, &(node->RightChild()));
            }
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldInOrder(const FoldFunctor ff, const void *par, void *acc) const
    {
        FoldInOrder(ff, par, acc, &(Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::FoldInOrder(const FoldFunctor ff, const void *par, void *acc, Node *node) const
    {
        if (size > 0)
        {
            if (node != nullptr)
            {
                if (node->HasLeftChild())
                    FoldInOrder(ff, par, acc, &node->LeftChild());

                ff(node->Element(), par, acc);

                if (node->HasRightChild())
                    FoldInOrder(ff, par, acc, &node->RightChild());
            }
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapBreadth(const MapFunctor mf, void *par)
    {
        MapBreadth(mf, par, &(Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::MapBreadth(const MapFunctor mf, void *par, Node *node)
    {
        if (size > 0)
        {
            QueueLst<Node *> savedNodes;

            savedNodes.Enqueue(node);

            while (!savedNodes.Empty())
            {
                node = savedNodes.HeadNDequeue();
                mf(node->Element(), par);
                if (node->HasLeftChild())
                    savedNodes.Enqueue(&(node->LeftChild()));

                if (node->HasRightChild())
                    savedNodes.Enqueue(&(node->RightChild()));
            }
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldBreadth(const FoldFunctor ff, const void *par, void *acc) const
    {
        FoldBreadth(ff, par, acc, &(Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::FoldBreadth(const FoldFunctor ff, const void *par, void *acc, Node *node) const
    {
        if (size > 0)
        {
            QueueLst<Node *> savedNodes;

            savedNodes.Enqueue(node);

            while (!savedNodes.Empty())
            {
                node = savedNodes.HeadNDequeue();
                ff(node->Element(), par, acc);
                if (node->HasLeftChild())
                    savedNodes.Enqueue(&(node->LeftChild()));

                if (node->HasRightChild())
                    savedNodes.Enqueue(&(node->RightChild()));
            }
        }
    }

    /* ************************************BTPreOrderIterator****************************** */
    template <typename Data>
    BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator++()
    {

        if (Terminated())
        {
            throw std::length_error("Albero terminato");
        }
        else
        {
            if (curr->HasLeftChild())
            {
                if (curr->HasRightChild())
                    savedNodes.Push(&(curr->RightChild()));

                curr = &curr->LeftChild();
            }
            else
            {
                if (curr->HasRightChild())
                    curr = &curr->RightChild();
                else if (!savedNodes.Empty())
                    curr = savedNodes.TopNPop();
                else
                    curr = nullptr;
            }
        }
        return *this;
    }

    /* ************************************BTPostOrderIterator****************************** */
    //operator ++
    template <typename Data>
    BTPostOrderIterator<Data> &BTPostOrderIterator<Data>::operator++()
    {
        if (Terminated())
        {
            throw std::length_error("Albero terminato");
        }
        else
        {
            if (!savedNodes.Empty())
            {
                if (savedNodes.Top()->HasLeftChild() && curr == &savedNodes.Top()->LeftChild())
                {
                    if (savedNodes.Top()->HasRightChild())
                        curr = mostLeftLeaf(&savedNodes.Top()->RightChild());
                    else
                        curr = savedNodes.TopNPop();
                }
                else
                {
                    curr = savedNodes.TopNPop();
                }
            }
            else
            {
                curr = nullptr;
            }
        }
        return *this;
    }

    /* ************************************BTInOrderIterator****************************** */
    //operator ++
    template <typename Data>
    BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator++()
    {
        if (Terminated())
        {
            throw std::length_error("Albero terminato");
        }
        else
        {
            if (curr->HasRightChild())
            {
                curr = mostLeftNode(&curr->RightChild());
            }
            else if (!savedNodes.Empty())
            {
                curr = savedNodes.TopNPop();
            }
            else
            {
                curr = nullptr;
            }
        }
        return *this;
    }

    template <typename Data>
    BTBreadthIterator<Data> &BTBreadthIterator<Data>::operator++()
    {
        if (Terminated())
        {
            throw std::length_error("Albero terminato");
        }
        else
        {
            if (curr->HasLeftChild())
                savedNodes.Enqueue(&curr->LeftChild());

            if (curr->HasRightChild())
                savedNodes.Enqueue(&curr->RightChild());

            if (savedNodes.Empty())
                curr = nullptr;
            else
                curr = savedNodes.HeadNDequeue();
        }
        return *this;
    }
}
