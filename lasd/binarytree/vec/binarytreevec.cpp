
namespace lasd
{

    /* ************************************************************************** */
    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(unsigned long pos, Vector<NodeVec *> *elements, const Data &dato)
    {
        index = pos;
        data = dato;
        ref = elements;
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(unsigned long pos, Vector<NodeVec *> *elements, Data &&dato) noexcept
    {
        ref = elements;
        index = pos;
        std::swap(data, dato);
    }

    template <typename Data>
    BinaryTreeVec<Data>::~BinaryTreeVec()
    {
        if(size > 0)
            Clear();
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data> &cont)
    {
        size = cont.Size();
        elements.Resize(size);
        for (unsigned long i = 0; i < size; ++i)
        {
            elements[i] = new NodeVec(i, &elements, cont[i]);
        }
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec &BT)
    {
        size = BT.size;
        elements.Resize(BT.elements.Size());
        for (unsigned long i = 0; i < BT.elements.Size(); ++i)
            elements[i] = new NodeVec(i, &elements, BT.elements[i]->Element());
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec &&BT) noexcept
    {
        std::swap(size, BT.size);
        std::swap(elements, BT.elements);
        for (unsigned long i = 0; i < size; ++i)
            elements[i]->ref = &elements;
    }

    template <typename Data>
    BinaryTreeVec<Data> &BinaryTreeVec<Data>::operator=(const BinaryTreeVec &BT)
    {
        BinaryTreeVec<Data> *tmp = new BinaryTreeVec<Data>(BT);
        std::swap(*this, *tmp);
        for (unsigned long i = 0; i < size; ++i)
        {
            elements[i]->ref = &elements;
        }
        delete tmp;
        return *this;
    }

    template <typename Data>
    BinaryTreeVec<Data> &BinaryTreeVec<Data>::operator=(BinaryTreeVec &&BT) noexcept
    {
        std::swap(size, BT.size);
        std::swap(elements, BT.elements);

        for (unsigned long i = 0; i < size; ++i)
        {
            elements[i]->ref = &elements;
        }
        return *this;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec &BT) const
    {
        if (size == BT.size)
        {
            for (unsigned long i = 0; i < size; ++i)
            {
                if (elements[i] != BT.elements[i])
                    return false;
            }
        }
        else
        {
            return false;
        }

        return true;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec &BT) const
    {
        return !(*this == BT);
    }
    /* ************************************************************************** */
}
