#include "common.h"

extern SDL_Surface *background;
extern SDL_Surface *screen;

struct RES_IDC {
    int ID;
	union {
		uint32_t life, atk;
	};
    SDL_Rect rect;
} res_idc[] =
	{
		{ID_PLAYER, {400}, {0, 0, 29, 33}},
		{ID_ENEMY, {100}, {0, 33, 62, 50}},
		{ID_DOT, {10}, {29, 13, 6, 6}},
		{ID_BLOOD, {0}, {0, 0, BLOOD_W, BLOOD_H}},
		{ID_SMALLBOMB_0, {0}, {32 * 0, 83, 32, 32}},
		{ID_SMALLBOMB_1, {0}, {32 * 1, 83, 32, 32}},
		{ID_SMALLBOMB_2, {0}, {32 * 2, 83, 32, 32}},
		{ID_SMALLBOMB_3, {0}, {32 * 3, 83, 32, 32}},
		{ID_SMALLBOMB_4, {0}, {32 * 4, 83, 32, 32}},
		{ID_SMALLBOMB_5, {0}, {32 * 5, 83, 32, 32}},
		{ID_SMALLBOMB_6, {0}, {32 * 6, 83, 32, 32}},
		{ID_SMALLBOMB_7, {0}, {32 * 7, 83, 32, 32}},
		{ID_BIGBOMB_0, {0}, {180 * 0, 115 + 135 * 0, 180, 135}},
		{ID_BIGBOMB_1, {0}, {180 * 1, 115 + 135 * 0, 180, 135}},
		{ID_BIGBOMB_2, {0}, {180 * 2, 115 + 135 * 0, 180, 135}},
		{ID_BIGBOMB_3, {0}, {180 * 3, 115 + 135 * 0, 180, 135}},
		{ID_BIGBOMB_4, {0}, {180 * 0, 115 + 135 * 1, 180, 135}},
		{ID_BIGBOMB_5, {0}, {180 * 1, 115 + 135 * 1, 180, 135}},
		{ID_BIGBOMB_6, {0}, {180 * 2, 115 + 135 * 1, 180, 135}},
		{ID_BIGBOMB_7, {0}, {180 * 3, 115 + 135 * 1, 180, 135}}
	};

#define NR_RES (sizeof(res_idc)/sizeof(res_idc[0]))

#define NR_ITEM NR_RES

static ITEM item[NR_ITEM];

void init_res()
{
    uint32_t i;
    SDL_Surface *pic = NULL;
#ifdef _WIN32
    pic = SDL_LoadBMP("data\\picture.bmp");
#else
    pic = SDL_LoadBMP("data/picture.bmp");
#endif
    Assert(pic != NULL, "pic not found!\n");

#ifdef _WIN32
	background = SDL_LoadBMP("data\\background.bmp");
#else
	background = SDL_LoadBMP("data/background.bmp");
#endif
    Assert(background != NULL, "bk not found!\n");

    SDL_Rect srcrect, dstrect;

    for(i = 0; i < NR_RES; i++)
    {
        SDL_Surface *optimized;
        SDL_Surface *tmp = SDL_CreateRGBSurface(SDL_SWSURFACE, res_idc[i].rect.w, res_idc[i].rect.h, 32,
                                                0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
        if(tmp == NULL)
            panic("error occured!\n");
        srcrect.x = res_idc[i].rect.x;
        srcrect.y = res_idc[i].rect.y;
        dstrect.x = 0;
        dstrect.y = 0;
        dstrect.w = srcrect.w = res_idc[i].rect.w;
        dstrect.h = srcrect.h = res_idc[i].rect.h;

        SDL_BlitSurface(pic, &srcrect, tmp, &dstrect);

        optimized = SDL_DisplayFormat(tmp);
        SDL_FreeSurface(tmp);

        uint32_t colorkey = SDL_MapRGB(optimized->format, 0xff, 0, 0xff);
        SDL_SetColorKey(optimized, SDL_SRCCOLORKEY, colorkey);

        //SDL_BlitSurface(optimized, NULL, screen, NULL);

        item[res_idc[i].ID].load_surface(optimized);

        //item[res_idc[i].ID].show(screen, 80, 80);
    }

    SDL_FreeSurface(pic);
}

void UpdateScreen()
{
	SDL_BlitSurface(background, NULL, screen, NULL);
}

void show_item(uint32_t itemID, float x, float y)
{
    Assert((itemID >= 0) && (itemID < NR_ITEM), "Invalid itemID!\n");
    item[itemID].show(screen, x, y);
}

POINT query_itemwh(uint32_t itemID)
{
    Assert(itemID < NR_ITEM, "Invalid itemID!\n");
    SDL_Surface *item_surface = item[itemID].query_surface();
	return POINT(item_surface->w, item_surface->h);
}

bool is_offscreen(uint32_t itemID, POINT pos)
{
    SDL_Surface *item_surface = item[itemID].query_surface();
    int dx = abs(pos.x + ((item_surface->w - screen->w) >> 1));
    int dy = abs(pos.y + ((item_surface->h - screen->h) >> 1));
    int dw = ((item_surface->w + screen->w) >> 1);
    int dh = ((item_surface->h + screen->h) >> 1);
    return ((dx > dw) || (dy > dh));
}

bool query_item_collision(uint32_t itemID, int i, int j)
{
	SDL_Surface *item_surface = item[itemID].query_surface();
	assert(i >= 0 && i < item_surface->w && j>= 0 && j < item_surface->h);
	uint8_t * pixels = (uint8_t *)(item_surface->pixels);
	return (pixels[3 * i + j] != 0xff
		&&  pixels[3 * i + j + 1] != 0x0
		&&  pixels[3 * i + j + 2] != 0xff);
}

uint32_t query_life_atk(uint32_t itemID)
{
	Assert(itemID < NR_ITEM, "Invalid itemID!\n");
	return res_idc[itemID].life;
}

void set_life_atk(uint32_t itemID, int life_atk)
{
	Assert(itemID < NR_ITEM, "Invalid itemID!\n");
	res_idc[itemID].life = life_atk;
}

void draw_strip(int part, uint32_t total, int x, int y)
{
	uint32_t i, j;
	SDL_Surface *item_surface = item[ID_BLOOD].query_surface();
	uint32_t *pixels = (uint32_t * )item_surface->pixels;
	if(part < 0)
		part = 0;
	else if((uint32_t)part >= total)
		part = total;

	for(i = 0; i < BLOOD_W; i ++)
	{
		pixels[i + 0 * BLOOD_W] = 0x00ff0000;
		pixels[i + (BLOOD_H - 1) * BLOOD_W] = 0x00ff0000;
	}

	for(j = 0; j < BLOOD_H; j ++)
	{
	 	pixels[0  + j * BLOOD_W] = 0x00ff0000;
		pixels[BLOOD_W - 1 + j * BLOOD_W] = 0x00ff0000;
	}

	for(i = 0; i < BLOOD_W * part / total; i++)
		for(j = 0; j < BLOOD_H; j++)
		{
			pixels[i + j * BLOOD_W] = 0x00ff0000;
		}
	for(i = BLOOD_W * part / total + 1; i < BLOOD_W; i++)
		for(j = 0; j < BLOOD_H; j++)
		{
			pixels[i + j * BLOOD_W] = 0x00ff00ff;
		}
	item[ID_BLOOD].show(screen, x, y);

	draw_str(x + BLOOD_W, y, 0x3f, 2, "%d/%d", part, total);
}
