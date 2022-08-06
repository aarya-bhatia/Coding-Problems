#include <vector>
#include <functional>
#include <cstdlib>
#include <cstdio>

struct Person
{
    int height;
    int weight;
};

struct HeightCmp
{
    bool operator()(Person p1, Person p2) const { 
        return p1.weight > p2.weight; 
    }
};

int longestSubsequenceLength(std::vector<Person> elements, 
        std::function<int(Person)> fp)
{
    std::vector<int> subseqMaxElement;
    std::vector<int> subseqSize;

    for(int i = 0; i < elements.size(); i++)
    {
        int element = fp(elements[i]);
        bool found = false;

        for(int j = 0; j < subseqMaxElement.size(); j++)
        {
            if(element > subseqMaxElement[j])
            {
                found = true;
                subseqMaxElement[j] = element;
                subseqSize[j]++;
            }
        }

        if(!found)
        {
            subseqMaxElement.push_back(element);
            subseqSize.push_back(1);
        }
    }

    auto it = std::max_element(std::begin(subseqSize), std::end(subseqSize));
    if(it == subseqSize.end()) return -1;
    return *it;
}

/**
 * We need to find the longest sequence of persons in increasing
 * order of height and weight from given persons.
 */
int maxCircusTowerSize(std::vector<Person> entries)
{
    // Sort by height and find longest subsequence of weights

    qsort(entries.data(),entries.size(),sizeof(Person),
        [](const void *o1, const void *o2) {
            return ((const Person *) o1)->height - 
            ((const Person *) o2)->height;
        }
     );

    return longestSubsequenceLength(entries, [](Person p){return p.weight;});
}

int main()
{
    std::vector<Person> persons = {
        { 56, 90 },
        { 60, 85 },
        { 62, 91 },
        { 64, 57 },
        { 65, 60 },
        { 66, 62 },
        { 69, 80 },
        { 68, 70 },
    };

    int result = maxCircusTowerSize(persons);
    printf("Result:%d\n",result);

    return 0;
}
