#include <iostream>
#include <vector>

using namespace std;

struct Mem
{
    int index;
    int start;
    int length;
};

class nextFit
{
public:
    nextFit(string dataFile);

private:
    void print();
    void allocate(int num);
    void release(int num);
    void coalesce(int num);
    void printFree();
    void printAllocate();

    vector<Mem> freeList;
    vector<Mem> allocateList;
    int location;
};