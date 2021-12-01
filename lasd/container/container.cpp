
namespace lasd {

/* ************************************************************************** */
template <typename Data>
void auxFoldExists(const Data& dat, const void* val, void* exists){
    if(dat == *((Data *)val))
        *((bool*) exists) = true;
}

template <typename Data>
bool FoldableContainer<Data>::Exists(const Data& dat) const noexcept{
    bool exists = false;
    FoldPreOrder(&auxFoldExists<Data>, &dat, &exists);
    return exists;
} 
/* ************************************************************************** */

}
