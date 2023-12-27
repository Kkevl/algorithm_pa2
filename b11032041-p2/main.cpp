#include<iostream>
#include"router.h"
using namespace std;
int main(int argc, char **argv){	
	if(argc != 3){
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
        exit(1);
    }
    //my function to solve the answer
    router Rout;
    Rout.getroutdata(argv[1]);
    Rout.sssp();
    // openy the output file
    fstream fout;
    fout.open(argv[2],fstream::out);
    if(!fout.is_open()){
        cout << "Error: the output file is not opened!!" << endl;
	    exit(1);
    }
    // output something to the output file
    for (int i = 0; i < Rout.getnumnet(); i++){    
        fout<<i<<" "<<Rout.routingnum[i]<<endl;
        for (int j = Rout.routingnum[i]*2+1 ; j > 1; j-=2){
            fout<<Rout.anservector[i][j-1]<<" "<<Rout.anservector[i][j]<<" "
                <<Rout.anservector[i][j-3]<<" "<<Rout.anservector[i][j-2]<<endl;
        }
    }
    return 0;
}
