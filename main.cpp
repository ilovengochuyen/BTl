#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <SDL.h>
#include "sdl_utils.h"
#include "cut1.h"
#include <cstdlib>
#include <ctime>

#define fi first
#define se second
#define pii pair <int,int>


using namespace std;

vector <vector<int>> A;
vector <int> B;

void initialization()
{
    for(int i=1;i<=table_width;i++)
        for(int j=1;j<=table_height;j++)
    {
        b[i][j].make((i-1)*10+1,(j-1)*10+1,i*10-1,j*10-1);
    }
    for(int i=1;i<=table_width;i++)
        for(int j=1;j<=table_height;j++)
            a[i][j]=0;
    for(int i=1;i<=table_width;i++)
        for(int j=1;j<=table_height;j++)
    {
        drawColor(i,j,white);
    }
    SDL_RenderPresent(renderer);
}

void draw_table()
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

void draw_object()
{
    for(int i=1;i<=table_width;i++)
        for(int j=1;j<=table_height;j++)
            if(a[i][j]==1)
    {
            drawColor(i,j,255,0,0,0);
    }
            else if (a[i][j]==2)
    {
            if (turn %2 )
                //SDL_SetRenderDrawColor(renderer,green);
                {
                    drawColor(i,j,green);
                }
            else
                //SDL_SetRenderDrawColor(renderer,blue);
                {
                    drawColor(i,j,blue);
                }
    }
    SDL_RenderPresent(renderer);
}

void make_point()
{
    srand(time(NULL));
    int x,y;
    do
    {
	 x =1 + rand()%table_width;
	 y =10 + rand()%(table_height-10);
    }
    while( a[x][y]!=0);
    a[x][y]=2;
}

void check_point()
{
    pii tg=snake[lsnake];
    for(int i=lsnake;i>=2;i--)
        snake[i]=snake[i-1];
    snake[1]=make_pair(X,Y);
    //a[snake[1].fi][snake[1].se]=1;
    //xóa đuôi
    {
            drawColor(tg.fi,tg.se,white);
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

void creative()
{
    int n=A[online-1][0],tt=1;
    for(int i=1;i<=n;i++)
    {
        int x,y;
        x=A[online-1][tt++];
        y=A[online-1][tt++];
        a[x][y]=1;
    }
    online =lsnake;
}

void stop()
{
    cout << 1;
    while (true)
    {
        //if (e.key.keysym.sym== SDLK_SPACE) return;
        if (SDL_PollEvent(&e) ==0) continue;
        if (e.type == SDL_KEYDOWN)
        	if (e.key.keysym.sym) return ;
    }
}

void runSnake(int Map)
{
    X=10;Y=10;lsnake=1;
    stepx=1;stepy=0;
    online=1;
    snake[1]=make_pair(X,Y);
    make_point();
    while(true)
    {
        if(Map==1 && lsnake<=4 && lsnake>online) creative();
        ++turn;
        draw_object();
        X+=stepx;
        Y+=stepy;
        if(a[X][Y]==1) break;
        switch (X)
        {
            case 0: X=table_width;break;
            case table_width+1: X=1;break;
        }
        switch (Y)
        {
            case 0 : Y=table_height;break;
            case table_height+1: Y=1;break;
        }
        check_point();
        a[X][Y]=1;
        SDL_Delay(speed * 10);
        if (SDL_PollEvent(&e) ==0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN)
        {
        	switch (e.key.keysym.sym)
        	{
        		case SDLK_SPACE: stop(); break;
        		case SDLK_LEFT: left(); break;
            	case SDLK_RIGHT: right(); break;
            	case SDLK_DOWN: down(); break;
            	case SDLK_UP: up(); break;
        		default: break;
			}
        }
    }
        initialization();
}


int menu()
{
    ifstream myfile("map1.txt");

        if (myfile.fail())
        {
            std::cout << "Failed to open this file!" << std::endl;
            return -1;
        }

        for(int i=1;i<=table_width;i++)
            for(int j=1;j<=table_height;j++)
                {myfile>>a[i][j];}

        draw_object();
        drawptr(1);
        int ok=1;
        myfile.close();
        while(true)
        {
        SDL_Delay(speed * 10);
        if (SDL_PollEvent(&e) ==0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN)
        {
        	switch (e.key.keysym.sym)
        	{

        		case SDLK_SPACE:return ok; break;
            	case SDLK_DOWN: if(!ok){drawptr(1);ok=1;}else {drawptr(2);ok=0;} break;
            	case SDLK_UP: if(!ok){drawptr(1);ok=1;}else {drawptr(2);ok=0;} break;
        		default: break;
			}
        }
         draw_object();
        }

}

int chooseMap()
{
    draw_object();
    initialization();
    ifstream myfile("mapmap.txt");

        if (myfile.fail())
        {
            std::cout << "Failed to open this file!" << std::endl;
            return -1;
        }

        for(int i=1;i<=table_width;i++)
            for(int j=1;j<=table_height;j++)
                {myfile>>a[i][j];}

        draw_object();
        drawptr2(1);
        int ok=1;

        while(true)
        {
        SDL_Delay(speed * 10);
        if (SDL_PollEvent(&e) ==0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN)
        {
        	switch (e.key.keysym.sym)
        	{

        		case SDLK_SPACE:return ok; break;
            	case SDLK_DOWN: if(ok==2){drawptr2(1);ok=1;}else {drawptr2(2);ok=2;} break;
            	case SDLK_UP: if(ok==2){drawptr2(1);ok=1;}else {drawptr2(2);ok=2;} break;
        		default: break;
			}
        }
         draw_object();
        }
    myfile.close();
}

void getmap(int Map)
{
    draw_object();
    initialization();
    if(Map==1)
    {
    ifstream myfile("mapl.txt");

        if (myfile.fail())
        {
            std::cout << "Failed to open this file!" << std::endl;
            return ;
        }
        int n;int tt=0;
        while(tt<3)
        {
            A.push_back(B);
            int x;
            myfile >> n;
            A[tt].push_back(n);
            for(int i=1;i<=n*2;i++)
                {
                    myfile >> x;
                    A[tt].push_back(x);
                }
            ++tt;
        }
        myfile.close();

        runSnake(Map);
    }
    else if(Map==2)
    {
    ifstream myfile("map2.txt");

        if (myfile.fail())
        {
            std::cout << "Failed to open this file!" << std::endl;
            return ;
        }

        for(int i=1;i<=table_width;i++)
            for(int j=1;j<=table_height;j++)
                {myfile>>a[i][j];}
        myfile.close();
        runSnake(Map);
    }
}

int main(int arg, char *argv[])
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    draw_table();
    initialization();

    while(true)
    {
        int ok=menu();
        if(ok)
            {
                getmap(chooseMap());
            }
        else break;
    }

    quitSDL(window,renderer);
    return 0;
}
