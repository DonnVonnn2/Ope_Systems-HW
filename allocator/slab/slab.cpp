#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//Donovan Frazier
using namespace std;

struct sevenEleven              //call it seven eleven cuz it got that big gulp
{
    vector<char*> slab;       //holds da addresses :3
    vector<vector<char*>> gulp;       //number of gulps :3
    const int GULPSIZE = 128;       //gulp size so i can do quik mmafs
};

void slabber(sevenEleven&);         // makes slabs :3
// bool isEmpty(sevenEleven);
void drinkSpiller(sevenEleven&);        //clears slabs and gulps
void slabCounter(sevenEleven);          // counts the  slab
void slabFree(sevenEleven&, int);           // only clears the slabs, used for testing only.
void allocTest(sevenEleven&);
void slabTooFree(sevenEleven&);
void slabFree2(sevenEleven&);        // double free.
void manualAdd(sevenEleven&, void*);
void destructor(sevenEleven&);      // becaues ya boi wack and couldn't make a real destructor

int main()
{
    int16_t = 0x12345;
    sevenEleven allcator;
    slabber(allcator);
    slabber(allcator);
    slabCounter(allcator);
    drinkSpiller(allcator);
    allocTest(allcator);
    allcator.slab.resize(255);
    slabFree(allcator,19);
    slabFree2(allcator);
    manualAdd(allcator);

    return 0;
}


void slabber(sevenEleven& cator)
{

    cout << "Gulping\n";
    if(!cator.slab.empty())
        cator.slab.clear();


    for(int i = 0; i < cator.GULPSIZE; i++)
    {
       char* data = new char;
       *data = 'a';
       cator.slab.push_back(data);
       cout << "Allocating slab " << (cator.GULPSIZE - 1) - i << endl;
    }
    cator.gulp.push_back(cator.slab);
    cator.slab.clear();
}

bool isEmpty(sevenEleven cat)
{
    char* sample = cat.slab.at(4);
    if(sample == nullptr)
        return true;
    
    return false;
}


void slabCounter(sevenEleven cat)
{
    int estimate = 0;
    int counter = 0;

    for(int i = 0; i < cat.gulp.size(); i++)
    {
        estimate += cat.gulp.at(i).size();
    }
    
    cout << "Number of available slabs should be: " << estimate;

    for(int i = 0; i < cat.gulp.size(); i++)
    {
        vector<char*> slam = cat.gulp[i];
        for(int e = 0; e < slam.size(); e++)     
        {
            if(*slam[e] == 'a')
            {
                counter++;
            }
        }
    }
    if(counter == estimate)
    {
        cout << " Is: " << counter << " (Correct)\n";
    }
    else
    {
        cout << " Is: " << counter << " (Wrong)\n";
        exit(1);
    }

}

void slabFree(sevenEleven& cat, int index)
{
    if(cat.slab[index] == nullptr)
    {
        cout << "Correctly caught error: attempting to free nullptr\n";
    }
    else
    {
        cout << "Did Not Catch Attempt to Free NULL\n";
        delete cat.slab[index];
        cat.slab[index] = nullptr;      //might as well free it lmao
        exit(1);
    }
}


void drinkSpiller(sevenEleven& cat)
{
    cout << "Releasing all Allocated Buffers\n";
    while(cat.gulp.size()> 0)
    {
        cat.slab.clear();
        cat.slab = cat.gulp.back();
        cat.gulp.pop_back();
        for(int i = 0; i < cat.slab.size() - 1; i++)
        {
            char* slub = cat.slab[i];
            delete slub;
            slub = nullptr;
        }
    }
    cat.slab.clear();
}

void allocTest(sevenEleven& cat)
{
    void* mem;     // free'd space memory
    char* mem2 = new char;         //realloced space memeory
    *mem2 = 'a';
    cat.slab.push_back(mem2);
    cout << "Allocating Slab " << 256 - cat.slab.size() << endl;
    mem = &cat.slab.back();
    delete cat.slab.back();
    cat.slab.back() = nullptr;
    cat.slab.pop_back();
    cat.slab.push_back(mem2);
    cout << "Allocating Slab " << 256 - cat.slab.size() << endl;
    if(mem == &cat.slab.back())
    {
        cout << "Alloc / Free / Alloc Test succeeded\n";
    }
    else
    {
        cout << "Alloc / Free / Alloc Test \" failed\n";
        exit(1);
    }


    
}

void slabTooFree(sevenEleven cat)
{
    if(cat.slab.size() > 256 || cat.gulp.size() >= 2)
    {
        cout << "Correctly caught error: free'd too many slabs\n";
    }
    else{
        cout << "Did Not Catch Freeing of Too Many Buffers\n";
        exit(1);
    }

}

void slabFree2(sevenEleven& cat)
{
    cout << "Allocating Slab " << 256 - cat.slab.size() << endl;
    char* mem = new char;
    *mem = 'a';
    cat.slab[21] = mem;
    cout << "Allocating Slab " << 256 - cat.slab.size() << endl;
    delete mem;
    mem = nullptr;
    mem = new char;
    *mem = 'a';
    cat.slab[22] = mem;
    delete cat.slab[22];
    cat.slab[22] = nullptr;

    if(cat.slab[22] == nullptr)
    {
        cout << "Correctly caught error: attempting double free\n";
    }
    else{
        cout << "Did Not Catch Attempt to Double Free\n";
        exit(1);
    }

}


void destructor(sevenEleven& cat)
{
    cout << "Program Ending - Destructors should now run\n";



    while(cat.gulp.size()> 0)
    {
        cat.slab.clear();
        cat.slab = cat.gulp.back();
        cat.gulp.pop_back();
        for(int i = 0; i < cat.slab.size() - 1; i++)
        {
            char* slub = cat.slab[i];
            delete slub;
            slub = nullptr;
        }
    }
    
}

void manualAdd(sevenEleven& cat, int16_t add)
{

    for(int i = 0; i < cat.gulp.size(); i++)
    {
        cat.slab = cat.gulp[i];
        for(int e = 0; e < cat.slab.size(); e++)
        {
            if(&cat.slab[e] != add)
            {
                cout << "Correctly caught error: attempting to free location not in any gulp\n";
            }
            else if(&cat.slab[e] == add)
            {
                cout << "Did Not Catch Attempt to Free BAD Address\n";
            }
        }

    }
}