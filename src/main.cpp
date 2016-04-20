#include "common.h"

void init_res();
void init_enemy();
void init_bullet();
void init_player();
void init_plane();
void init_bomb();
void init_character();
void init_xbullets();
void game_start();

SDL_Surface *screen, *background;

int main(int argc, char **argv)
{
    srand(time(NULL));
    
    SDL_Init(SDL_INIT_EVERYTHING);
    
    screen = SDL_SetVideoMode(BK_W, BK_H, 32, SDL_SWSURFACE);
        
    init_res();

	init_player();

	init_plane();

	init_bullet();

	init_bomb();
	
	init_character();

	init_xbullets();

	game_start();

	/* Should not reach here! */
	assert(0);
}
