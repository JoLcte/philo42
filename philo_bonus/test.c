#include <stdio.h>
#include <unistd.h>
#include <string.h>

void	add_and_print_buff(char *s, int size, int print)
{
	char buff[1000];
	static int	idx_save;
	int		i;

	i = 0;
	while (i < size)
	{
		buff[idx_save + i] = s[i];
		++i;
	}
	idx_save += size;
	if (print)
	{
		buff[idx_save] = '\0';
		write(1, buff, idx_save);
		idx_save = 0;
	}
}

int	main()
{
	add_and_print_buff("\e[38;5;45m", 10, 0);
	add_and_print_buff("coucou ", 7, 0);
	add_and_print_buff("c'est moi ", 10, 0);
	add_and_print_buff("!\e[m\n", 5, 1);
	add_and_print_buff("\e[38;5;45m", 10, 0);
	add_and_print_buff("coucou ", 7, 0);
	add_and_print_buff("c'est re moi ", 13, 0);
	add_and_print_buff("!\e[m\n", 5, 1);
	return (0);
}
