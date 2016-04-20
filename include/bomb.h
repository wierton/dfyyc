#ifndef __BOMB_H__
#define __BOMB_H__

#define NR_BOMB 100

#define NR_DELAYPERCALL 10

enum BOMB_TYPE {IDB_SMALL, IDB_BIG};

typedef struct tagBOMBINFO {
	POINT pos;
	int p;
	BOMB_TYPE bomb_type;
} BOMBINFO, *LPBOMBINFO;

void add_bomb(POINT pos, BOMB_TYPE bomb_type);
void show_bomb();

#endif
