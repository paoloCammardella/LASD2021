
namespace lasd
{

    /* *************************************Constructors************************************* */
    //Default contructor
    template <typename Data>
    QueueVec<Data>::QueueVec()
    {
        size = 4;
        front = 0;
        rear = -1;
        elements = new Data[size]{};
    }

    //Copy contructor from a linear container
    template <typename Data>
    QueueVec<Data>::QueueVec(const LinearContainer<Data> &cont)
    {
        size = cont.Size();
        elements = new Data[size];
        front = 0;
        for (unsigned long i = 0; i < size; ++i)
        {
            elements[i] = cont[i];
        }
        rear = size - 1;
    }

    //Copy contructor
    template <typename Data>
    QueueVec<Data>::QueueVec(const QueueVec<Data> &que) : Vector<Data>::Vector(que)
    {
        front = que.front;
        rear = que.rear;
    }

    //Move contructor
    template <typename Data>
    QueueVec<Data>::QueueVec(QueueVec<Data> &&que) noexcept
    {
        std::swap(size, que.size);
        std::swap(rear, que.rear);
        std::swap(front, que.front);
        std::swap(elements, que.elements);
    }

    //Destructor
    template <typename Data>
    QueueVec<Data>::~QueueVec()
    {
        Clear();
    }
    /* ************************************Assignments************************************** */
    //Copy assignments
    template <typename Data>
    QueueVec<Data> &QueueVec<Data>::operator=(const QueueVec<Data> &que)
    {
        Vector<Data>::operator=(que);
        front = que.front;
        rear = que.rear;
        return *this;
    }

    //Move assignment
    template <typename Data>
    QueueVec<Data> &QueueVec<Data>::operator=(QueueVec<Data> &&que) noexcept
    {
        std::swap(size, que.size);
        std::swap(front, que.front);
        std::swap(rear, que.rear);
        std::swap(elements, que.elements);
        return *this;
    }

    /* ************************************Comparison*********************************************** */
    template <typename Data>
    bool QueueVec<Data>::operator==(const QueueVec<Data> &que) const
    {
        if (Size() == que.Size())
        {
            for (unsigned long i = 0; i < Size(); ++i)
            {
                if (elements[i] != que.elements[i])
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
    bool QueueVec<Data>::operator!=(const QueueVec<Data> &que) const
    {
        return !(*this == que);
    }
    /* ************************************Specific member functions*********************************************** */
    template <typename Data>
    void QueueVec<Data>::Enqueue(const Data &data)
    {
        if (Size() == size)
        {
            Expand();
        }
        rear = (rear + 1) % size;
        elements[rear] = data;
    }

    template <typename Data>
    void QueueVec<Data>::Enqueue(Data &&data) noexcept
    {
        if (Size() == size)
        {
            Expand();
        }
        rear = (rear + 1) % size;
        elements[rear] = data;
    }

    template <typename Data>
    Data &QueueVec<Data>::Head() const
    {
        if (Size() != 0)
        {
            return elements[front];
        }
        else
        {
            throw std::length_error("La coda alla quale stai accedendo e` vuota");
        }
    }

    template <typename Data>
    void QueueVec<Data>::Dequeue()
    {
        if (Size() != 0)
        {
            front = (front + 1) % size;
            if (Size() < size / 4)
            {
                Reduce();
            }
        }
        else
        {
            throw std::length_error("La coda alla quale stai accedendo e` vuota");
        }
    }

    template <typename Data>
    Data QueueVec<Data>::HeadNDequeue()
    {
        if (Size() != 0)
        {
            Data var = Head();
            Dequeue();
            return var;
        }
        else
        {
            throw std::length_error("La coda alla quale stai accedendo e` vuota");
        }
    }

    template <typename Data>
    void QueueVec<Data>::Clear()
    {
        front = 0;
        size = 4;
        rear = -1;
        delete[] elements;
        elements = new Data[size]{};
    }

    template <typename Data>
    void QueueVec<Data>::Expand()
    {
        SwapVectors(size * 2);
    }

    template <typename Data>
    void QueueVec<Data>::Reduce()
    {
        SwapVectors(size * 1.25);
    }

    template <typename Data>
    void QueueVec<Data>::SwapVectors(const unsigned long &dim){
       if (dim == 0)
            Clear();
        else if (size != dim)
        {
            unsigned long limit = (size < dim) ? size : dim;
            Data *tmpElements = new Data[dim]{};
            for (unsigned long i = 0; i < limit; ++i)
            {
                std::swap(elements[i], tmpElements[i]);
            }
            std::swap(elements, tmpElements);
            size = dim;
            delete[] tmpElements;
        }
    }
}
