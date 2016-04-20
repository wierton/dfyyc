#include "common.h"

void move_player();

INPUTSTATE g_InputState = {kdirUnknown, kdirUnknown, SDLK_Unknown};

void msgloop()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT)
            exit(0);
        if(event.type == SDL_KEYDOWN)
        {
			switch(event.key.keysym.sym)
			{
				//dir key
				case SDLK_UP	:g_InputState.dir = kdirUp;	break;
				case SDLK_DOWN	:g_InputState.dir = kdirDown;	break;
				case SDLK_LEFT	:g_InputState.dir = kdirLeft;	break;
				case SDLK_RIGHT	:g_InputState.dir = kdirRight;	break;
				default:
					g_InputState.dwKey = event.key.keysym.sym;
					break;
			}
        }
		else if(event.type == SDL_KEYUP)
        {
			switch(event.key.keysym.sym)
			{
				case SDLK_UP	:g_InputState.dir = kdirUnknown;
								 break;
				case SDLK_DOWN	:g_InputState.dir = kdirUnknown;
								 break;
				case SDLK_LEFT	:g_InputState.dir = kdirUnknown;
								 break;
				case SDLK_RIGHT	:g_InputState.dir = kdirUnknown;
								 break;
				default:
					g_InputState.dwKey = SDLK_Unknown;
					break;
			}
        }
    }
	move_player();
}
