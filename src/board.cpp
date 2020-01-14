#include "./../include/board.h"
#include <iostream>
#include <vector>
#include <cstdlib>
//#include <./../lib/io.h>

int Board::get_dimx() { return dim_x; }
int Board::get_dimy() { return dim_y; }



void Board::intialize(){

    for (int i=0; i<dim_y; i++){
        map[i].clear();
    }

}


void Board::draw(int mode){

    switch (mode)
    {
    case 0:
        for (int i=0; i<500; i++) { std::cout<<std::endl; }
        break;
    
    case 1:
        system("CLS");
        break;
    }

    

    for (int i=0; i<dim_y; i++){
        
        for (int k=0; k<41; k++){
                std::cout << ' ';
            } 
        for (int j=0; j<dim_x; j++){
            
            std::cout << map[i][j];

        } std::cout << std::endl;

    }
}

void Board::set_value(char character, int pos_x, int pos_y) { map[pos_y][pos_x] = character; }


void Board::set_default(){

    for (int i=0; i<dim_y; i++){
        for (int j=0; j<dim_x; j++){

            if (i==0 || i==dim_y-1) { 
                
                map[i].push_back('#');
            } else if (j == 0 || j == dim_x-1) { 
                map[i].push_back('#'); 
            } else { 
                map[i].push_back(' '); 
                }

        } std::cout << std::endl;
    }

}



char Board::get_character(int pos_x, int pos_y) { return  map[pos_y][pos_x]; }

void Board::clear(int pos_x, int pos_y) { map[pos_x][pos_y] = ' '; }





Board::Board(int x, int y):
    map(y), dim_x(x), dim_y(y) {
    intialize();
    set_default();
}

Board::~Board() {
}