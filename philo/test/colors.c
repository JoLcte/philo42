#include <stdio.h>
#include <stdlib.h>

#define R 100 - (i % 100)
#define B 230 - (i % 230)
#define COLORDIED "\e[48;2;%d;0;%dmPhilo %d died\e[m\n"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (printf("Give me a number between 1 and 200\n"));
	int n = atoi(av[1]);
	int i = 1;
	while (i < n)
	{
		printf(COLORDIED, R, B, i);
		++i;
	}
	return (0);
}
