#ifndef __MSG_H__
#define __MSG_H__


typedef unsigned long long DWORD;

typedef enum tagPALDIRECTION {
    kdirUp = 0,
    kdirDown,
    kdirLeft,
    kdirRight,
    kdirUnknown
} PALDIRECTION, *LPPALDIRECTION;

typedef struct tagINPUTSTATE {
    PALDIRECTION prevdir, dir;
    SDLKey dwKey;
} INPUTSTATE;

#define SDLK_Unknown SDLK_0

extern INPUTSTATE g_InputState;

void msgloop();

#endif
