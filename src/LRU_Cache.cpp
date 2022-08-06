#include <bits/stdc++.h>
using namespace std;

struct _Node
{
    _Node *prev;
    _Node *next;
    int key;
    int val;

    _Node();
};

_Node::_Node()
{
    prev = next = nullptr;
    key = val = 0;
}

class LRUCache
{
private:
    _Node *head;
    _Node *tail;
    unordered_map<int, _Node *> mp;
    int capacity;
    int size;

public:
    LRUCache(int capacity);
    ~LRUCache();
    int get(int key);
    void put(int key, int value);

private:
    void moveToFront(_Node *node);
    void printCache();
};

void LRUCache::printCache()
{
    _Node *itr = head->next;
    while (itr != tail)
    {
        cout << "(" << itr->key << "," << itr->val << ") ";
        itr = itr->next;
    }
    cout << endl;
    cout << "map: {";

    for (pair<int, _Node *> it : mp)
    {
        auto key = it.first;
        auto val = it.second;
        printf("%d->%p ", key, val);
    }
    cout << "}\n";
}

LRUCache::LRUCache(int capacity) : capacity(capacity)
{
    size = 0;
    head = new _Node();
    tail = new _Node();

    head->next = tail;
    tail->prev = head;
}

LRUCache::~LRUCache()
{
    _Node *itr = head->next;

    while (itr != tail)
    {
        _Node *tmp = itr->next;
        delete itr;
        itr = tmp;
    }

    delete head;
    delete tail;

    head = tail = nullptr;
}

int LRUCache::get(int key)
{
    // cout << "get " << key << endl;

    if (mp.find(key) == mp.end())
    {
        return -1;
    }

    int retval = mp[key]->val;
    moveToFront(mp[key]);
    // printCache();

    return retval;
}

void LRUCache::put(int key, int value)
{
    // cout << "put " << key << " -> " << value << endl;

    if (mp.find(key) != mp.end())
    {
        // update value of existing node

        _Node *target = mp[key];
        target->val = value;

        // node was recently used so move it to front of list

        moveToFront(target);
        mp[key] = head->next;
    }
    else
    {
        // Insert at start of list
        _Node *node = new _Node();

        node->key = key;
        node->val = value;

        node->prev = head;
        node->next = head->next;

        node->prev->next = node;
        node->next->prev = node;

        mp[key] = node;

        size++;

        // handle overflow
        if (size > capacity)
        {
            // Remove least recently used node
            // This is at the end of list
            _Node *last = tail->prev;
            last->prev->next = tail;
            tail->prev = last->prev;

            cout << "evicted: " << last->key << endl;
            mp.erase(last->key);

            delete last;
        }
    }

    // printCache();
}

void LRUCache::moveToFront(_Node *node)
{
    if (node == head->next)
        return;

    // update the adjacent pointers of node

    node->prev->next = node->next;
    node->next->prev = node->prev;

    // insert node after head

    node->next = head->next;
    node->prev = head;

    node->next->prev = node;
    node->prev->next = node;
}

int main()
{
    vector<int> output;
    LRUCache lRUCache(2);
    lRUCache.put(1, 1);                // cache is {1=1}
    lRUCache.put(2, 2);                // cache is {1=1, 2=2}
    output.push_back(lRUCache.get(1)); // return 1
    lRUCache.put(3, 3);                // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    output.push_back(lRUCache.get(2)); // returns -1 (not found)
    lRUCache.put(4, 4);                // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    output.push_back(lRUCache.get(1)); // return -1 (not found)
    output.push_back(lRUCache.get(3)); // return 3
    output.push_back(lRUCache.get(4)); // return 4

    cout << "output\n";
    for (int i : output)
        cout << i << endl;
}