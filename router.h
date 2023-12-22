#pragma once
#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<fstream>
#include"grapher.h"
using namespace std;
class router
{
private:
    int gridsize,capacity,numnet,loadbuffer;
    // vector<int> posx1,posy1,posx2,posy2;
    vector<int> positions[4]; //(x1,y1)(x2,y2)
public:    
    router();
    void getroutdata(string filename);
    void printresult();
    void sssp();
};
inline router::router(){
    gridsize = 0;
    capacity = 0;
    numnet = 0;
}

inline void router::getroutdata(string filename){
    ifstream handler;
    handler.open(filename);
    if(handler.is_open()){        
        string strbuffer;
        handler>>strbuffer>>gridsize>>gridsize;
        handler>>strbuffer>>capacity;
        handler>>strbuffer>>strbuffer>>numnet; //fin>>"num" "net" and netnumber
        vector<int> buffer(numnet);
        for (int i = 0; i < 4; i++){
            positions[i] = buffer;
        }
        // posx1 = buffer;
        // posx2 = buffer;
        // posy1 = buffer;
        // posy2 = buffer;
        for (int iter = 0; iter < numnet; iter++){
            // handler>>loadbuffer>>posx1[iter]>>posy1[iter]>>posx2[iter]>>posy2[iter];
            handler>>loadbuffer>>positions[0][iter]>>positions[1][iter]>>positions[2][iter]>>positions[3][iter];
        }
        handler.close();
    }
    else{
        cout << "Error: the input file is not opened!!" << endl;
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
        exit(1);
    }   
    return;
}
//debug use
inline void router::printresult(){
    cout<<"gridnum "<<gridsize;
    cout<<"\ncapacity "<<capacity;
    cout<<"\nnumnet "<<numnet<<endl;
    for (int i = 0; i < numnet; i++){
        cout<<i<<" "<<positions[0][i]<<" "<<positions[1][i]<<" "<<positions[2][i]<<" "<<positions[3][i]<<endl;
    }    
    return;
}

// need to pass gridsize,capacity,positions
inline void router::sssp(){   
    grapher dgraph(gridsize,capacity,numnet);
    dgraph.settile(positions);
    dgraph.printtilemap();
    dgraph.printedgemap();

}
