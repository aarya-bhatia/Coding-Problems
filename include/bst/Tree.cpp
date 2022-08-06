#include "Tree.hpp"
#include <iostream>

template<class T>
static size_t getSize(TreeNode<T> *root)
{
    if(!root) return 0;
    return 1 + getSize(root->left) + getSize(root->right);
}

template<class T>
Tree<T>::Tree(TreeNode<T> *root)
{
    _root = root;
    _size = getSize(root);
}

template<class T> Tree<T>::~Tree()
{
    clear();
}

template<class T>
void Tree<T>::insert(const T&data) 
{ 
    insert(_root, data); 
}

template<class T>
void Tree<T>::clear() 
{ 
    clear(_root); 
    _root = nullptr;
    _size = 0;
}

template<class T>
bool Tree<T>::erase(const T&data) 
{ 
    return erase(_root, data); 
}

template<class T>
void Tree<T>::print() const 
{ 
    print(_root, 0); 
    std::cout << "\n";
}

template<class T>
size_t Tree<T>::size() const 
{ 
    return _size; 
}

template<class T> void Tree<T>::insert(TreeNode<T> *&current, const T &data)
{
    if(!current)
    {
        current = new TreeNode<T>();
        current->data = data;
        _size++;
    }
    else if(data < current->data)
    {
        insert(current->left, data);
    }
    else if(data > current->data)
    {
        insert(current->right, data);
    }
}

template<class T> bool Tree<T>::erase(TreeNode<T> *&current, const T&data)
{
    if(!current) 
    {
        return false;
    }
    else if(data < current->data) 
    {
        return erase(current->left, data);
    } 
    else if(data > current->data) 
    {
        return erase(current->right, data);
    }
    else
    {
        if(!current->left && !current->right)
        {
            delete current;
            current = nullptr;
            _size--;
            return true;
        } 

        TreeNode<T> *replace = nullptr;

        if(!current->left)
        {
            TreeNode<T> *node = current->right;
            while(node->left) node = node->left;
            replace = node->left;
            node->left = nullptr;
        }
        else
        {
            TreeNode<T> *node = current->left;
            while(node->right) node = node->right;
            replace = node->right;
            node->right = nullptr;
        }

        if(replace)
        {
            replace->left = current->left;
            replace->right = current->right;
            current = replace;
            _size--;
            return true;
        }

        return false;
    }
}

template<class T> Tree<T> *Tree<T>::clone(TreeNode<T> *node) const
{
    if(!node) { return nullptr; }

    TreeNode<T> *tree = new TreeNode<T> { node->data }; 
    tree->left = clone(node->left);
    tree->right = clone(node->right);
    return tree;
}

template<class T> Tree<T> *Tree<T>::clone() const { 
    TreeNode<T> *treeRoot = clone(_root); 
    Tree<T> *tree = new Tree<T>();
    tree->_root = treeRoot;
    tree->_size = _size;
    return tree;
}


template<class T> void Tree<T>::print( const TreeNode<T> *node, int depth ) const
{
    if(!node)
    {
        return;
    }

    std::cout << node->data << " ";

    print(node->left, depth+1);
    print(node->right, depth+1);
}

template<class T> void Tree<T>::clear(TreeNode<T> *node)
{
    if(!node) 
    {
        return;
    }

    if(node->left) 
    {
        clear(node->left);
    }

    if(node->right) 
    {
        clear(node->right);
    }

    delete node;
}

template<class T> Tree<T>::Iterator::Iterator(TreeNode<T> *current): 
    _current(current), _queue()
{
}

template<class T> 
const T &Tree<T>::Iterator::operator*() const
{
    return _current->data;
}

template<class T> 
typename Tree<T>::Iterator &Tree<T>::Iterator::operator++()
{
    if(_current)
    {
        if(_current->left) _queue.push(_current->left);
        if(_current->right) _queue.push(_current->right);

        if(!_queue.empty())
        {
            _current = _queue.front();
            _queue.pop();
        }
        else
        {
            _current = nullptr;
        }
    }

    return *this;
}

template<class T> 
typename Tree<T>::Iterator Tree<T>::Iterator::operator++(int)
{
    Tree<T>::Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<class T> 
bool Tree<T>::Iterator::operator!=(Tree<T>::Iterator other) const
{
    return _current != other._current;
}
