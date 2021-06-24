#include "includes.h"

int	take_forks(t_list	*phi)
{
	t_fork	*fork;
	int		i;

	fork = phi->r_fork;
	if (phi->numb % 2)
		fork = phi->l_fork;
	i = 0;
	while (i++ < 2)
	{
		while (take_fork(fork))
		{
			if (check_time(phi->time_end_eat, phi->param->time_to_die))
			{
				if (retu_fork(phi->l_fork) || retu_fork(phi->r_fork))
					return (error_mess(0, 3, 0, 0));
				return (0);
			}
		}
		if (mes_about_phi(phi->param->simul, phi->numb, 'f'))
			return (0);
		fork = phi->l_fork;
		if (phi->numb % 2)
			fork = phi->r_fork;
	}
	return (1);
}

int	eating_back(t_list	*phi)
{
	if (check_time(phi->time_end_eat, phi->param->time_to_die))
	{
		if (retu_fork(phi->l_fork) || retu_fork(phi->r_fork))
			return (error_mess(0, 3, 0, 0));
		return (0);
	}
	if (mes_about_phi(phi->param->simul, phi->numb, 'e'))
		return (0);
	usleep(phi->param->time_to_eat * 1000);
	gettimeofday(phi->time_end_eat, NULL);
	if (retu_fork(phi->l_fork) || retu_fork(phi->r_fork))
		return (error_mess(0, 3, 0, 0));
	if (check_time(phi->time_end_eat, phi->param->time_to_die))
		return (0);
	return (1);
}

int	one_live(t_list	*phi)
{
	if (mes_about_phi(phi->param->simul, phi->numb, 't'))
		return (0);
	if (phi->param->number_of_philosophers == 1)
	{
		while (die_while_sleep(*phi) == 0)
			NULL;
		return (0);
	}
	if (!take_forks(phi))
		return (0);
	if (!eating_back(phi))
		return (0);
	if (mes_about_phi(phi->param->simul, phi->numb, 's'))
		return (0);
	if (die_while_sleep(*phi))
		return (0);
	return (1);
}
