#include "includes.h"

int	ft_atoi_end(char *str, size_t *num)
{
	int	i;

	i = 0;
	*num = 0;
	while (str[i] > 47 && str[i] < 58)
	{
		*num = *num * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != 0 || str[0] == 0)
		return (1);
	return (0);
}

float	dif_time_mc(struct timeval *t1, struct timeval *t2)
{
	float	t;

	t = (t2->tv_sec - t1->tv_sec) * 1000;
	t = t + (t2->tv_usec - t1->tv_usec) / 1000;
	return (t);
}

int	check_time(struct timeval *time_end_eat, size_t time_to_die)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (dif_time_mc(time_end_eat, &now) > time_to_die)
		return (1);
	return (0);
}

int	die_while_sleep(t_list	phi)
{
	if (phi.param->time_to_sleep < phi.param->time_to_die + 10)
		usleep(phi.param->time_to_sleep * 1000);
	else
		usleep(phi.param->time_to_die * 1000);
	if (check_time(phi.time_end_eat, phi.param->time_to_die))
		return (1);
	return (0);
}

int	mes_about_phi(int simul, size_t numb, char f)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL))
		return (0);
	if (simul)
	{
		if (f == 'f')
			printf("%lu%lu %lu has taken a fork\n",
				now.tv_sec, (size_t)(now.tv_usec / 1000), numb);
		if (f == 'e')
			printf("%lu%lu %lu is eating\n",
				now.tv_sec, (size_t)(now.tv_usec / 1000), numb);
		if (f == 's')
			printf("%lu%lu %lu is sleeping\n",
				now.tv_sec, (size_t)(now.tv_usec / 1000), numb);
		if (f == 't')
			printf("%lu%lu %lu is thinking\n",
				now.tv_sec, (size_t)(now.tv_usec / 1000), numb);
		return (0);
	}
	if (f == 'd')
		printf("%lu%lu %lu died\n",
			now.tv_sec, (size_t)(now.tv_usec / 1000), numb);
	return (1);
}
