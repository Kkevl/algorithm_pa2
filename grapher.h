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
    int gridsize,capacity,edgecost = 1,
            numnet,mode;
public:
    grapher(int,int,int );
    vector<vector<int>> tilemap,tilemapcolor,ansvector,edgemapx,edgemapy;
    vector<int> ansroutenum;
    int maxflowx = 0,maxflowy = 0, thisx,thisy;
    // create a map that represent every tile, each should refresh every time dijkstra
    void printtilemap();
    void printedgemap();// create " " to represent each edge between each tile
    void settile(vector<int> pointers[]);
    void traverse(int, int, int, int, int);
    void maxflow();

};

inline grapher::grapher(int grid,int cap,int net){
    vector<vector<int>> buffer(grid,vector<int>(grid,0));
    vector<vector<int>> netbuffer(net,vector<int>()); //use to save route of each time route
    capacity = cap;
    gridsize = grid;
    numnet = net;
    ansvector = netbuffer;
    tilemap = buffer;
    edgemapx = buffer;
    edgemapy = buffer;
    for (int i = 0; i < grid; i++){
        for (int j = 0; j < grid-1; j++){
            edgemapx[i][j] = 0;//edgecost;
        }     
    }
    for (int i = 0; i < grid-1; i++){
        for (int j = 0; j < grid; j++){
            edgemapy[i][j] = 0;//edgecost;
        }        
    }    
}

inline void grapher::printtilemap(){
    for (int i = gridsize-1; i >= 0; i--){
        for (int j = 0; j < gridsize; j++){
            cout<<tilemap[i][j]<<" ";
        }
        cout<<endl;
    }    
    
}

inline void grapher::printedgemap(){
    cout<<"======edgex=======\n";
    for (int i = gridsize-1; i >= 0; i--){
        for (int j = 0; j < gridsize-1; j++){
            cout<<edgemapx[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"======edgey=======\n";
    for (int i = gridsize-2; i >= 0; i--){
        for (int j = 0; j < gridsize; j++){
            cout<<edgemapy[i][j]<<" ";
        }
        cout<<endl;
    }
}

inline void grapher::settile( vector< int > pointers[]){
    for (int i = 0; i < numnet; i++){
        tilemap[ pointers[1][i] ][ pointers[0][i] ] += 1;
        tilemap[ pointers[3][i] ][ pointers[2][i] ] += 1;
    }    
}

// since the position of list is invertrd, the poiot is reversed
inline void grapher::traverse( int netid ,int startx,int starty,int endx, int endy){
    if(startx<=endx){
        if (starty<endy) mode = 0; // at right top or straight up
        else mode = 1; // at right down  or straight down
    }
    else{
        if (starty<=endy) mode = 2; // at left or left top 
        else mode = 3; // at left down
    }
    //initialize the point
    int r = 0;
    thisx = startx;
    thisy = starty;
    switch (mode)
    {
    case 0: // traverse right to up (ex>=sx) (ey>sy)
        for (int i = 0; i < (endx - startx); i++){
            ansvector[netid].push_back(thisx);
            ansvector[netid].push_back(thisy);
            edgemapx[thisy][thisx] += edgecost;
            thisx += 1;
            r+=1;
        }
        for (int i = 0; i < (endy - starty); i++){
            ansvector[netid].push_back(thisx);
            ansvector[netid].push_back(thisy);
            edgemapy[thisy][thisx] += edgecost;
            thisy += 1;
            r+=1;
        }
        break;
    case 1: // traverse right to down (ex>=sx) (ey<sy)
        for (int i = 0; i < (endx - startx); i++){
            ansvector[netid].push_back(thisx);
            ansvector[netid].push_back(thisy);
            edgemapx[thisy][thisx] += edgecost;
            thisx += 1;
            r+=1;
        }
        for (int i = 0; i < (starty - endy); i++){
            ansvector[netid].push_back(thisx);
            ansvector[netid].push_back(thisy);
            edgemapy[thisy-1][thisx] += edgecost;
            thisy -= 1;
            r+=1;
        }
        break;
    case 2:  // at left top or left
        for (int i = 0; i < ( startx - endx); i++){
            ansvector[netid].push_back(thisx);
            ansvector[netid].push_back(thisy);
            edgemapx[thisy][thisx-1] += edgecost;
            thisx -= 1;
            r+=1;
        }
        for (int i = 0; i < ( endy - starty ); i++){
            ansvector[netid].push_back(thisx);
            ansvector[netid].push_back(thisy);
            edgemapy[thisy][thisx] += edgecost;
            thisy += 1;
            r+=1;
        }
        break;
    case 3: // at left down
        for (int i = 0; i < ( startx - endx); i++){
            ansvector[netid].push_back(thisx);
            ansvector[netid].push_back(thisy);
            edgemapx[thisy][thisx-1] += edgecost;
            thisx -= 1;
            r+=1;
        }
        for (int i = 0; i < ( starty - endy); i++){
            ansvector[netid].push_back(thisx);
            ansvector[netid].push_back(thisy);
            edgemapy[thisy-1][thisx] += edgecost;
            thisy -= 1;
            r+=1;
        }
        break;
    default:
        break;
    }
    ansvector[netid].push_back(thisx);
    ansvector[netid].push_back(thisy);
    ansroutenum.push_back(r);
}

inline void grapher::maxflow(){
    for(auto& row:edgemapx){
        auto it = max_element(row.begin(), row.end());
        if( *it > maxflowx ) maxflowx = *it;
    }
    for(auto& row:edgemapy){
        auto it = max_element(row.begin(), row.end());
        if( *it > maxflowy ) maxflowy = *it;
    }
}
