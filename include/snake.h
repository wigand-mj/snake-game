#ifndef _SNAKE_H_
#define _SNAKE_H_
#include <cstddef>
class node {
public:
	int posx;
	int posy;
	char body;
	node* next;
	node(int x, int y, char Body) : posx(x), posy(y), body(Body), next(NULL){};
};

class snake {
private:
	node* first;
	node* last;
	int length;
    char heading; //wasd für die Ausrichtung
public:
	snake(int startlength,int startx,int starty,char startheading);
	~snake();
	int firstposx();
	int firstposy();
	int lastposx();
	int lastposy();
	int getlength();
	char getheading();
	int getposx(int place); 
	int getposy(int place);
	void grow(); //Lässt die Schlange um 1 Element wachsen (ggf. unnötig)
	void move(); //Bewege die Schlange in Richtung heading
    void setheading(char Direction);
	
};
#endif