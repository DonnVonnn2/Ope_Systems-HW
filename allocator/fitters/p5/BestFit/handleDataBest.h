#include <iostream>
#include <vector>

using namespace std;

class handleDataBest
{
public:
    handleDataBest(string dataFile); //takes in the datafile and calls parse
    void parse(string dataFile); //parses the data
    vector<string> getContents(); //returns the contents of the file
private:
    vector<string> fileContent; //vector of strings where each element holds a line of the file
};