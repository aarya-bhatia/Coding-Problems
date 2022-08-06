#include <list>
#include <unordered_map>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

#define debug true

class LFUCache
{
public:
    struct Node
    {
        int key;
        int value;
        int count;

        Node(int k = 0, int v = 0) : key(k), value(v)
        {
            count = 1;
        }

        std::string to_string() const
        {
            char res[30];
            sprintf(res, "( key:%d, value:%d, count:%d )", key, value, count);
            return std::string(res);
        }
    };

    LFUCache(int capacity);
    int get(int key);
    void put(int key, int value);

    typedef list<Node>::iterator Iterator;

    void log() const;

private:
    int _size;
    int _capacity;

    unordered_map<int, Iterator> _map;
    unordered_map<int, list<Node>> _list;
    set<int> _freq;

    bool _containsKey(int key) const;
    void _evict();
    Iterator _touch(int key);
};

void LFUCache::log() const
{
    cout << "[ ";

    for (const auto &it : _list)
    {
        for (const auto &nodeIt : it.second)
        {
            cout << nodeIt.to_string() << " ";
        }
    }

    cout << "]" << endl;
}

LFUCache::LFUCache(int capacity) : _capacity(capacity)
{
    _size = 0;
}

LFUCache::Iterator LFUCache::_touch(int key)
{
    // Get list iterator to node having given key
    Iterator i = _map[key];
    Node node = *i;

    // Remove node from old list as it's frequency is changed
    _list[node.count].erase(i);

    if (_list[node.count].empty())
    {
        _freq.erase(node.count);
    }

    // Insert node to front of new list as it is recently used
    node.count++;
    _map[key] = _list[node.count].insert(_list[node.count].begin(), node);

    _freq.insert(node.count);

    if (debug)
        cout << "Touched key: " << key << endl;
    if (debug)
        log();

    // Return new iterator
    return _map[key];
}

bool LFUCache::_containsKey(int key) const
{
    return _map.find(key) != _map.end();
}

void LFUCache::_evict()
{
    if (_size == _capacity)
    {
        // Get the lowest frequency of nodes
        int min_count = *_freq.begin();

        Node node = _list[min_count].back();
        if (debug)
            cout << "Evicted key: " << node.key << endl;

        // Remove the LRU node with this frequency
        _map.erase(node.key);
        _list[min_count].pop_back();
        _size--;

        if (_list[min_count].empty())
        {
            _freq.erase(min_count);
        }

        if (debug)
            log();
    }
}

int LFUCache::get(int key)
{
    if (debug)
        cout << "get " << key << endl;
    if (debug)
        log();

    if (!_containsKey(key))
    {
        return -1;
    }

    Iterator i = _touch(key);

    return i->value;
}

void LFUCache::put(int key, int value)
{
    if (_capacity <= 0)
        return;

    if (debug)
        cout << "put " << key << ", " << value << endl;
    
    if(debug)
        log();

    if (_containsKey(key))
    {
        Iterator i = _touch(key);
        i->value = value;
    }
    else
    {
        if (_size + 1 > _capacity)
            _evict(); // Evict before adding new node, so to not evict the new node itself

        // Add new node to list with frequency 1
        Node node(key, value);
        _map[key] = _list[node.count].insert(_list[node.count].begin(), node);
        _freq.insert(node.count);
        _size++;
    }
}

int main()
{
    vector<int> output;

    // LFUCache lfuCache(2);
    // lfuCache.put(1, 1);                // cache is {1=1}
    // lfuCache.put(2, 2);                // cache is {1=1, 2=2}
    // output.push_back(lfuCache.get(1)); // return 1
    // lfuCache.put(3, 3);                // lfu key was 2, evicts key 2, cache is {1=1, 3=3}
    // output.push_back(lfuCache.get(2)); // returns -1 (not found)
    // output.push_back(lfuCache.get(3)); // returns -1 (not found)
    // lfuCache.put(4, 4);                // lfu key was 1, evicts key 1, cache is {4=4, 3=3}
    // output.push_back(lfuCache.get(1)); // return -1 (not found)
    // output.push_back(lfuCache.get(3)); // return 3
    // output.push_back(lfuCache.get(4)); // return 4

    // cout << "output\n";
    // for (int i : output)
    //     cout << i << endl;

    // cout << "--------------------------------\n";
    
    LFUCache lfu(1);
    cout << lfu.get(1) << endl;
    lfu.put(2,1);
    cout << lfu.get(2) << endl;
    lfu.put(3,2);
    cout << lfu.get(2) << endl;
    cout << lfu.get(3) << endl;

    cout << "output\n";
    for (int i : output)
        cout << i << endl;
}