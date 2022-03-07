#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

int	main()
{
	struct timeval t0;
	struct timeval tf;
	long int start;
	long int now;
	long int delta_t;
	
	gettimeofday(&t0, NULL);
	start = t0.tv_sec * 1000 + t0.tv_usec * 0.001;
	gettimeofday(&tf, NULL);
	now = tf.tv_sec * 1000 + tf.tv_usec * 0.001;
	delta_t = now - start;
	int i = 0;
	while (delta_t < 400)
	{	
		++i;
		usleep(200 * 0.1);
		gettimeofday(&tf, NULL);
		now = tf.tv_sec * 1000 + tf.tv_usec * 0.001;
		delta_t = now - start;
	}
	printf("i = %d\n", i);
	return (0);
}
