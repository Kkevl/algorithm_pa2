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
public:   
    vector<int> positions[4],routingnum; 
    vector<vector<int>> anservector;
    router();
    void getroutdata(string filename);
    void sssp();
    int getnumnet(){ return numnet;}
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
        for (int i = 0; i < 4; i++){    //initialize the block for positions
            positions[i] = buffer;
        }
        for (int iter = 0; iter < numnet; iter++){
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

// need to pass gridsize,capacity,positions
inline void router::sssp(){   
    grapher dgraph(gridsize,capacity,numnet);
    // remember that position will be inverted!
    for (int i = 0; i < numnet; i++){    
        dgraph.dijkstra(positions[0][i],positions[1][i], positions[2][i],positions[3][i]);
        dgraph.refindpath(i,positions[0][i],positions[1][i], positions[2][i],positions[3][i]);
    }
    anservector = dgraph.ansvector;
    routingnum = dgraph.ansroutenum;
}
