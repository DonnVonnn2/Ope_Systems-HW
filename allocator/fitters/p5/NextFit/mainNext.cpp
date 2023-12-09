#include <iostream>
#include <getopt.h>

#include "handleDataNext.h"
#include "nextFit.h"

using namespace std;

int main(int argc, char * argv[])
{
    //checks the command line args
    //void PrintUsage();
    bool HandleOptions(int argc, char ** argv, int &);

    int kibibytes = 512;

    if (!HandleOptions(argc, argv, kibibytes)) {
		//PrintUsage();
		return 1;
	}

    string file("../tests/test_15.txt");
    handleDataNext hd(file);
    nextFit nf(file);


    return 0;
}


void PrintUsage() {
	cerr << "Usage:" << endl;
	cerr << "-k int          optional - an integer" << endl;
	cerr << "Note that without care, a string is just one \"word\"" << endl;
}

bool HandleOptions(int argc, char ** argv, int & kibibytes) {
	int c;
	while ((c = getopt(argc, argv, "h:k:")) != -1) {
		switch (c) {
			default:
			case 'h':
                PrintUsage();
				return false;

			case 'k':
				kibibytes = atoi(optarg);
				break;
		}
	}

	return 0;
}























/*bool HandleOptions(int argc, char ** argv, char** pName) {
    int c;
    bool argTrue = false;

    //checks args to see if they mach any valid command line options, execute switch statements if this is the case
    while ((c = getopt(argc, argv, "h:k:")) != -1) {
        argTrue = true;       

		switch (c){
            default:
            case 'h': //if '-h' is present
            {
                *pName = optarg;
    
                break;

            }
            case 'k': //if '-k' is present
            {
                *sPName = optarg;

                break;

            }
        }
    }

    return argTrue;

}*/