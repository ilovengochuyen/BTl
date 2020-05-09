#ifndef cut__H
#define cut__H

#define pii pair <int,int>
#define green 0,0,250,0
#define blue 00,200,00,00
#define white 255,255,255,255
#define red 255,0,0,0

#include <iostream>
#include <SDL.h>
const int size = 9;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int table_width=100;
const int table_height=60;
const int tx[]={-3,-2,-1,0,-1,-1};
const int ty[]={0,0,0,0,-1,1};
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Event e;
//khai báo biến cục bộ
static int a[table_width][table_height];
int turn =0;
int speed=10;

struct table
{
    int x,y,z,t;
    make(int a,int b,int c,int d)
    {
        x=a;y=b;z=c;t=d;
    }
};
table b[table_width][table_height];
//khai báo snake
int lsnake=1;
pii snake[1000];


void drawColor(int i,int j,int c1,int c2,int c3,int c4)
{
            //if(i<=10&& j<=10 ) return;
            SDL_SetRenderDrawColor(renderer,c1,c2,c3,c4);
            SDL_Rect fillrect;
            fillrect.x=b[i][j].x;
            fillrect.y=b[i][j].y;
            fillrect.w=size;
            fillrect.h=size;
            SDL_RenderFillRect(renderer, &fillrect);
        //SDL_RenderPresent(renderer);
}

void drawptr(int p)
{
    const int x1=30,y1=25,x2=40,y2=40;
    if(p==1)
    {
        for(int i=0;i<=5;i++)
            drawColor(x1+tx[i],y1+ty[i],blue);
        for(int i=0;i<=5;i++)
            drawColor(x2+tx[i],y2+ty[i],white);
    }
    else
    {
        for(int i=0;i<=5;i++)
            drawColor(x1+tx[i],y1+ty[i],white);
        for(int i=0;i<=5;i++)
            drawColor(x2+tx[i],y2+ty[i],blue);
    }
}

void drawptr2(int p)
{
    const int x1=50,y1=10,x2=50,y2=22;
    if(p==1)
    {
        for(int i=0;i<=5;i++)
            drawColor(x1+tx[i],y1+ty[i],blue);
        for(int i=0;i<=5;i++)
            drawColor(x2+tx[i],y2+ty[i],white);
    }
    else
    {
        for(int i=0;i<=5;i++)
            drawColor(x1+tx[i],y1+ty[i],white);
        for(int i=0;i<=5;i++)
            drawColor(x2+tx[i],y2+ty[i],blue);
    }
}

int X=1,Y=1,stepx=0,stepy=0;
void left()
{
        stepx=-1;
        stepy=0;
}
void right()
{
        stepx=+1;
        stepy=0;
}
void up()
{
        stepx=0;
        stepy=-1;
}
void down()
{
        stepx=0;
        stepy=+1;
}

#endif
