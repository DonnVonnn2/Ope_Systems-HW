#include "handleDataBest.h"
#include <iostream>
#include <fstream>

using namespace std;

handleDataBest::handleDataBest(string dataFile)
{
    parse(dataFile);
}

void handleDataBest::parse(string dataFile)
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

vector<string> handleDataBest::getContents()
{
    return fileContent;
}