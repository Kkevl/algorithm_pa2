#pragma once
#include<iostream>
#include<cstdlib>
#include <string>
#include<vector>
#include<fstream>
class router
{
private:
    /* data */
public:    
    string strbuffer;
    int gridsize,capacity,numnet;
    void testfunc(int a);
    void getroutdata(string file);

};

inline void router::testfunc(int a){
    a++;
    return;
}

inline void router::getroutdata(string file){
    strbuffer = file;
}

