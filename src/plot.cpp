#include "common.h"
#include "bullet.h"
#include "plane.h"
#include "plot.h"

PLOT plot [] = {
	{{ID_DOT, ID_ENEMY, IDBF_SPEEDLINE, PI / 3 + 0.25, 2 *PI / 3, 1}, ID_ENEMY, 3, IDPF_LINE, {POINT(100, 1), 1, 0, 0}, 0}
};

#define NR_PLOT (sizeof(plot) / sizeof(plot[0]))
