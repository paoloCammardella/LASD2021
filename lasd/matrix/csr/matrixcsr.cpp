
namespace lasd
{

    /* *********************************Constructors********************************* */
    template <typename Data>
    MatrixCSR<Data>::MatrixCSR()
    {
        rowVector.Resize(1);
        rowVector[0] = &head;
    }

    template <typename Data>
    MatrixCSR<Data>::MatrixCSR(const unsigned long rows, const unsigned long columns)
    {
        rowsNumber = rows;
        columnsNumber = columns;
        rowVector.Resize(rowsNumber + 1);

        for (unsigned long index = 0; index < rowsNumber + 1; ++index)
        {
            rowVector[index] = &head;
        }
    }

    template <typename Data>
    MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data> &matrix) : MatrixCSR<Data>::MatrixCSR(matrix.rowsNumber, matrix.columnsNumber)
    {
        for (unsigned long i = 0; i < rowsNumber; ++i)
        {
            for (Node **ptr = matrix.rowVector[i]; ptr != matrix.rowVector[i + 1]; ptr = &((*ptr)->next))
            {
                Node &node = **ptr;
                (*this)(i, node.dat.second) = node.dat.first;
            }
        }
    }

    template <typename Data>
    MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data> &&matrix) noexcept
    {
        std::swap(columnsNumber, matrix.columnsNumber);
        std::swap(rowsNumber, matrix.rowsNumber);
        std::swap(rowVector, matrix.rowVector);
        std::swap(head, matrix.head);
        std::swap(size, matrix.size);

        unsigned long index = 0;
        while (index < size && rowVector[index] == &matrix.head)
        {
            rowVector[index] = &head;
            ++index;
        }
    }

    template <typename Data>
    MatrixCSR<Data>::~MatrixCSR()
    {
        if (size > 0)
        {
            Clear();
        }
    }

    template <typename Data>
    MatrixCSR<Data> &MatrixCSR<Data>::operator=(const MatrixCSR<Data> &matrix)
    {
        MatrixCSR<Data> *tmp = new MatrixCSR<Data>(matrix);
        std::swap(*this, *tmp);
        delete tmp;

        return *this;
    }

    template <typename Data>
    MatrixCSR<Data> &MatrixCSR<Data>::operator=(MatrixCSR<Data> &&matrix) noexcept
    {
        std::swap(columnsNumber, matrix.columnsNumber);
        std::swap(rowsNumber, matrix.rowsNumber);
        std::swap(rowVector, matrix.rowVector);
        std::swap(head, matrix.head);
        std::swap(size, matrix.size);

        unsigned long index = 0;
        while (index < size && rowVector[index] == &matrix.head)
        {
            rowVector[index] = &head;
            ++index;
        }

        return *this;
    }

    template <typename Data>
    bool MatrixCSR<Data>::operator==(const MatrixCSR<Data> &matrix) const noexcept
    {
        // for(unsigned long i = 0; i < rowsNumber; ++i){
        //     for(unsigned long j = 0; j < columnsNumber; ++j){
        //         if(ExistsCell(i, j) && matrix.ExistsCell(i, j)){
        //             if((*this)(i,j) != matrix(i,j)) return false;
        //         }else if(matrix.ExistsCell(i, j)) return false;
        //     }
        // }
        // return true;

        return (rowsNumber == matrix.rowsNumber && columnsNumber == matrix.columnsNumber && List<std::pair<Data, unsigned long>>::operator==(matrix));
    }

    template <typename Data>
    bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data> &matrix) const noexcept
    {
        return !(*this == matrix);
    }

    template <typename Data>
    void MatrixCSR<Data>::RowResize(const unsigned long rows)
    {
        if (rows == 0)
        {
            List<std::pair<Data, ulong>>::Clear();
            size = 0;
            rowVector.Resize(1);
            rowVector[0] = &head;
            return;
        }
        else if (rows < rowsNumber)
        {
            Node *pointer = *rowVector[rows];
            Node *tmp = nullptr;
            while (pointer != nullptr)
            {
                tmp = pointer->next;
                delete pointer;
                pointer = tmp;
                --size;
            }

            rowVector.Resize(rows + 1);
            *rowVector[rows] = nullptr;
        }
        else if (rows > rowsNumber)
        {
            rowVector.Resize(rows + 1);
            for (unsigned long i = rowsNumber; i < rows; ++i)
            {
                rowVector[i + 1] = rowVector[rowsNumber];
            }
        }
        rowsNumber = rows;
    }

    template <typename Data>
    void MatrixCSR<Data>::ColumnResize(const unsigned long columns)
    {
        if (columns == 0)
        {
            List<std::pair<Data, ulong>>::Clear();
            size = 0;
            rowVector.Resize(1);
            rowVector[0] = &head;
            return;
        }
        else if (columns < columnsNumber)
        {
            unsigned long i = 0;
            Node **pointer = &head;
            while (i <= rowsNumber)
            {
                Node *node;
                Node **end = rowVector[i];
                while (pointer != end && (*pointer)->dat.second < columns)
                {
                    node = *pointer;
                    pointer = &(node->next);
                }
                if (pointer != end)
                {
                    Node *tmp = *pointer;
                    *pointer = (*pointer)->next;
                    delete tmp;
                    --size;
                }
                while (i <= rowsNumber && rowVector[i] == end)
                {
                    rowVector[i] = pointer;
                    ++i;
                }
            }
        }
        columnsNumber = columns;
    }

    template <typename Data>
    bool MatrixCSR<Data>::ExistsCell(unsigned long row, unsigned long column) const noexcept
    {
        if (row < rowsNumber && column < columnsNumber)
        {
            Node **pointer = rowVector[row];
            while (pointer != rowVector[row + 1])
            {
                Node &node = **pointer;
                if (node.dat.second == column)
                {
                    return true;
                }
                pointer = &(node.next);
            }
        }
        return false;
    }

    template <typename Data>
    Data &MatrixCSR<Data>::operator()(unsigned long row, unsigned long column)
    {
        if (row < rowsNumber && column < columnsNumber)
        {
            Node **pointer = rowVector[row];
            while (pointer != rowVector[row + 1] && (*pointer)->dat.second <= column)
            {
                Node &node = **pointer;
                if (node.dat.second == column)
                {
                    return node.dat.first;
                }
                pointer = &(node.next);
            }

            std::pair<Data, unsigned long> data;
            data.second = column;
            Node *newMatrixNode = new Node(data);
            newMatrixNode->next = (*pointer);
            (*pointer) = newMatrixNode;

            for (unsigned long i = row + 1; i < rowsNumber + 1 && rowVector[i] == pointer; ++i)
            {
                rowVector[i] = &(newMatrixNode->next);
            }
            ++size;
            return newMatrixNode->dat.first;
        }
        else
            throw std::out_of_range("La cella non esiste");
    }

    template <typename Data>
    const Data &MatrixCSR<Data>::operator()(unsigned long row, unsigned long column) const
    {
        if (row < rowsNumber && column < columnsNumber)
        {
            for (Node **pointer = rowVector[row]; pointer != rowVector[row + 1] && (*pointer)->dat.second <= column; pointer = &(*pointer)->next)
            {
                Node &node = **pointer;
                if (node.dat.second == column)
                {
                    return node.dat.first;
                }
            }
            throw std::out_of_range("Il dato non e` presente");
        }
        else
        {
            throw std::out_of_range("La cella non esiste");
        }
    }

    template <typename Data>
    void MatrixCSR<Data>::Clear()
    {
        if (size > 0)
        {
            List<std::pair<Data, unsigned long>>::Clear();
            rowsNumber = columnsNumber = 0;
            rowVector.Resize(1);
        }
    }

    template <typename Data>
    void MatrixCSR<Data>::MapPreOrder(MapFunctor mf, void *par)
    {
        List<std::pair<Data, unsigned long>>::MapPreOrder(
            [&mf](std::pair<Data, unsigned long> &datx, void *paro)
            { mf(datx.first, paro); },
            par);
    }

    template <typename Data>
    void MatrixCSR<Data>::MapPostOrder(MapFunctor mf, void *par)
    {
        List<std::pair<Data, unsigned long>>::MapPostOrder(
            [&mf](std::pair<Data, unsigned long> &datx, void *paro){ mf(datx.first, paro); }
            ,par);
    }

    template <typename Data>
    void MatrixCSR<Data>::FoldPreOrder(FoldFunctor ff, const void *par, void *acc) const
    {
        List<std::pair<Data, unsigned long>>::FoldPreOrder(
            [&ff](const std::pair<Data, unsigned long> &datx, const void *paro, void *acco)
            { ff(datx.first, paro, acco); },
            par, acc);
    }

    template <typename Data>
    void MatrixCSR<Data>::FoldPostOrder(FoldFunctor ff, const void *par, void *acc) const
    {
        List<std::pair<Data, unsigned long>>::FoldPostOrder(
            [&ff](const std::pair<Data, unsigned long> &datx, const void *paro, void *acco)
            { ff(datx.first, paro, acco); },
            par, acc);
    }
    /* ********************************************************************* */
}
