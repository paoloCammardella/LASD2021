#include <iostream>

namespace lasd
{
    /* ***********************************constructors*************************************** */
    template <typename Data>
    List<Data>::Node::Node(const Data &data)
    {
        this->dat = data;
        this->next = nullptr;
    }

    template <typename Data>
    List<Data>::Node::Node(Data &&data) noexcept
    {
        std::swap(dat, data);
        next = nullptr;
    }

    template <typename Data>
    List<Data>::Node::Node(const Node &node)
    {
        dat = node.dat;
        next = node.next;
    }

    template <typename Data>
    List<Data>::Node::Node(Node &&node) noexcept
    {
        std::swap(dat, node.dat);
        std::swap(next, node.next);
    }
    /* *******************************comparison operator********************************** */
    template <typename Data>
    bool List<Data>::Node::operator==(const Node &node) const noexcept
    {
        if (dat == node.dat)
        {
            while (next != nullptr && node.next != nullptr)
            {
                if (*next == *node.next)
                {
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    bool List<Data>::Node::operator!=(const Node &node) const noexcept
    {
        return !(*this == node);
    }
    /*---------------------------------------LIST-------------------------------------------*/

    /* **********************************Constructors************************************** */
    template <typename Data>
    List<Data>::List(const LinearContainer<Data> &cont)
    {
        if (cont.Size() > 0)
        {
            Node *curr = new Node(cont[0]);
            head = curr;
            size = cont.Size();
            unsigned long i = 1;
            while (i < cont.Size())
            {
                curr->next = new Node(cont[i]);
                tail = curr->next;
                curr = curr->next;
                ++i;
            }
        }
    }

    template <typename Data>
    List<Data>::List(const List<Data> &list)
    {
        size = list.size;
        if (list.head != nullptr)
        {
            head = new Node(list.head->dat);
            Node *tmp = list.head->next;
            Node *curr = head;
            tail = head;

            while (tmp != nullptr)
            {
                tail->next = new Node(tmp->dat);
                tail = tail->next;
                tmp = tmp->next;
            }
        }
        else
        {
            head = tail = nullptr;
        }
    }

    template <typename Data>
    List<Data>::List(List<Data> &&list) noexcept
    {
        std::swap(head, list.head);
        std::swap(tail, list.tail);
        std::swap(size, list.size);
    }

    template <typename Data>
    List<Data>::~List()
    {
        Clear();
    }

    template <typename Data>
    List<Data> &List<Data>::operator=(const List<Data> &list)
    {
        List<Data> *tmpList = new List<Data>(list);
        std::swap(*tmpList, *this);
        delete tmpList;
        return *this;
    }

    template <typename Data>
    List<Data> &List<Data>::operator=(List<Data> &&list) noexcept
    {
        std::swap(size, list.size);
        std::swap(head, list.head);
        std::swap(tail, list.tail);
        return *this;
    }

    template <typename Data>
    bool List<Data>::operator==(const List<Data> &list) const noexcept
    {
        if (size == list.size)
        {
            Node *tmp = head;
            Node *curr = list.head;
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
    bool List<Data>::operator!=(const List<Data> &list) const noexcept
    {
        return !(*this == list);
    }

    template <typename Data>
    void List<Data>::InsertAtFront(const Data &data)
    {
        Node *node = new Node(data);

        if (head == nullptr)
        {
            tail = node;
        }
        else
        {
            node->next = head;
        }
        head = node;
        ++size;
    }

    template <typename Data>
    void List<Data>::InsertAtFront(Data &&data) noexcept
    {
        Node *node = new Node(data);
        if (head == nullptr)
        {
            tail = node;
        }
        else
        {
            node->next = head;
        }
        head = node;
        size++;
    }

    template <typename Data>
    void List<Data>::RemoveFromFront()
    {
        if (head != nullptr)
        {
            Node *tmp = head;
            head = head->next;
            delete tmp;
            --size;
        }
        else
            throw std::length_error("La lista a cui stai provando ad accedere e` vuota");
    }

    template <typename Data>
    Data List<Data>::FrontNRemove()
    {
        if (size > 0)
        {
            Data dat = head->dat;
            RemoveFromFront();
            return dat;
        }
        else
            throw std::length_error("La lista a cui stai provando ad accedere e` vuota");
    }

    template <typename Data>
    void List<Data>::InsertAtBack(const Data &data)
    {
        if (head == nullptr)
        {
          InsertAtFront(data);
        }
        else
        {
            tail->next = new Node(data);;
            tail = tail->next;
            ++size;
        }
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data &&data) noexcept
    {
        if(head == nullptr){
            InsertAtFront(data);
        }else{
            tail->next = new Node(data);
            tail = tail->next;
            ++size;
        }
    }

    template <typename Data>
    void List<Data>::Clear()
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
            tail = nullptr;
            size = 0;
        }
    }

    template <typename Data>
    Data &List<Data>::Front() const
    {
        if (size > 0)
            return (head->dat);
        else
            throw std::length_error("la lista alla quale stai provando ad accedere e` vuota.");
    }

    template <typename Data>
    Data &List<Data>::Back() const
    {
        if (size > 0)
            return (tail->dat);
        else
            throw std::length_error("la lista alla quale stai provando ad accedere e` vuota.");
    }

    template <typename Data>
    Data &List<Data>::operator[](const unsigned long i) const
    {
        if (size < i)
            throw std::out_of_range("L'indice al quale stai provando ad accedere e` maggiore della dimensione della lista");
        else if (i == size - 1)
            return tail->dat;
        else
        {
            Node *curr = head;
            for (unsigned long j = 0; j < i; ++j)
                curr = curr->next;
            return curr->dat;
        }
    }

    template <typename Data>
    void List<Data>::MapPreOrder(const MapFunctor foo, void *par)
    {
        MapPreOrder(foo, par, head);
    }

    template <typename Data>
    void List<Data>::MapPostOrder(const MapFunctor foo, void *par)
    {
        MapPostOrder(foo, par, head);
    }

    template <typename Data>
    void List<Data>::MapPreOrder(const MapFunctor foo, void *par, Node *start)
    {
        while (start != nullptr)
        {
            foo(start->dat, par);
            start = start->next;
        }
    }

    template <typename Data>
    void List<Data>::MapPostOrder(const MapFunctor foo, void *par, Node *start)
    {
        Node *node = start;
        if (node == nullptr)
        {
            return;
        }
        MapPostOrder(foo, par, node->next);
        foo(node->dat, par);
    }

    template <typename Data>
    void List<Data>::FoldPreOrder(const FoldFunctor foo, const void *par, void *acc) const
    {
        FoldPreOrder(foo, par, acc, head);
    }

    template <typename Data>
    void List<Data>::FoldPostOrder(const FoldFunctor foo, const void *par, void *acc) const
    {
        FoldPostOrder(foo, par, acc, head);
    }

    template <typename Data>
    void List<Data>::FoldPreOrder(const FoldFunctor foo, const void *par, void *acc, Node *start) const
    {
        while (start != nullptr)
        {
            foo(start->dat, par, acc);
            start = start->next;
        }
    }

    template <typename Data>
    void List<Data>::FoldPostOrder(const FoldFunctor foo, const void *par, void *acc, Node *start) const
    {
        if (start != nullptr)
        {
            FoldPostOrder(foo, par, acc, start->next);
            foo(start->dat, par, acc);
        }
    }
}