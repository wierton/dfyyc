#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <SDL/SDL.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "debug.h"
#include "item.h"
#include "msg.h"
#include "bomb.h"

#include "resource/video.h"

#define BK_W 800
#define BK_H 600

#define is_inbounder(x, y) ((x < BK_W) && (x >= 0) && (y < BK_H) && (y >= 0))

typedef uint32_t HANDLE;

#ifdef dist
#	undef dist
#else
inline float dist(POINT a, POINT b)
{
    float dx = fabs(a.x-b.x);
    float dy = fabs(a.y-b.y);
    return sqrt(dx*dx+dy*dy);
}
#endif

#define INF 0x7fffffff

#define INVALID_HANDLE_VALUE 0xffffffff

#define PI 3.1415926

#define E 2.71828

void UpdateScreen();

#endif
