#include "functions.h"

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
	if (dif_time_mc(time_end_eat, &now) + 10 > time_to_die)
		return (1);
	return (0);
}

int	die_while_sleep(t_list	phi)
{
	if (phi.param->time_to_sleep + 10 < phi.param->time_to_die)
		usleep(phi.param->time_to_sleep * 1000);
	else
	{
		usleep(phi.param->time_to_die * 1000);
		return (1);
	}
	if (check_time(phi.time_end_eat, phi.param->time_to_die))
		return (1);
	return (0);
}
