#include "common.h"

void ITEM::load_surface(SDL_Surface * optimized)
{
    surface = optimized;
}

SDL_Surface * ITEM::query_surface()
{
    return surface;
}

void ITEM::show(SDL_Surface * screen, float px, float py)
{
    SDL_Rect srcrect, dstrect;
    
    srcrect.x = srcrect.y = 0;
    srcrect.w = surface->w;
    srcrect.h = surface->h;
    
    dstrect.x = px - (surface->w >> 1);
    dstrect.y = py - (surface->h >> 1);
    dstrect.w = surface->w;
    dstrect.h = surface->h;
    
    SDL_BlitSurface(surface, &srcrect, screen, &dstrect);

}
