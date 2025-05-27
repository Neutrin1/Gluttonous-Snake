//@File    :   resnake.cpp
//@Time    :   2025/05/27 19:37:40
//@Author  :   Neutrin 
// #include<bits/stdc++.h>
#include <cmath>
#include <iostream>
#include<conio.h>
#define H 22
#define W 22
using namespace std;
class Game_map{ 
   public:
   char edge[H][W];
   int i,j,x1,y1;  
   Game_map();
   void award();
   void prt(int grade, int score, int gamespeed);
};

Game_map::Game_map(){
    for(i=1;i<=H-2;i++){
        for(j=1;j<=W-2;j++){
            edge[i][j]=' ';
        }
    }   
    for(i=0;i<=H-1;i++){
        edge[i][0]='#'; // 左边�?
        edge[i][W-1]='#'; // 右边�?
    }
    for(j=0;j<=W-1;j++){
        edge[0][j]='#'; // 上边�?
        edge[H-1][j]='#'; // 下边�?
    }
    
}

void Game_map::award(){
    srand(time(0));
    do{
        x1 = rand() % H - 2 + 1; 
        y1 = rand() % W - 2 + 1;
    }
    while(edge[x1][y1] != ' '); 
    edge[x1][y1] = '$'; 
}

void Game_map::prt(int grade, int score, int gamespeed){
    system("cls");
    for(i=0;i<=H-1;i++){
        for(j=0;j<=W-1;j++){
            std::cout << edge[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "score:" << score << "  speed:" << gamespeed << "  grade:" << grade << std::endl;
}

class snake:public Game_map{
    public:
    int pp[2][100];
    long start;
    int head, tail, grade, score, gamespeed, length, 
        timeover, x, y;
    char direction;
    snake();
    void move();
};

snake::snake(){
    cout<<"welcom to snake!"<<endl;
    for(i=3;i>=0;i--){
        start = clock();
        while (clock() - start <= 1000) {
            // 等待1�?
            system("cls");
            if (i>0){
                cout << "countdown: " << i << endl;
            }
        }
    }
    for (i=1;i<=3;i++){
            edge[1][i] = '*'; 
        }
    edge[1][4] = '@';
    for(i=0;i<4;i++){
        pp[0][i] = 1; 
        pp[1][i] = i + 1; 
    }
}


void snake::move(){
    score = 0;
    head = 3, tail = 0;
    grade = 1, length = 4, gamespeed = 500, direction = 77;
    award(); 
    while (1)
    {
        timeover = 1;
        start = clock();
        while ((timeover=(clock()-start<=gamespeed))&&!kbhit());
        if(timeover){
            getch();
            direction = getch(); 
        }
        switch (direction) {
            case 72: 
                x = pp[0][head] - 1;
                y = pp[1][head];
                break;
            case 80: 
                x = pp[0][head] + 1;
                y = pp[1][head];
                break;
            case 75: 
                x = pp[0][head];
                y = pp[1][head] - 1;
                break;
            case 77: 
                x = pp[0][head];
                y = pp[1][head] + 1;
                break;
            default:
                continue; 
        }
        if (x==0 || x==H-1 || y==0 || y==W-1 || edge[x][y]=='*') {
            std::cout << "Game Over!" << std::endl;
            break; 
        }
        if (edge[x][y] != ' ' &&!(x==x1&&y==y1)){
            std::cout << "Game Over!" << std::endl;
            break; 
        }
        if (x==x1 && y==y1) {
            length ++;
            score=score+100;
            if(length>=8)
            {
                length -= 8;
                grade ++;
                if(gamespeed>=200)
                    gamespeed = 550 - grade * 50;
            }
            edge[x][y]= '@';
            edge[pp[0][head]][pp[1][head]] = '*';
            head = (head+1)%100;
            pp[0][head] = x;
            pp[1][head] = y;
            award();
            prt(grade,score,gamespeed);
        }
        else {
            edge[pp[0][tail]][pp[1][tail]] = ' '; 
            tail = (tail + 1) % 100; 
            edge[pp[0][head]][pp[1][head]] = '*'; 
            head = (head + 1) % 100; 
            pp[0][head] = x; 
            pp[1][head] = y; 
            edge[pp[0][head]][pp[1][head]] = '@'; 
            prt(grade, score, gamespeed); 
        }
    }  
}


int main()
{
    snake s;
    s.move();
    return 0;
}