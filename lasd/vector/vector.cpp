
namespace lasd
{

    /* ******************************Specific constructors************************************* */
    template <typename Data>
    Vector<Data>::Vector(const unsigned long n_size)
    {
        elements = new Data[n_size]{};
        size = n_size;
    }

    template <typename Data>
    Vector<Data>::Vector(const LinearContainer<Data> &container)
    {
        size = container.Size();
        elements = new Data[size];
        for (unsigned long i = 0; i < size; ++i)
        {
            elements[i] = container[i];
        }
    }
    /* *****************************Copy n Move constructors********************************* */
    //copy constructor
    template <typename Data>
    Vector<Data>::Vector(const Vector<Data> &cVector)
    {
        elements = new Data[cVector.size]{};
        std::copy(cVector.elements, cVector.elements + cVector.size, elements);
        size = cVector.size;
    }

    //move constructor
    template <typename Data>
    Vector<Data>::Vector(Vector<Data> &&mVector) noexcept
    {
        std::swap(elements, mVector.elements);
        std::swap(size, mVector.size);
    }
    /* **************************************Destructor************************************** */
    template <typename Data>
    Vector<Data>::~Vector()
    {
        delete[] elements;
    }
    /* **************************************Copy n Move assignment************************** */
    template <typename Data>
    Vector<Data> &Vector<Data>::operator=(const Vector<Data> &vector)
    {
        Vector<Data> *tmpvec = new Vector<Data>(vector);
        std::swap(*tmpvec, *this);
        delete tmpvec;
        return *this;
    }

    template <typename Data>
    Vector<Data> &Vector<Data>::operator=(Vector<Data> &&vector) noexcept
    {
        std::swap(elements, vector.elements);
        std::swap(size, vector.size);
        return *this;
    }
    /* **************************************Comparison operator***************************** */
    template <typename Data>
    bool Vector<Data>::operator==(const Vector<Data> &vector) const noexcept
    {
        if (size == vector.size)
        {
            for (unsigned long i = 0; i < size; ++i)
            {
                if (elements[i] != vector.elements[i])
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
    bool Vector<Data>::operator!=(const Vector<Data> &vector) const noexcept
    {
        return !(*this == vector);
    }

    template <typename Data>
    void Vector<Data>::Resize(const unsigned long n_size)
    {
        if (n_size == 0)
            Clear();
        else if (size != n_size)
        {
            unsigned long limit = (size < n_size) ? size : n_size;
            Data *tmpElements = new Data[n_size]{};
            for (unsigned long i = 0; i < limit; ++i)
            {
                std::swap(elements[i], tmpElements[i]);
            }
            std::swap(elements, tmpElements);
            size = n_size;
            delete[] tmpElements;
        }
    }

    template <typename Data>
    void Vector<Data>::Clear()
    {
        delete[] elements;
        elements = nullptr;
        size = 0;
    }

    template <typename Data>
    Data &Vector<Data>::Front() const
    {
        if (size != 0)
            return elements[0];
        else
            throw std::length_error("Il vettore al quale stai provando ad accedere e` vuoto.");
    }

    template <typename Data>
    Data &Vector<Data>::Back() const
    {
        if (size != 0)
            return elements[size - 1];
        else
            throw std::length_error("Il vettore al quale stai provando ad accedere e` vuoto.");
    }

    template <typename Data>
    Data &Vector<Data>::operator[](const unsigned long i) const
    {
        if (i < size)
            return elements[i];
        else
            throw std::out_of_range("L'indice " + std::to_string(i) + "; e` maggiore della dimensione.");
    }

    template <typename Data>
    void Vector<Data>::MapPreOrder(const MapFunctor foo, void *par)
    {
        for (unsigned long i = 0; i < size; ++i)
        {
            foo(elements[i], par);
        }
    }

    template <typename Data>
    void Vector<Data>::MapPostOrder(const MapFunctor foo, void *par)
    {
        unsigned long i = size;
        while (i > 0)
        {
            foo(elements[--i], par);
        }
    }

    template <typename Data>
    void Vector<Data>::FoldPreOrder(const FoldFunctor foo, const void *par, void *acc) const
    {
        for (unsigned long i = 0; i < size; ++i)
        {
            foo(elements[i], par, acc);
        }
    }

    template <typename Data>
    void Vector<Data>::FoldPostOrder(const FoldFunctor foo, const void *par, void *acc) const
    {
        unsigned long i = size;
        while (i > 0)
        {
            foo(elements[--i], par, acc);
        }
    }
}