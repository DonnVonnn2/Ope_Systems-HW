#include <iostream>
#include <iomanip>

#include "nextFit.h"
#include "handleDataNext.h"
#include <vector>

using namespace std;

nextFit::nextFit(string dataFile)
{
    location = 0;

    //free memory
    Mem m;
    m.index = 0;
    m.start = 0;
    m.length = 512;
    freeList.push_back(m);

    //create handleDataNext to read the file
    //get the contents from file 
    handleDataNext hd = handleDataNext(dataFile);
    vector<string> fileContents = hd.getContents();

    //if the vector is not 0 sort through it other wise it is an error and there are no commands
    if(fileContents.size() != 0)
    {
        //for each string in the vector
        //read the command
        //get the name of the job if that command takes a name
        //use the string command to call the command()
        for(uint i = 0; i < fileContents.size(); i++)
        {
            if(fileContents[i].size() != 0)
            {
                string command = fileContents[i].substr(0, 1); //returns the command name
                if(command == "p")
                {
                    print();
                }
                else if (command == "a")
                {
                    string strNum = fileContents[i].substr(2); //returns the number
                    int num = stoi(strNum);

                    allocate(num);
                }
                else if (command == "f")
                {
                    string strNum = fileContents[i].substr(2); //returns the number
                    int num = stoi(strNum);

                    release(num);
                }
            }
        }
    }
    else
    {

    }
}

void nextFit::allocate(int num)
{
    if(allocateList.size() != 0)
    {
        Mem m;
        m.index = allocateList.size();
        m.start = allocateList[allocateList.size() - 1].start + allocateList[allocateList.size() - 1].length;
        m.length = num;
        allocateList.push_back(m);
    }
    else
    {
        Mem m;
        m.index = 0;
        m.start = 0;
        m.length = num;
        allocateList.push_back(m);
    }
    int locA  = allocateList.size() - 1;
    cout << "Next Fit Starting index: " << allocateList[0].index << " Start: " << allocateList[locA].start << " Length: " << freeList[0].length << endl;
    
    freeList[0].start += num;
    freeList[0].length = freeList[0].length - num;
    
    if(freeList[0].length != 0)
    {
        int locB = freeList.size() - 1;
        cout << "Next Fit Ending index: " << freeList[locB].index << " Start: " << freeList[locB].start << " Length: " << freeList[locB].length << endl;
    }
    else
    {
        freeList.pop_back();
        cout << "Next Fit Ending index: " << freeList[0].index << " Free List is Empty" << endl;
    }

    cout << "Allocated: " << num << " kibibytes starting at: " << allocateList[locA].start << endl << endl;
     
}

void nextFit::coalesce()
{
    if(freeList.size() >= 1)
    {
        for(uint i = 1; i < freeList.size(); i++ ){
            Mem m = freeList[i];
            if((freeList[i-1].start + freeList[i-1].length) == m.start)
            {
                freeList[i-1].length += m.length;
                freeList.erase(freeList.begin() + i);
                cout << "Coalesce at: " << freeList[i-1].start << " adding " << m.length << endl;
                coalesce();
                return;
            }
        }
    }
}
void nextFit::release(int num)
{
    for(uint i = 0; i < allocateList.size(); i++)
    {
        if(num == allocateList[i].start)
        {
            Mem m;
            m.index = i;
            m.start = allocateList[i].start;
            m.length = allocateList[i].length;
            freeList.push_back(m); 
            allocateList.erase(allocateList.begin() + i); 
        }
    }
    coalesce();
    cout << "Freed block starting at: " << num << endl << endl;
}

void nextFit::print()
{
    printFree();
    printAllocate();
}

void nextFit::printFree()
{
    if(freeList.size() != 0)
    {
        cout << "Free List" << endl;
        cout << right << setw(6) << "Index" << setw(8) << "Start" <<setw(8) << "Length" << endl;
        for(uint i = 0; i < freeList.size(); i++)
        {
            cout << right << "[" << setfill('0') << setw(4) << freeList[i].index << "]" << setfill(' ') << setw(8) << freeList[i].start << setw(8) << freeList[i].length << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "Free List is empty" << endl << endl;
    }
}

void nextFit::printAllocate()
{
    if(allocateList.size() != 0)
    {
        cout << "Allocated List" << endl;
        cout << right << setw(6) << "Index" << setw(8) << "Start" <<setw(8) << "Length" << endl;
        for(uint i = 0; i < allocateList.size(); i++)
        {
            cout << right << "[" << setfill('0') << setw(4) << allocateList[i].index << "]" << setfill(' ') << setw(8) << allocateList[i].start << setw(8) << allocateList[i].length << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "Allocated List is empty" << endl << endl;
    }
}
