
namespace lasd
{

    /* **********************************Constructors**************************************** */
    template <typename Data>
    QueueLst<Data>::QueueLst()
    {
        head = nullptr;
        rear = nullptr;
        size = 0;
    }

    //Copy from a linear container
    template <typename Data>
    QueueLst<Data>::QueueLst(const LinearContainer<Data> &cont) : List<Data>(cont)
    {
    }
    //Copy constructor
    template <typename Data>
    QueueLst<Data>::QueueLst(const QueueLst<Data> &que) : List<Data>(que)
    {
    }

    //Move constructor
    template <typename Data>
    QueueLst<Data>::QueueLst(QueueLst<Data> &&que) noexcept : List<Data>(std::move(que))
    {
    }

    template <typename Data>
    QueueLst<Data>::~QueueLst()
    {
        Clear();
    }

    template <typename Data>
    QueueLst<Data> &QueueLst<Data>::operator=(const QueueLst<Data> &que)
    {
        List<Data>::operator=(que);
        return *this;
    }

    template <typename Data>
    QueueLst<Data> &QueueLst<Data>::operator=(QueueLst<Data> &&que) noexcept
    {
        List<Data>::operator=(std::move(que));
        return *this;
    }
    /* ***********************************Comparison**************************************** */

    template <typename Data>
    bool QueueLst<Data>::operator==(const QueueLst<Data> &que) const
    {
        return List<Data>::operator==(que);
    }

    template <typename Data>
    bool QueueLst<Data>::operator!=(const QueueLst<Data> &que) const
    {
        return !(*this == que);
    }
    /* *****************************Specific member functions******************************* */

    template <typename Data>
    void QueueLst<Data>::Enqueue(const Data &data)
    {
        List<Data>::InsertAtBack(data);
    }

    template <typename Data>
    void QueueLst<Data>::Enqueue(Data &&data) noexcept
    {
        List<Data>::InsertAtBack(std::move(data));
    }

    template <typename Data>
    Data &QueueLst<Data>::Head() const
    {
        return List<Data>::Front();
    }

    template <typename Data>
    void QueueLst<Data>::Dequeue()
    {
        List<Data>::RemoveFromFront();
    }

    template <typename Data>
    Data QueueLst<Data>::HeadNDequeue()
    {
        return List<Data>::FrontNRemove();
    }

    template <typename Data>
    void QueueLst<Data>::Clear()
    {
        List<Data>::Clear();
    }
}
