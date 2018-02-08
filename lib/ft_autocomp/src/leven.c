#include "../inc/levenshtein.h"

int			min_ope(int a, int b, int c)
{
	if (a < b && a < c)
		return (a);
	else if (b < a && b < c)
		return (b);
	return (c);
}

int			lev_distance(char *s1, char *s2)
{
	static int		matrix[CMD_SIZE][CMD_SIZE];
	int				x;
	int				y;
	int				len1;
	int				len2;

	x = 1;
	y = 1;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	matrix[0][0] = 0;
	while (y < len1)
	{
		matrix[0][y] = y;
		y++;
	}
	return (0);
}
