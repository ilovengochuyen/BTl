#ifndef sdl_utils__H
#define sdl_utils__H


#include <iostream>
#include <SDL.h>

using namespace std;

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,const int SCREEN_WIDTH,const int SCREEN_HEIGHT,const string &WINDOW_TITLE);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

struct Box{
    int x;
    int y;
    const int size=10;
    int stepX=5,stepY=5;
    void render(SDL_Renderer* renderer)
    {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect fillrect;
    fillrect.x=x;
    fillrect.y=y;
    fillrect.w=size;
    fillrect.h=size;
    SDL_RenderFillRect(renderer, &fillrect);

    }
    bool inside(int minx,int miny,int maxx,int maxy)
    {
        return (minx <= x && miny<=y && x<=maxx-size && y<maxy-size);
    }
    void move()
    {
        x+=stepX;
        y+=stepY;
    }
    void left()
    {
        stepX=-5;
        stepY=0;
    }
    void right()
    {
        stepX=5;
        stepY=0;
    }
    void up()
    {
        stepY=-5;
        stepX=0;
    }
    void down()
    {
        stepY=+5;
        stepX=0;
    }
};

#endif
