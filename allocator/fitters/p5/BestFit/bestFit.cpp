#include <iostream>
#include <iomanip>

#include "bestFit.h"
#include "handleDataBest.h"
#include <vector>

using namespace std;

bestFit::bestFit(string dataFile)
{
    //free memory
    Mem m;
    m.index = 0;
    m.start = 0;
    m.length = 512;
    freeList.push_back(m);

    //create handleDataNext to read the file
    //get the contents from file 
    handleDataBest hd = handleDataBest(dataFile);
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
                /*else if (command == "a")
                {
                    string strNum = fileContents[i].substr(2); //returns the number
                    int num = stoi(strNum);

                    //allocate(num);
                }
                else if (command == "f")
                {
                    string strNum = fileContents[i].substr(2); //returns the number
                    int num = stoi(strNum);

                    //release(num);
                }*/
            }
        }
    }
    else
    {

    }
}

void bestFit::print()
{
    printFree();
    printAllocate();
}

void bestFit::printFree()
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

void bestFit::printAllocate()
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