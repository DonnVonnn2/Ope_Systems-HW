#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>


void PrintOptions();        //prints the arguments required

int main(int argc, char * argv[])
{

    if (argc <= 1)  // checks to see if there are actuall arguments. if not asks to enter arguments and shows the options
    {
        perror("Please enter arguments."); // this is it cheif
        PrintOptions();
        return 1;
    }
    int number = 1;     //printable interger
    char *stringp = "a";    //printable string
    int parse;      //int that will be used to parse through the arguments
    // the part where it parses through the arguments

    while((parse = getopt(argc, argv, "hn:U:")) != -1) 
    {
         switch (parse)
         {
         case 'h':
              PrintOptions();
              return 1;
    
         case 'n':
             number = atoi(optarg);
             break;
         case 'U':
             stringp = optarg;
             break;
          }

    }
    number = number * number;

    printf("%s \n", stringp);
    printf("%d \n",number);
    // prints work, the code in ArgsManager doesn't send to the argumetns here because you didnt return by referance
    return 0;
}


void PrintOptions()
{
    perror("Usage: \n");
    perror("-h help             Shows this message\n");
    perror("-n interger         necessary for program\n");
    perror("-U string           necessary for program\n");



}

bool ArgsManager(int argc, char ** argv, int num, char *strng)
{
    int parse;

    while((parse = getopt(argc, argv, "hn:U:")) != -1) 
    {
         switch (parse)
         {
         case 'h':
              return false;
    
         case 'n':
             num = atoi(optarg);
             break;
         case 'U':
             strng = optarg;
             break;
          }

    }


    return parse >= -1;
}
