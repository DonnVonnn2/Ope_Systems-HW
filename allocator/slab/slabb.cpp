#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct sevenEleven              //call it seven eleven cuz it got that big gulp
{
    vector<char*> slabb;       //number of gulps :3
    
    const int GULPSIZE = 128;       //gulp size so i can do quik mmafs
};

void slabber();         // makes slabs :3
// bool isEmpty(sevenEleven);
void drinkSpiller();        //clears slabs and gulps
void slabCounter();          // counts the  slab
void slabClear();           // only clears the slabs, used for testing only.

sevenEleven MEM;        //global since its used basically everywhere


int main()
{
    //sets up the slabs and stuff, starting off null
    // for(char* i : MEM.usedSlabs )
    // {
    //     i = nullptr;
    // }
    // MEM.gulp.resize(255);       //starts at 0: Update, this is the buffer now;

    slabber();
    slabber();

    return 0;
}

void slabber()
{
    if(MEM.slabb.size() > 256)
    {
        cout << "Max number of slabs reached.\n";
        exit(1);
    }
    for(int i = 0; i < MEM.GULPSIZE; i++)
    {
        char* data = new char;
        *data = 'a';
        MEM.slabb.push_back(data);
    }
    // MEM.gulp.push_back(*MEM.usedSlabs);
}