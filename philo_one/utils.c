#include "includes.h"

int		ft_atoi_end(char *str, size_t *num)
{
	int i;

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
	float t;

	t = (t2->tv_sec - t1->tv_sec) * 1000;
	t = t + (t2->tv_usec - t1->tv_usec) / 1000;
	return (t);
}

int		check_time(struct timeval *time_end_eat, size_t time_to_die)
{
	struct timeval now;
	
	gettimeofday(&now, NULL);
	if (dif_time_mc(time_end_eat, &now) > time_to_die)
		return (1);
	return (0);
}

void	wait_phis(t_list *lst_phi)
{
	size_t i;
	
	i = 0;
	while (i < lst_phi->pphi->number_of_philosophers)
	{
		if (lst_phi->is_alive == 0)
			i++;
		else
			i = 0;
		lst_phi = lst_phi->next;
		//printf("is_alive %lu\n", i);
	}
}

int		error_mess(int fl, t_param *param)
{
	ft_lstdel(&(param->lst_phi));
	if (fl == 1)
		printf("Some error!\n");
	return (0);
}
