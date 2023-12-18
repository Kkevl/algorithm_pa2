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
    int gridsize,capacity;
public:
    grapher(int,int);
    // create a map that represent every tile, each should refresh every time dijkstra
    
    // create " " to represent each edge between each tile

};

inline grapher::grapher(int grid,int cap){
    capacity = cap;
    gridsize = grid;
}


