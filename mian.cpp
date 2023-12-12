#include<iostream>
#include"router.h"
using namespace std;
int main(int argc, char **argv)
{	
	if(argc != 3)
    {
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
        exit(1);
    }
    //my function to solve the answer
    router Rout;
    Rout.getroutdata(argv[1]);
    // parse the input file
    cout << "======================" << endl;
    cout << "        Parser        " << endl;
    cout << "======================" << endl;

    // open the output file
    fstream fout;
    fout.open(argv[2],fstream::out);
    if(!fout.is_open())
    {
        cout << "Error: the output file is not opened!!" << endl;
	    exit(1);
    }

    // output something to the output file
    fout<<endl;
    for (int i = 0; i < 0; i++)
    {
        cout<<"Chord(";
        fout<<endl;
    }
    return 0;
}
