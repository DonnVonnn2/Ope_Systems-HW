#include <iostream>
#include "handleDataNext.h"
#include <fstream>

using namespace std;

handleDataNext::handleDataNext(string dataFile)
{
    parse(dataFile);
}

void handleDataNext::parse(string dataFile)
{
    ifstream infile(dataFile);
    string line;
    //goes line by line of the file adding each line to a new element in the vector
    while (getline(infile, line))
    {
        fileContent.push_back(line);
    }
    infile.close();
}

vector<string> handleDataNext::getContents()
{
    return fileContent;
}