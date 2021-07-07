#include "functions.h"

static void	simple(size_t sec, size_t usec, size_t numb, char f)
{
	if (f == 'f')
		printf("%lu%lu %lu has taken a fork\n",
			sec, usec, numb);
	if (f == 'e')
		printf("%lu%lu %lu is eating\n",
			sec, usec, numb);
	if (f == 's')
		printf("%lu%lu %lu is sleeping\n",
			sec, usec, numb);
	if (f == 't')
		printf("%lu%lu %lu is thinking\n",
			sec, usec, numb);
}

static void	hard0(size_t sec, size_t usec, size_t numb, char f)
{
	if (f == 'f')
		printf("%lu%c%lu %lu has taken a fork\n",
			sec, '0', usec, numb);
	if (f == 'e')
		printf("%lu%c%lu %lu is eating\n",
			sec, '0', usec, numb);
	if (f == 's')
		printf("%lu%c%lu %lu is sleeping\n",
			sec, '0', usec, numb);
	if (f == 't')
		printf("%lu%c%lu %lu is thinking\n",
			sec, '0', usec, numb);
}

static void	hard00(size_t sec, size_t usec, size_t numb, char f)
{
	if (f == 'f')
		printf("%lu%s%lu %lu has taken a fork\n",
			sec, "00", usec, numb);
	if (f == 'e')
		printf("%lu%s%lu %lu is eating\n",
			sec, "00", usec, numb);
	if (f == 's')
		printf("%lu%s%lu %lu is sleeping\n",
			sec, "00", usec, numb);
	if (f == 't')
		printf("%lu%s%lu %lu is thinking\n",
			sec, "00", usec, numb);
}

static void	mes_died(size_t sec, size_t usec, size_t numb)
{
	if (usec > 99)
	printf("%lu%lu %lu is died\n",
		sec, usec, numb);
	if (usec < 100 && usec > 9)
	printf("%lu%c%lu %lu is died\n",
		sec, '0', usec, numb);
	if (usec < 10)
	printf("%lu%s%lu %lu is died\n",
		sec, "00", usec, numb);
}

int	mes_about_phi(int simul, size_t numb, char f)
{
	struct timeval	now;
	size_t usec;

	if (gettimeofday(&now, NULL))
		return (0);
	usec = (size_t)(now.tv_usec / 1000);
	if (f == 'd')
		mes_died(now.tv_sec, usec, numb);
	if (f == 'm')
		printf("message of %lu <<<<=================\n", numb);
	if (simul)
	{
		if (usec > 99)
			simple(now.tv_sec, usec, numb, f);
		if (usec < 100 && usec > 9)
			hard0(now.tv_sec, usec, numb, f);
		if (usec < 10)
			hard00(now.tv_sec, usec, numb, f);
		return (0);
	}
	return (1);
}
