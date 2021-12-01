
namespace lasd
{

    /* ************************************************************************** */

template <typename Data>
void BinaryTreeLnk<Data>::BTFromContainer(unsigned long index, NodeLnk *node, const LinearContainer<Data> &cont)
{
    if(index *2 + 1 < size){
        node->left = new NodeLnk(cont[index*2+1]);
        BTFromContainer(index*2+1, node->left, cont);
    }

    if(index *2 + 2 < size){
        node->right = new NodeLnk(cont[index*2+2]);
        BTFromContainer(index*2+2, node->right, cont);
    }
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data> &cont)
{
    size = cont.Size();
    root = new NodeLnk(cont[0]);
    BTFromContainer(0, root, cont);
}

template <typename Data>
void BinaryTreeLnk<Data>::TreeCopy(const NodeLnk &BTnode, NodeLnk* node)
{

    if(BTnode.HasLeftChild()){
        node->left = new NodeLnk(BTnode.LeftChild().Element());
        TreeCopy(BTnode.LeftChild(), node->left);
    }

    if(BTnode.HasRightChild()){
        node->right = new NodeLnk(BTnode.RightChild().Element());
        TreeCopy(BTnode.RightChild(), node->right);
    }
}


template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk &BTlnk)
{
    size = BTlnk.size;
    root = new NodeLnk(BTlnk.Root().Element());
    if (size > 0)
        TreeCopy(BTlnk.Root(), root);
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk &&BTlnk) noexcept
{
    std::swap(size, BTlnk.size);
    std::swap(root, BTlnk.root);
}

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk()
{
    if(root != nullptr)
        Clear();
}

template <typename Data>
BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk &BTlnk)
{
    BinaryTreeLnk<Data> *tmp = new BinaryTreeLnk<Data>(BTlnk);
    std::swap(*this, *tmp);
    delete tmp;
    return *this;
}

template <typename Data>
BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(BinaryTreeLnk &&BTlnk) noexcept
{
    std::swap(size, BTlnk.size);
    std::swap(root, BTlnk.root);

    return *this;
}

template <typename Data>
void BinaryTreeLnk<Data>::Clear()
{
    size = 0;
    delete root;
    root = nullptr;
}
/* ************************************************************************** */
}
