#include "common.h"
#include "stdarg.h"

extern SDL_Surface *screen;

extern uint8_t font8x8_basic[128][8];

static SDL_Surface *char_surface = NULL;

static char str[100];

#define SIN_CHAR_W 8
#define SIN_CHAR_H 8

#define MAX_TIMES 8

#define CHAR_W (MAX_TIMES * SIN_CHAR_W)
#define CHAR_H (MAX_TIMES * SIN_CHAR_H)

void init_character()
{
	char_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, CHAR_W, CHAR_H, 32 ,0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	uint32_t colorkey = SDL_MapRGB(char_surface->format, 0xff, 0,0xff);
	SDL_SetColorKey(char_surface, SDL_SRCCOLORKEY, colorkey);
}

void draw_character(char ch, int x, int y, uint32_t color, uint8_t times)
{
	uint32_t i, j;
	uint32_t *pixels = (uint32_t *)char_surface->pixels;
	assert(times != 0 && times <= MAX_TIMES);
	for(i = 0; i < CHAR_W; i++)
		for(j = 0; j < CHAR_H; j++)
		{
			if((font8x8_basic[(uint8_t)ch][j / times] >> (i / times)) & 0x1)
			{
				pixels[i + j * CHAR_W] = 0xff000000 | color;
			}
			else
				pixels[i + j * CHAR_W] = 0x00ff00ff;
		}

	SDL_Rect srcrect, dstrect;
	srcrect.x = srcrect.y = 0;
	srcrect.w = times * SIN_CHAR_W;
	srcrect.h = times * SIN_CHAR_H;
	dstrect.x = x - srcrect.w / 2;
	dstrect.y = y - srcrect.h / 2;
	SDL_BlitSurface(char_surface, &srcrect, screen, &dstrect);
}

int draw_str(int x, int y, uint32_t color, uint8_t times, const char * format, ...)
{
	int num;
	va_list parg_list;
	va_start(parg_list, format);
	num = vsprintf(str, format, parg_list);
	va_end(parg_list);

	//draw on screen
	int i, len =  strlen(str);
	for(i = 0; i < len; i++)
	{
		draw_character(str[i], x + i * times * SIN_CHAR_H, y, color, times);
	}

	return num;
}
