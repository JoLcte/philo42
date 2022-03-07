#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

int	main()
{
	struct timeval t0;
	struct timeval tf;
	long int start;
	long int now;
	long int delta_t;
	
	gettimeofday(&t0, NULL);
	start = t0.tv_sec * 1000 + t0.tv_usec * 0.001;
	usleep(200000);
	gettimeofday(&tf, NULL);
	now = tf.tv_sec * 1000 + tf.tv_usec * 0.001;
	printf("delta = %ld\n", now - start);
	return (0);
}
