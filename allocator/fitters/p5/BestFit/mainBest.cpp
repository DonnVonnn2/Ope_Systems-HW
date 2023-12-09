#include <iostream>

#include "handleDataBest.h"
#include "bestFit.h"

using namespace std;

int main(int argc, char * argv[])
{
    //checks the command line args
    //bool HandleOptions(int argc, char ** argv, char**);
    string file("../tests/test_20.txt");
    handleDataBest hd(file);
    bestFit bf(file);

    return 0;
}