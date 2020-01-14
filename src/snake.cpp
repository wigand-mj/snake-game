#include "./../include/snake.h"
#include <assert.h>



snake::snake(int startlength, int startx, int starty, char startheading) {
	if (startlength < 2) {
		assert(false);
	}
	length = startlength;
	heading = startheading;
	first = new node(startx, starty, '0'); // memory leak?
	last = new node(startx,starty,'+'); // memory leak?

	switch (startheading){
		case 's': 
		last->posx = startx;
		last->posy = starty-1;
		break;
		case 'a':
		last->posx = startx-1;
		last->posy = starty;
		break;		
		case 'w':
		last->posx = startx;
		last->posy = starty+1;
		break;
		case 'd':
		last->posx = startx+1;
		last->posy = starty;
		break;
	}

	if (startlength > 2) {
		node* begin = first;
		int nextx;
		int nexty;
		switch (startheading) {
		case 's':
			nextx = startx;
			nexty = starty - 1;		//fixed Bug
			break;
		case 'a':
			nextx = startx-1;
			nexty = starty;
			break;
		case 'w':
			nextx = startx;
			nexty = starty +1;
			break;
		case 'd':
			nextx = startx+1;
			nexty = starty;
			break;
		}

		for (int i = 0; i < (startlength - 2); i++) {
			switch (heading){
			case 's': 
				begin->next = new node(nextx, nexty , 'O');
				begin = begin->next;
				nexty--;
				break;
			case 'a': 
				begin->next = new node(nextx, nexty, 'O');
				begin = begin->next;
				nextx--;
				break;
			case 'w': 
				begin->next = new node(nextx, nexty, 'O');
				begin = begin->next;
				nexty++;
				break;
			
			case 'd': 
				begin->next = new node(nextx , nexty, 'O');
				begin = begin->next;
				nextx++;
				break;
			
			}
		}
		begin->next = last;
		switch (startheading){
	case 's':
		last->posx = begin->posx;
		last->posy = begin->posy - 1;
		break;
	case 'a':
		last->posx = begin->posx - 1;
		last->posy = begin->posy;
		break;
	case 'w':
		last->posx = begin->posx;
		last->posy = begin->posy + 1;
		break;
	case 'd':
		last->posx = begin->posx + 1;
		last->posy = begin->posy;
		break;
	}
	}
}

snake::~snake() {
	node* ptr;
	for (int i = 0; i < length - 1; i++) {
		node* ptr = first;
		first = first->next;
		delete ptr;
	}
}

int snake:: firstposx() {
	return first->posx;
}

int snake::firstposy() {
	return first->posy;
}

int snake::lastposx() {
	return last->posx;
}

int snake::lastposy() {
	return last->posy;
}

char snake::getheading() {
	return heading;
}
int snake::getlength() {
	return length;
}

void snake::setheading(char Direction) {
	heading = Direction;
	return;
}

void snake::grow() {
	node* newn = new node(last->posx, last->posy, 'O'); // memory leak?
		switch (heading){

	case 'w':
		newn->posx = newn->posx;
		newn->posy = newn->posy - 1;
		break;

	case 'a':
		newn->posx = newn->posx - 1;
		newn->posy = newn->posy;
		break;

	case 's':
		newn->posx = newn->posx;
		newn->posy = newn->posy + 1;
		break;

	case 'd':
		newn->posx = newn->posx + 1;
		newn->posy = newn->posy;
		break;

		}
		last->next = newn;
		last = newn;
		length++;
}

void snake::move() {
	int posnewx = first->posx;
	int posnewy = first->posy;
	int poscurx;
	int poscury;
	node* runner=first->next;

	switch (heading) {

	case 's':
		first->posy++;
		break;

	case 'a':
		first->posx--;
		break;
	case 'w':
		first->posy--;
		break;
	case 'd':
		first->posx++;
		break;

	}
	for (int i = 0; i < (length - 1); i++) {
		poscurx = runner->posx;
		poscury = runner->posy;
		runner->posx = posnewx;
		runner->posy = posnewy;
		posnewx = poscurx;
		posnewy = poscury;
		runner = runner->next;
	}
}

int snake::getposx(int place) {
	node* runner=first;
	for (int i = 0; i < (place); i++) {
		runner = runner->next;
	}
	return runner->posx;
}

int snake::getposy(int place) {
	node* runner = first;
	for (int i = 0; i < (place); i++) {
		runner = runner->next;
	}
	return runner->posy;
}







