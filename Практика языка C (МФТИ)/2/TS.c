#if 1
struct point_t {
	int x, y;
};
struct triangle_t {
	struct point_t pts[3];
};
#else
#include "u_template.h"
#endif

int double_area(struct triangle_t tr)
{
	int res;
	struct point_t v[2];
	v[0].x = tr.pts[1].x - tr.pts[0].x;
	v[0].y = tr.pts[1].y - tr.pts[0].y;
	v[1].x = tr.pts[2].x - tr.pts[0].x;
	v[1].y = tr.pts[2].y - tr.pts[0].y;
	res = v[0].x * v[1].y - v[0].y * v[1].x;
	return res < 0 ? -res : res;
}

#if 1
#include <stdio.h>

int main()
{
	int res;
	struct triangle_t tr;
	for (int i = 0; i < 3; ++i) {
		scanf("%d%d", &tr.pts[i].x, &tr.pts[i].y);
	}
	res = double_area(tr);
	printf("%d\n", res);
	return 0;
}
#endif
