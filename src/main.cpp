#define _WIN32_WINNT 0x0501
#define concat(FIRST,SECOND) FIRST SECOND
#define PLAY "play "
#define STOP "stop "
#define BGM "./../assets/BGM.wav"
#define NICE "./../assets/nice.wav"
#define LOOSE "./../assets/loose.wav"
#define CHOMPSCH "./../assets/chompsch.wav"

#include <iostream>
#include "./../include/board.h"
#include "./../include/snake.h"
#include <vector>
#include <string>
//#include <./../lib/Io.h>
#include <windows.h>
#include <conio.h>
#include <cmath>

#include "./../lib/mingw.thread.h"



int dimx = 40+2;
int dimy = 20+2;
std::string STATE = "WELCOME";
Board board1(dimx,dimy);
int s_length = 4;
int points = 0;
int item_amount = 12;
char startHeading = 's';
int startposx = round((dimx/2));
int startposy = round((dimy/2));
snake* snake1 = new snake(s_length,startposx, startposy, startHeading);
bool sound=0;
char item_icon = '$';


void update(int mode) {
    switch(mode) {
        case(0):
            board1.draw(0);
            break;
        case(1):
            board1.draw(1);
            std::cout << "POINTS: " << points << std::endl;
            break;
    }
    

}

char read_key(int timeout_ms) {
	Sleep(timeout_ms);
	if (!_kbhit()) 
		return 0;
	return _getch();
}

void eat(snake* s) {

    s->grow();
    points+=100;
    if (points%200 == 0){
        mciSendString(concat(PLAY,NICE), NULL, 0, 0);
    }
    if (points==item_amount*100){STATE="WIN";}
    
}

bool check_collision(snake* s) {
    bool ret = false;
    switch(s->getheading()) {
        case 'w':
            if ((board1.get_character(s->getposx(0),s->getposy(0)-1)=='#') || (board1.get_character(s->getposx(0),s->getposy(0)-1)=='O')) {
            STATE = "GAMEOVER";
            ret = true;
            } else if ((board1.get_character(s->getposx(0),s->getposy(0)-1)==item_icon)){
                mciSendString(concat(PLAY,CHOMPSCH), NULL, 0, 0);
                eat(s);
            }

            break;
        case 'a':
            if ((board1.get_character(s->getposx(0)-1,s->getposy(0))=='#') || (board1.get_character(s->getposx(0)-1,s->getposy(0))=='O')) {
            STATE = "GAMEOVER";
            ret = true;
            } else if ((board1.get_character(s->getposx(0)-1,s->getposy(0))==item_icon)){
                mciSendString(concat(PLAY,CHOMPSCH), NULL, 0, 0);
                eat(s);
            }
            break;
        case 's':
            if ((board1.get_character(s->getposx(0),s->getposy(0)+1)=='#') || (board1.get_character(s->getposx(0),s->getposy(0)+1)=='O')) {
            STATE = "GAMEOVER";
            ret = true;
            } else if ((board1.get_character(s->getposx(0),s->getposy(0)+1)==item_icon)){
                mciSendString(concat(PLAY,CHOMPSCH), NULL, 0, 0);
                eat(s);
            }
            break;
        case 'd':
            if ((board1.get_character(s->getposx(0)+1,s->getposy(0))=='#') || (board1.get_character(s->getposx(0)+1,s->getposy(0))=='O')) {
            STATE = "GAMEOVER";
            ret = true;
            } else if ((board1.get_character(s->getposx(0)+1,s->getposy(0))==item_icon)){
                mciSendString(concat(PLAY,CHOMPSCH), NULL, 0, 0);
                eat(s);
            }
            break;
    }

    return ret;

}

void snake_move(snake* s) {

    if (!check_collision(s)) {
        board1.set_value(' ', s->getposx(s->getlength()-1), s->getposy(s->getlength()-1));
        s->move();
    } else { 
        sound=0;
        mciSendString(concat(PLAY, LOOSE), NULL, 0, 0); }

}

void update_snake_pos(snake* s) {

    for (int i=0; i<s->getlength(); i++) {
       
        board1.set_value('O', s->getposx(i), s->getposy(i));

    }
   

}


void print_snake_pos(snake* s){
    for (int i=0; i<s->getlength(); i++){
        std::cout << "Glied " << i << ": x - " << s->getposx(i) << ", y - " << s->getposy(i) << std::endl;
    }
}

void go(snake* s) {

    snake_move(s);
    update_snake_pos(s);
    update(1);

}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}



std::vector<std::vector<int>> create_item_pattern(int dx, int dy, int amount) {
    std::vector<int> dimX;
    std::vector<int> dimY;
    int forbidden[dx][dy];
    int map[dx][dy];
    std::vector< std::vector< int>> output(dx);

    for (int x=0; x<dx; x++){
        for (int y=0; y<dy; y++){
            map[x][y] = 0;
        }
    }

    for (int i=0; i<dx; i++){
        output[i].clear();
    }

    for (int i=0; i<dx; i++){
        for (int j=0;j<dy;j++){
            output[i].push_back(0);
        }      
    }

    dimX.clear(); dimY.clear();

    for (int i=1; i<dx-1;i++){
        dimX.push_back(i);
    }
    for (int i=1; i<dy-1;i++){
        dimY.push_back(i);
    }

    for (int i=0; i<s_length; i++){
        switch(startHeading){
            case 'w':
                for (int i=startposy; i<s_length; i++){
                    forbidden[startposx][i] = 1;
                }
                break;
            case 'a':
                for (int i=startposx; i<s_length; i--){
                    forbidden[i][startposy] = 1;
                }
                break;
            case 's':
                for (int i=startposy; i<s_length; i--){
                    forbidden[startposx][i] = 1;
                }
                break;
            case 'd':
                for (int i=startposx; i<s_length; i++){
                    forbidden[i][startposy] = 1;
                } 
                break;
        }
    }

    for (int m=0; m<amount;){ 
        int x = rand()%((dx-2)-1 + 1) + 1;
        int y = rand()%((dy-2)-1 + 1) + 1;
        if (!(forbidden[x][y] == 1)) {
            map[x][y] = 1;
            m+=1;
            forbidden[x][y] = 1;
        }
    }

    for (int x=0; x<dx; x++){
        for (int y=0; y<dy; y++){
            if ((map[x][y] == 1)) {
                output[x][y] = 1;
            }
        }
    }

    return output;

}





void sound_engine_init(){
    while(sound) {
        mciSendString(concat(PLAY,BGM), NULL, 0, 0);
        Sleep(200);
    } mciSendString(concat(STOP,BGM), NULL, 0, 0);

}

void create_items(std::vector<std::vector<int>> map){
    for (int i=0; i<dimx; i++){
                for (int j=0; j<dimy;j++){
                    if (map[i][j] ==1) { board1.set_value('$', i, j);}
                }
            }

}

//####################################################################################################################################################################################

void printintro() {
	std::cout << std::endl;
	std::cout << "                           _____                   _  " << std::endl;
	std::cout << "                          / ____|                 | |  " << std::endl;
	std::cout << "                         | (___    _ __     __ _  | | __   ___ " << std::endl;
	std::cout << "                          \\___ \\  | '_ \\   / _` | | |/ /  / _\\ " << std::endl;
	std::cout << "                          ____) | | | | | | (_| | |   <  |  __/ " << std::endl;
	std::cout << "                         |_____/  |_| |_|  \\__,_| |_|\\_\\  \\___| " << std::endl;
	std::cout << "" << std::endl;
	std::cout << "  _                 __  __   _  _     _   _                   __  __   _  _  " << std::endl;
	std::cout << " | |               |  \\/  | | || |   (_) | |        ___      |  \\/  | | || |  " << std::endl;
	std::cout << " | |__    _   _    | \\  / | | || |_   _  | | __    ( _ )     | \\  / | | || |_  __  __" << std::endl;
	std::cout << " |  _ \\  | | | |   | |\\/| | |__   _| | | | |/ /    / _ \\/\\   | |\\/| | |__   _| \\ \\/ /" << std::endl;
	std::cout << " | |_) | | |_| |   | |  | |    | |   | | |   <    | (_>  <   | |  | |    | |    >  < " << std::endl;
	std::cout << " |____/   \\__, |   |_|  |_|    |_|   |_| |_|\\_\\    \\___/\\/   |_|  |_|    |_|   /_/\\_\\"<<std::endl;
	std::cout << "           __/ |                                                                     " << std::endl;
	std::cout << "          |___/                                                                      " << std::endl;
	std::cout << std::endl;
	return;
}


//####################################################################################################################################################################################

void printGameover() {

    system("CLS");
    for (int i=0; i<5; i++) { std::cout<<std::endl; }
	std::cout << std::endl;
	std::cout << "             ______                          ____                     __" << std::endl;
	std::cout << "            / ____/___ _____ ___  ___       / __ \\_   _____  _____   / /" << std::endl;
	std::cout << "           / / __/ __ `/ __ `__ \\/ _ \\     / / / / | / / _ \\/ ___/  / / " << std::endl;
	std::cout << "          / /_/ / /_/ / / / / / /  __/    / /_/ /| |/ /  __/ /     /_/  " << std::endl;
	std::cout << "          \\____/\\__,_/_/ /_/ /_/\\___/     \\____/ |___/\\___/_/     (_)   " << std::endl;
	std::cout << "                                                              " << std::endl;
	return;
}

//####################################################################################################################################################################################

int main() {
    sound=1;
    std::thread s1(sound_engine_init);
    bool intro_printed=false;
        

    while(true) {
        if (STATE == "WELCOME"){
                if (!intro_printed) {
                    system("CLS");
                    printintro();
                    std::cout << "Press F To Play!" << std::endl;
                    intro_printed=true;
                } 
                if (read_key(400)=='f') { STATE = "INIT"; }
        } else if (STATE == "INIT") {
     
            create_items(create_item_pattern(dimx,dimy,item_amount));
            update_snake_pos(snake1);
            update(0);

            STATE = "OP";
        } else if (STATE == "OP") {
            ShowConsoleCursor(false);
            char input = read_key(100);

            if (input == 'w' || input == 'a' || input == 's' || input == 'd') { 
                if (!(((input == 'w') && (snake1->getheading() == 's')) || 
                      ((input == 's') && (snake1->getheading() == 'w')) || 
                      ((input == 'a') && (snake1->getheading() == 'd')) || 
                      ((input == 'd') && (snake1->getheading() == 'a')))) {

                    snake1->setheading(input); 
                }
                
            }
            else if (input == 'q') { STATE = "END"; }
            else if (input == 'g') { snake1->grow(); }
            go(snake1);
            

        } else if (STATE == "GAMEOVER") {
            ShowConsoleCursor(false);
            sound = 0;
            char inp;
            printGameover();
            std::cout << "          Do you want to continue? [y/n]" <<std::endl;
            std::cin >> inp;
            if (inp=='y'){
                STATE = "INIT";
            } else if (inp=='n'){
                STATE = "END";
            } else {
                std::cout << "Something was wrong with your input. Try again!"<<std::endl;
            } 
        } else if (STATE == "WIN") {
                std::cout<<"JUHU GEWONNEN!!!"<<std::endl;
                STATE = "END";
        } else if (STATE == "END") {
            sound=0;
            s1.join();
            system("pause");
            break;
        }
    }
    


return 0;}






	/*
int choice;
std::cout<<"Hauptmenue"<<std::endl<<"1. Spiel starten"<<std::endl<<"2. Spiel beenden"<<std::endl;
while(!(chocie==1 || choice==2)){
std::cin>>choice;
}
if (choice ==2){
	system("pause");
	break;
}
choice = 8;
std::cout<<"Gewuenschte Startlaenge? :";
while (!(choice<7)){
std::cin>>choice;
}
*/
