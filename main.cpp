#include <iostream>
#include <bits/stdc++.h>
#include <SDL.h>
#include "sdl_utils.h"
#include <cstdlib>
#include <ctime>

#define fi first
#define se second
#define pii pair <int,int>
#define green 0,0,250,0
#define blue 00,200,00,00

using namespace std;
//tạo màn hình
const int size = 9;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int table_width=100;
const int table_height=60;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";
//khai báo biến cục bộ
static int a[table_width+100][table_height+100];
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
table b[table_width+100][table_height+100];

void initialization(SDL_Window* window, SDL_Renderer* renderer)
{
    for(int i=1;i<=table_width;i++)
        for(int j=1;j<=table_height;j++)
    {
        b[i][j].make((i-1)*10+1,(j-1)*10+1,i*10-1,j*10-1);
    }
    for(int i=1;i<=table_width;i++)
        for(int j=1;j<=table_height;j++)
            a[i][j]=0;
    for(int i=1;i<table_width;i++)
    {
        a[i][1]=1;
        a[i][table_height]=1;
    }
    for(int j=1;j<=table_height;j++)
    {
        a[1][j]=1;
        a[table_width][j]=1;
    }
    for(int i=1;i<=table_width;i++)
        for(int j=1;j<=table_height;j++)
    {
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_Rect fillrect;
            fillrect.x=b[i][j].x;
            fillrect.y=b[i][j].y;
            fillrect.w=size;
            fillrect.h=size;
            SDL_RenderFillRect(renderer, &fillrect);
    }
    SDL_RenderPresent(renderer);
}

void draw_table(SDL_Window* window, SDL_Renderer* renderer)
{


    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    for(int i=1;i<=table_height;i++)
    {
        SDL_RenderDrawLine(renderer,0,(i-1)*10,SCREEN_WIDTH,(i-1)*10);
    }
    for(int j=1;j<=table_width;j++)
    {
        SDL_RenderDrawLine(renderer,(j-1)*10,0,(j-1)*10,SCREEN_HEIGHT);
    }

    SDL_RenderPresent(renderer);

}

void draw_object(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,255,0,0,0);
    for(int i=1;i<=table_width;i++)
        for(int j=1;j<=table_height;j++)
            if(a[i][j]==1)
    {
            SDL_SetRenderDrawColor(renderer,255,0,0,0);
            SDL_Rect fillrect;
            fillrect.x=b[i][j].x;
            fillrect.y=b[i][j].y;
            fillrect.w=size;
            fillrect.h=size;
            SDL_RenderFillRect(renderer, &fillrect);
    }
            else if (a[i][j]==2)
    {
            if (turn %2 )
                SDL_SetRenderDrawColor(renderer,green);
            else
                SDL_SetRenderDrawColor(renderer,blue);
            SDL_Rect fillrect;
            fillrect.x=b[i][j].x;
            fillrect.y=b[i][j].y;
            fillrect.w=size;
            fillrect.h=size;
            SDL_RenderFillRect(renderer, &fillrect);
    }
    SDL_RenderPresent(renderer);
}

int X=10,Y=10,stepx=0,stepy=0;
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

void make_point()
{
    srand(time(NULL));
    int x,y;
    do
    {
	 x =1 + rand()%table_width;
	 y =1 + rand()%table_height;
    }
    while( a[x][y]!=0);
    a[x][y]=2;
}

//khai báo snake
int lsnake=1;
pii snake[100];

void check_point(SDL_Renderer* renderer)
{
    pii tg=snake[lsnake];
    for(int i=lsnake;i>=2;i--)
        snake[i]=snake[i-1];
    snake[1]=make_pair(X,Y);
    //a[snake[1].fi][snake[1].se]=1;
    //xóa đuôi
    {
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_Rect fillrect;
            fillrect.x=b[tg.fi][tg.se].x;
            fillrect.y=b[tg.fi][tg.se].y;
            fillrect.w=size;
            fillrect.h=size;
            SDL_RenderFillRect(renderer, &fillrect);
            a[tg.fi][tg.se]=0;
    }

    if(a[X][Y]==2)
    {
        ++lsnake;
        snake[lsnake]=make_pair(snake[lsnake-1].fi-stepx,snake[lsnake-1].se-stepy);
        make_point();
    }
    a[snake[lsnake].fi][snake[lsnake].se]=1;

}

int main(int arg, char *argv[])
{
    //
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Event e;
    draw_table(window, renderer);
    initialization(window, renderer);
    draw_object(window, renderer);
    stepx=0;
    stepy=1;
    snake[1]=make_pair(X,Y);
    make_point();

    while(true)
    {
        ++turn;
        draw_object(window, renderer);
        X+=stepx;
        Y+=stepy;
        if(X<1 || Y<1 || X>table_width || Y>table_height || a[X][Y]==1) break;
        check_point(renderer);
        a[X][Y]=1;
        SDL_Delay(speed * 10);
        if (SDL_PollEvent(&e) ==0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN)
        {
        	switch (e.key.keysym.sym)
        	{
        		case SDLK_ESCAPE: break;
        		case SDLK_LEFT: left(); break;
            	case SDLK_RIGHT: right(); break;
            	case SDLK_DOWN: down(); break;
            	case SDLK_UP: up(); break;
        		default: break;
			}

        }

    }
    quitSDL(window,renderer);
    return 0;
}
