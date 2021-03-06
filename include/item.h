#ifndef __ITEM_H__
#define __ITEM_H__

#define BLOOD_W 50
#define BLOOD_H 16

enum ID_ITEM {
	ID_PLAYER,
	ID_ENEMY,
	ID_DOT,
	ID_BLOOD,
	ID_SMALLBOMB_0,
	ID_SMALLBOMB_1,
	ID_SMALLBOMB_2,
	ID_SMALLBOMB_3,
	ID_SMALLBOMB_4,
	ID_SMALLBOMB_5,
	ID_SMALLBOMB_6,
	ID_SMALLBOMB_7,
	ID_BIGBOMB_0,
	ID_BIGBOMB_1,
	ID_BIGBOMB_2,
	ID_BIGBOMB_3,
	ID_BIGBOMB_4,
	ID_BIGBOMB_5,
	ID_BIGBOMB_6,
	ID_BIGBOMB_7,
	ID_CHAR
};

struct POINT {
    float x,y;
    POINT(float a = 0, float b = 1)
    {
        x = a;
        y = b;
    }
};

typedef POINT (*CALC_TRAIL_FUNC)(POINT, POINT, POINT);

class ITEM {
    SDL_Surface *surface;
public:
    ITEM(){surface = NULL;}
    
    void load_surface(SDL_Surface * screen);
    
    SDL_Surface *query_surface();
    
    void show(SDL_Surface * screen, float px, float py);
};

bool is_offscreen(uint32_t itemID, POINT pos);
void show_item(uint32_t, float, float);
POINT query_itemwh(uint32_t);
bool query_item_collision(uint32_t, int, int);
uint32_t query_life_atk(uint32_t);
void draw_strip(int, uint32_t, int, int);

#endif
