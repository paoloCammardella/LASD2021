
namespace lasd
{
    /* **********************************Constructors************************************** */
    template <typename Data>
    StackLst<Data>::StackLst()
    {
        head = nullptr;
        size = 0;
    }

    //Copy from a linear container
    template <typename Data>
    StackLst<Data>::StackLst(const LinearContainer<Data> &cont)
    {
        if (cont.Size() > 0)
        {
            size = cont.Size();
            for (unsigned long i = size - 1; i > -1; --i)
            {
                Push(cont[i]);
            }
        }
    }

    //Copy contructor
    template <typename Data>
    StackLst<Data>::StackLst(const StackLst<Data> &stk)
    {

        size = stk.size;
        if (stk.head != nullptr)
        {
            head = new Node(stk.head->dat);
            Node *tmp = stk.head->next;
            Node *curr = head;

            while (tmp != nullptr)
            {
                curr->next = new Node(tmp->dat);
                curr = curr->next;
                tmp = tmp->next;
            }
        }
        else
        {
            head = nullptr;
        }
    }

    //Move constructor
    template <typename Data>
    StackLst<Data>::StackLst(StackLst<Data> &&stk) noexcept
    {
        std::swap(head, stk.head);
        std::swap(size, stk.size);
    }
    /* ***********************************Destructor*************************************** */

    template <typename Data>
    StackLst<Data>::~StackLst()
    {
        Clear();
        delete head;
    }

    /* **********************************Assignment*************************************** */

    // Copy assignment
    template <typename Data>
    StackLst<Data> &StackLst<Data>::operator=(const StackLst<Data> &stk)
    {
        List<Data>::operator=(stk);
        return *this;
    }

    // Move assignment
    template <typename Data>
    StackLst<Data> &StackLst<Data>::operator=(StackLst<Data> &&stk) noexcept
    {
        std::swap(head, stk.head);
        std::swap(size, stk.size);
        return *this;
    }
    /* ***********************************Comparison*********************************** */
    template <typename Data>
    bool StackLst<Data>::operator==(const StackLst<Data> &stk) const
    {
        if (size == stk.size)
        {
            Node *tmp = head;
            Node *curr = stk.head;
            while (curr)
            {
                if (tmp->dat != curr->dat)
                {
                    return false;
                }
                curr = curr->next;
                tmp = tmp->next;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    bool StackLst<Data>::operator!=(const StackLst<Data> &stk) const
    {
        return !(stk == *this);
    }

    /* ***************************Specific member functions****************************** */
    template <typename Data>
    void StackLst<Data>::Push(const Data &data)
    {
        Node *tmp = new Node(data);
        tmp->next = head;
        head = tmp;
        ++size;
    }

    template <typename Data>
    void StackLst<Data>::Push(Data &&data) noexcept
    {
        Node *tmp = new Node(data);
        tmp->next = head;
        head = tmp;
        ++size;
    }

    template <typename Data>
    Data &StackLst<Data>::Top() const
    {
        if (size > 0)
        {
            return head->dat;
        }
        else
            throw std::length_error("La pila alla quale stai provando ad accedere e` vuota");
    }

    template <typename Data>
    void StackLst<Data>::Pop()
    {
        if (size > 0)
        {
            Node *tmp = head;
            head = head->next;
            delete tmp;
            --size;
        }
        else
        {
            throw std::length_error("La pila alla quale stai provando ad accedere e` vuota");
        }
    }

    template <typename Data>
    Data StackLst<Data>::TopNPop()
    {
        if (size > 0)
        {
            Node *tmp = head;
            head = head->next;
            Data var = tmp->dat;
            delete tmp;
            --size;
            return var;
        }
        else
        {
            throw std::length_error("La pila alla quale stai provando ad accedere e` vuota");
        }
    }

    template <typename Data>
    void StackLst<Data>::Clear()
    {
        if (size > 0)
        {
            while (head != nullptr)
            {
                Node *tmp = head;
                head = head->next;
                delete tmp;
            }
            head = nullptr;
            size = 0;
        }
    }
}
