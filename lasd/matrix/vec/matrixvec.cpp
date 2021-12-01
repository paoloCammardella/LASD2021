
namespace lasd
{

    /* ************************************************************************** */
    template <typename Data>
    MatrixVec<Data>::MatrixVec()
    {
        rowsNumber = columnsNumber = size = 0;
        rowVector.Resize(size);
    }

    template <typename Data>
    MatrixVec<Data>::MatrixVec(const unsigned long rows, const unsigned long columns)
    {
        rowsNumber = rows;
        columnsNumber = columns;
        size = rowsNumber * columnsNumber;
        rowVector.Resize(size);
    }

    template <typename Data>
    MatrixVec<Data>::MatrixVec(const MatrixVec &mat)
    {
        rowsNumber = mat.rowsNumber;
        columnsNumber = mat.columnsNumber;
        rowVector = mat.rowVector;
        size = mat.size;
    }

    template <typename Data>
    MatrixVec<Data>::MatrixVec(MatrixVec &&mat) noexcept
    {
        std::swap(rowsNumber, mat.rowsNumber);
        std::swap(columnsNumber, mat.columnsNumber);
        std::swap(rowVector, mat.rowVector);
        std::swap(size, mat.size);
    }

    template <typename Data>
    MatrixVec<Data>::~MatrixVec()
    {
        if (size > 0)
        {
            Clear();
        }
    }

    template <typename Data>
    MatrixVec<Data> &MatrixVec<Data>::operator=(const MatrixVec &mat)
    {
        MatrixVec<Data> *tmp = new MatrixVec<Data>(mat);
        std::swap(*this, *tmp);
        delete tmp;
        return *this;
    }

    template <typename Data>
    MatrixVec<Data> &MatrixVec<Data>::operator=(MatrixVec &&mat) noexcept
    {
        std::swap(rowsNumber, mat.rowsNumber);
        std::swap(columnsNumber, mat.columnsNumber);
        std::swap(rowVector, mat.rowVector);
        std::swap(size, mat.size);

        return *this;
    }

    template <typename Data>
    bool MatrixVec<Data>::operator==(const MatrixVec &mat) const noexcept
    {
        if (columnsNumber == mat.columnsNumber && rowsNumber == mat.rowsNumber)
            if (rowVector == mat.rowVector)
                return true;

        return false;
    }

    template <typename Data>
    bool MatrixVec<Data>::operator!=(const MatrixVec &mat) const noexcept
    {
        return !(*this == mat);
    }

    template <typename Data>
    void MatrixVec<Data>::RowResize(const unsigned long n_size)
    {
        if (n_size > 0)
        {
            size = n_size * columnsNumber;
            rowVector.Resize(size);
            rowsNumber = n_size;
        }
        else
        {
            rowsNumber = 0;
            Vector<Data>::Clear();
        }
    }

    template <typename Data>
    void MatrixVec<Data>::ColumnResize(const unsigned long newColumnNumber)
    {
        if (newColumnNumber == 0){    
            columnsNumber = 0;
            Vector<Data>::Clear();
        }
        else if (columnsNumber != newColumnNumber)
        {
            size = rowsNumber * newColumnNumber;
            Vector<Data> tmpMatrixVec(size);

            unsigned long limit = (newColumnNumber > columnsNumber) ? columnsNumber : newColumnNumber;
            for (unsigned long i = 0; i < rowsNumber; ++i)
            {
                for (unsigned long j = 0; j < limit; ++j)
                {
                    std::swap(tmpMatrixVec[i *newColumnNumber + j], rowVector[i *columnsNumber + j]);
                }
            }
            columnsNumber = newColumnNumber;
            std::swap(tmpMatrixVec, rowVector);
            tmpMatrixVec.Clear();
        }
    }

    template <typename Data>
    Data &MatrixVec<Data>::operator()(const unsigned long row, const unsigned long column)
    {
        return const_cast<Data &>(static_cast<const Matrix<Data> *>(this)->operator()(row, column));
    }

    template <typename Data>
    const Data &MatrixVec<Data>::operator()(const unsigned long row, const unsigned long column) const
    {
        if (row < rowsNumber && column < columnsNumber)
        {
                return rowVector[(row * columnsNumber) + column];
        }
        else
            throw std::out_of_range("Cell doesn't exists!");
    }

    template <typename Data>
    void MatrixVec<Data>::Clear()
    {
        rowsNumber = columnsNumber = size = 0;
    }

    template <typename Data>
    void MatrixVec<Data>::MapPreOrder(const MapFunctor mf, void *par)
    {
        rowVector.MapPreOrder(mf, par);
    }

    template <typename Data>
    void MatrixVec<Data>::MapPostOrder(const MapFunctor mf, void *par)
    {
        rowVector.MapPostOrder(mf, par);
    }

    template <typename Data>
    void MatrixVec<Data>::FoldPreOrder(const FoldFunctor ff, const void *par, void *acc) const
    {
        rowVector.FoldPreOrder(ff, par, acc);
    }

    template <typename Data>
    void MatrixVec<Data>::FoldPostOrder(const FoldFunctor ff, const void *par, void *acc) const
    {
        rowVector.FoldPostOrder(ff, par, acc);
    }
    /* ************************************************************************** */

}
