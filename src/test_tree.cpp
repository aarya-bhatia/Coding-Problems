#include "Tree.hpp"

int main()
{
    Tree<char> t;

    t.insert('a');
    t.insert('b');
    t.insert('c');
    t.insert('e');
    t.erase('e');
    t.erase('a');
    t.insert('j');
    t.erase('k');

    t.print();

    t.clear();
    std::cout << "size: " << t.size() << "\n";

    for(int i = 0; i < 20; i++) 
    {
        t.insert('a' + i);
    }

    for(Tree<char>::Iterator it = t.begin(); it != t.end(); it++)
    {
        std::cout << *it << " ";
    }

    std::cout << "\n";

    return 0;
}
