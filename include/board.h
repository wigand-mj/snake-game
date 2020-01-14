#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {

    private:
    int dim_x;
    int dim_y;
    std::vector <std::vector<char>> map;

    public:
    
    int get_dimx();
    int get_dimy();
    void intialize();
    void draw(int mode);
    void set_value(char character, int pos_x, int pos_y);
    void set_default();
    char get_character(int pos_x, int pos_y);
    void clear(int pos_x, int pos_y);


    
    Board(int x, int y);
    ~Board();


};

#endif
