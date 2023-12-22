#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include"router.h"
using namespace std;
class grapher
{
private:
    int gridsize,capacity,numnet,mode;
public:
    grapher(int,int,int );
    vector<vector<int>> tilemap,ansvector;
    vector<vector<int>> edgemapx,edgemapy;
    // create a map that represent every tile, each should refresh every time dijkstra
    void printtilemap();
    // create " " to represent each edge between each tile
    void printedgemap();
    void settile(vector<int> pointers[]);
    void traverse(int, int, int, int);

};

inline grapher::grapher(int grid,int cap,int net){
    vector<vector<int>> buffer(grid,vector<int>(grid,0));
    vector<vector<int>> netbuffer(net,vector<int>(grid,0));
    capacity = cap;
    gridsize = grid;
    numnet = net;
    tilemap = buffer;
    edgemapx = buffer;
    edgemapy = buffer;
    ansvector = netbuffer;
}

inline void grapher::printtilemap(){
    for (int i = 0; i < gridsize; i++){
        for (int j = 0; j < gridsize; j++){
            cout<<tilemap[i][j]<<" ";
        }
        cout<<endl;
    }    
    cout<<"===================\n";
}

inline void grapher::printedgemap(){
    for (int i = 0; i < gridsize; i++){
        for (int j = 0; j < gridsize; j++){
            cout<<edgemapx[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"===============\n";
    for (int i = 0; i < gridsize; i++){
        for (int j = 0; j < gridsize; j++){
            cout<<edgemapy[i][j]<<" ";
        }
        cout<<endl;
    }
}

inline void grapher::settile( vector< int > pointers[]){
    for (int i = 0; i < numnet; i++){
        tilemap[ pointers[0][i] ][ pointers[1][i] ] += 1;
        tilemap[ pointers[2][i] ][ pointers[3][i] ] += 1;
        // cout<<i<<" "<<pointers[0][i]<<" "<<pointers[1][i]<<" "<<pointers[2][i]<<" "<<pointers[3][i]<<endl;
    }    
}

inline void grapher::traverse(int startx,int starty,int endx, int endy){
    if(startx<endx){
        if (starty<endy) mode = 0; // at right top
        else mode = 1; // at right down or straight up
    }
    else{
        if (starty<endy) mode = 2; // at left top
        else mode = 3; // at left down  or straight down
    }
    switch (mode)
    {
    case 0:

        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
}
