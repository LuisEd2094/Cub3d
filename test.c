#include <math.h>
#include <stdio.h>

int	main(void)
{
	int		i;
	float	x;
	float	y;
	float	x1, y1;
	float	x2, y2, dx, dy, step;

	x1 = 1;
	y1 = 1;
	x2 = 3;
	y2 = 4;

	dx = x2 - x1;
	dy = y2 - y1;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = x1;
	y = y1;
	i = 0;
	while (i <= step)
	{
		printf("%d - x: %f, y: %f\n", i, x, y);
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
}