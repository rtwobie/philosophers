#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void	*routine1(void *ptr)
{
	(void)ptr;
	for (int i = 0; i < 8; i++)
	{
		printf("marx[%i]\n", i);
		printf("marx: sleeping...\n");
		sleep(3);
		printf("marx: thinking...\n");
		sleep(1);
		printf("marx: eating...\n");
		sleep(2);
	}
	printf("marx: died...\n");
	return (0);
}

void	*routine2(void *ptr)
{
	(void)ptr;
	for (int i = 0; i < 4; i++)
	{
		printf("pascal[%i]\n", i);
		printf("pascal: eating...\n");
		sleep(2);
		printf("pascal: sleeping...\n");
		sleep(3);
		printf("pascal: thinking...\n");
		sleep(1);
	}
	printf("pascal: died...\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	pthread_t	marx;
	pthread_t	pascal;

	pthread_create(&marx, NULL, routine1, NULL);
	pthread_create(&pascal, NULL, routine2, NULL);
	pthread_join(marx, NULL);
}
