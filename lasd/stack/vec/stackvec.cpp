
namespace lasd
{

    /* ***********************************Constructors*************************************** */
    //Default constructor
    template <typename Data>
    StackVec<Data>::StackVec()
    {
        size = 2;
        elements = new Data[size]{};
        firstFree = 0;
    }

    //Copy constructor from linear container
    template <typename Data>
    StackVec<Data>::StackVec(const LinearContainer<Data> &cont)
    {
        size = cont.Size();
        elements = new Data[size];
        for (unsigned long i = 0; i < size; ++i)
        {
            elements[i] = cont[i];
        }
        firstFree = size;
    }

    //Copy contructor
    template <typename Data>
    StackVec<Data>::StackVec(const StackVec<Data> &stk)
    {
        size = stk.size;
        elements = new Data[size]{};
        std::copy(stk.elements, stk.elements + stk.firstFree, elements);
        firstFree = stk.firstFree;
    }

    //Move constructor
    template <typename Data>
    StackVec<Data>::StackVec(StackVec<Data> &&mstk) noexcept
    {
        std::swap(size, mstk.size);
        std::swap(elements, mstk.elements);
        std::swap(firstFree, mstk.firstFree);
    }
    /* ***********************************Destructor*************************************** */
    template <typename Data>
    StackVec<Data>::~StackVec()
    {
        Clear();
    }
    /* **********************************Assignments*************************************** */
    //Copy assignment
    template <typename Data>
    StackVec<Data> &StackVec<Data>::operator=(const StackVec<Data> &stk)
    {
        StackVec<Data> *tmpvec = new StackVec<Data>(stk);
        std::swap(*tmpvec, *this);
        delete tmpvec;
        return *this;
    }

    //Move assignment
    template <typename Data>
    StackVec<Data> &StackVec<Data>::operator=(StackVec<Data> &&mstk) noexcept
    {
        std::swap(size, mstk.size);
        std::swap(elements, mstk.elements);
        std::swap(firstFree, mstk.firstFree);
        return *this;
    }
    /* **********************************Comparison*************************************** */
    template <typename Data>
    bool StackVec<Data>::operator==(const StackVec<Data> &stk) const
    {
        if (firstFree == stk.firstFree)
        {
            for (unsigned long i = 0; i < firstFree; ++i)
            {
                if (elements[i] != stk.elements[i])
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    bool StackVec<Data>::operator!=(const StackVec<Data> &stk) const
    {
        return !(*this == stk);
    }
    /* ******************************Specific member functions********************************* */
    template <typename Data>
    void StackVec<Data>::Push(const Data &data)
    {
        if (firstFree == size)
        {
            Expand();
        }
        elements[firstFree] = data;
        ++firstFree;
    }

    template <typename Data>
    void StackVec<Data>::Push(Data &&data) noexcept
    {
        if (firstFree == size)
        {
            Expand();
        }
        elements[firstFree] = data;
        ++firstFree;
    }

    template <typename Data>
    Data &StackVec<Data>::Top() const
    {
        if (firstFree != 0)
        {
            return elements[firstFree - 1];
        }
        else
        {
            throw std::length_error("La pila alla quale stai provando ad accedere e` vuota");
        }
    }

    template <typename Data>
    void StackVec<Data>::Pop()
    {
        if (firstFree != 0)
        {
            --firstFree;
            if (firstFree == (size / 4))
            {
                Reduce();
            }
        }
        else
        {
            throw std::length_error("La pila alla quale stai provando ad accedere e` vuota");
        }
    }

    template <typename Data>
    Data StackVec<Data>::TopNPop()
    {
        if (firstFree != 0)
        {
            Data var = Top();
            Pop();
            return var;
        }
        else
        {
            throw std::length_error("La pila alla quale stai provando ad accedere e` vuota");
        }
    }

    template <typename Data>
    void StackVec<Data>::Clear()
    {
        delete[] elements;
        size = 2;
        elements = new Data[size]{};
        firstFree = 0;
    }

    template <typename Data>
    void StackVec<Data>::Expand()
    {
        Vector<Data>::Resize(size * 2);
    }

    template <typename Data>
    void StackVec<Data>::Reduce()
    {
        Vector<Data>::Resize(size * 1.25);
    }
}