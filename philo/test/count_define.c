#include <stdio.h>
#include <unistd.h>
#include <string.h>
# define WRONG_VAL "\e[48;5;124m \
Error: wrong value. Arguments must be unsigned integers.\e[m\n"
# define TOO_BIG "\e[48;5;124m \
Error: too big value. Arguments must be smaller than INTMAX.\e[m\n"
# define WRONG_SETUP "\e[48;5;124m \
Error: try [nb_philo][time_to_die][time_to_eat][time_to_sleep][nb_meals]\e[m\n"
# define NO_ZERO "\e[48;5;124m \
Error: null value. Arguments must be greater than 0.\e[m\n"

int	main()
{
	printf("len WRONG_VAL = %d\n%s", strlen(WRONG_VAL), WRONG_VAL);
	printf("len TOO_BIG = %d\n%s", strlen(TOO_BIG), TOO_BIG);
	printf("len WRONG_SETUP = %d\n%s", strlen(WRONG_SETUP), WRONG_SETUP);
	printf("len NO_ZERO = %d\n%s", strlen(NO_ZERO), NO_ZERO);
}
