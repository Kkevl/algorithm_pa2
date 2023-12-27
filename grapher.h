#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<vector>
#include<algorithm>
#include"router.h"
using namespace std;
class grapher
{
private:
    int gridsize,
        capacity,
        edgecost = 1,
        numnet,
        mode;
public:
    grapher(int,int,int );
    vector<vector<int>> tilemap ,tilemapcolor ,lastposition ,
                        edgemapx ,edgemapy ,
                        ansvector;
    vector<int> ansroutenum;
    int maxflowx = 0,maxflowy = 0, thisx,thisy;
    // create a map that represent every tile, each should refresh every time dijkstra
    void printtilemap();
    void printedgemap();// create " " to represent each edge between each tile
    void settile(int stx ,int sty);
    void traversel(int, int, int, int, int);
    void maxflow();
    void dijkstra(int ,int ,int ,int);
    void extractmin(int *,int* , vector<int>&);
    void relax(int, int , int , int);
    //refresh weight will be done by founding path
    void refindpath(int, int ,int ,int , int );
};

inline grapher::grapher(int grid,int cap,int net){
    vector<vector<int>> buffer(grid,vector<int>(grid,0));
    vector<vector<int>> netbuffer(net,vector<int>()); //use to save route of each time route
    capacity = cap;
    gridsize = grid;
    numnet = net;
    ansvector = netbuffer;
    tilemap = buffer;
    tilemapcolor = buffer;
    lastposition = buffer;
    edgemapx = buffer;
    edgemapy = buffer;
    for (int i = 0; i < grid; i++){
        for (int j = 0; j < grid-1; j++){
            edgemapx[i][j] = edgecost;
        }     
    }
    for (int i = 0; i < grid-1; i++){
        for (int j = 0; j < grid; j++){
            edgemapy[i][j] = edgecost;
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

//will use to reset all key for dijkstra
inline void grapher::settile(int stx, int sty){
    for (int i = 0; i < gridsize; i++){
        for (int j = 0; j < gridsize; j++){
            tilemap[i][j] = INT16_MAX;
        }        
    }
    tilemap[sty][stx] = 0;
    //color reset
    for (int i = 0; i < gridsize; i++){
        for (int j = 0; j < gridsize; j++){
            tilemapcolor[i][j] = 0;
        }        
    }
}

// since the position of list is invertrd, the poiot is reversed
inline void grapher::traversel( int netid ,int startx,int starty,int endx, int endy){
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

//count the overflow
inline void grapher::maxflow(){
    int over = 0;
    for(auto& row:edgemapx){
        auto it = max_element(row.begin(), row.end());
        if( *it > maxflowx ) maxflowx = *it;
        if( *it > capacity+1 ) over++;
    }
    for(auto& row:edgemapy){
        auto it = max_element(row.begin(), row.end());
        if( *it > maxflowy ) maxflowy = *it;
        if( *it > capacity+1 ) over++;
    }
    cout<<"over = "<<over<<endl;
}

inline void grapher::dijkstra(int startx,int starty ,int endx ,int endy){
    //initialize the tile weight&color&(lastposition)
    settile(startx,starty); 
    vector<int> Q;
    // set Q's bound
    for (int i = 0; i < gridsize; i++){
        for (int j = 0; j < gridsize; j++){
            Q.push_back(gridsize*i+j);
        }        
    }    
    //use gridsize*y + x to encode the position
    thisx = startx;
    thisy = starty;
    while (!Q.empty()){
        //relax all edge of this point
        extractmin( &thisx , &thisy , Q );
        
        if ((thisx == endx)&(thisy == endy)) break;

        tilemapcolor[thisy][thisx] = 1; // means black
        //relax neighbors right, up ,left ,down
        if(thisx<gridsize-1) relax(thisx+1,thisy, edgemapx[thisy][thisx] , 1);// check not out of right bound
        if(thisy<gridsize-1) relax(thisx,thisy+1, edgemapy[thisy][thisx] , 2);// check not out of up bound
        if(thisx>0) relax(thisx-1,thisy,  edgemapx[thisy][thisx-1] ,  3 );// check not out of left bound
        if(thisy>0) relax(thisx,thisy-1, edgemapy[thisy-1][thisx] , 4 );// check not out of down bound
    }

}

inline void grapher::extractmin(int *thex, int *they , vector<int> &sets){
    int temp = 0;
    for (int i = 0; i < sets.size(); i++){
        if ( tilemap[ sets[temp]/gridsize ][ sets[temp]%gridsize ] > tilemap [ sets[i] / gridsize ] [ sets[i] % gridsize ] ){
            // if the tile number of [seti] is lesser than change target to it
            temp = i;
        }        
    }
    *they = sets[temp]/gridsize;
    *thex = sets[temp]%gridsize;
    sets.erase( sets.begin() + temp );
    return;
}

inline void grapher::relax(int posx, int posy , int weight, int  direction){  // recieve the position of need to change
    if (tilemapcolor[posy][posx] != 0){
        return;
    }    
    else if ( tilemap[ posy ] [ posx ]  >( tilemap[ thisy ][ thisx ] + weight) ){
        tilemap[ posy ] [ posx ] = ( tilemap[ thisy ][ thisx ] + weight);
        lastposition[ posy ] [ posx ] = direction;
    }    
}

inline void grapher::refindpath(int netid,int startx,int starty, int endx, int endy){
    //todo: refind the best path and pass to ansvector also refresh the edge
    thisx = endx;
    thisy = endy;
    int direction,r = 0;

    while ( (thisx != startx) || (thisy != starty) ){
        ansvector[netid].push_back(thisx);
        ansvector[netid].push_back(thisy);
        direction = lastposition[thisy][thisx];
        r+=1; //steps counter
        switch (direction)
        {
        case 1: //move left
            edgemapx[thisy][thisx-1] += edgecost;
            thisx -= 1;
            break;
        case 2: //move down
            edgemapy[thisy-1][thisx] += edgecost;
            thisy -= 1;
            break;
        case 3: //move right
            edgemapx[thisy][thisx] += edgecost;
            thisx += 1;
            break;
        case 4: // move up
            edgemapy[thisy][thisx] += edgecost;
            thisy += 1;
            break;
        default:
            break;
        }
    }
    ansvector[netid].push_back(thisx);
    ansvector[netid].push_back(thisy);
    ansroutenum.push_back(r);    
    return;
}
