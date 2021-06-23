#include "includes.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

int	one_live(t_list	*phi)
{
	t_fork	*fork;
	int		i;

	mes_about_phi(phi->numb, 't');
	if (phi->numb % 2)
		fork = phi->l_fork;
	else
		fork = phi->r_fork;
	i = 0;
	if (phi->param->number_of_philosophers == 1)
	{
		while (die_while_sleep(*phi) == 0)
			NULL;
		return (0);
	}
	while (i < 2)
	{
		while (take_fork(fork))
		{
			if (check_time(phi->time_end_eat, phi->param->time_to_die))
			{
				if (retu_fork(phi->l_fork))
					return (error_mess(0, 3, 0, 0));
				if (retu_fork(phi->r_fork))
					return (error_mess(0, 3, 0, 0));
				return (0);
			}
		}
		if (i == 1)
			break ;
		if (phi->numb % 2)
			fork = phi->r_fork;
		else
			fork = phi->l_fork;
		i++;
	}
	if (check_time(phi->time_end_eat, phi->param->time_to_die))
	{
		if (retu_fork(phi->l_fork))
			return (error_mess(0, 3, 0, 0));
		if (retu_fork(phi->r_fork))
			return (error_mess(0, 3, 0, 0));
		return (0);
	}
	mes_about_phi(phi->numb, 'f');
	mes_about_phi(phi->numb, 'e');
	usleep(phi->param->time_to_eat * 1000);
	gettimeofday(phi->time_end_eat, NULL);
	if (pthread_mutex_unlock(phi->l_fork->mutex))
		return (error_mess(0, 3, 0, 0));
	if (pthread_mutex_unlock(phi->r_fork->mutex))
		return (error_mess(0, 3, 0, 0));
	if (check_time(phi->time_end_eat, phi->param->time_to_die))
		return (0);
	mes_about_phi(phi->numb, 's');
	if (die_while_sleep(*phi))
		return (0);
	return (1);
}

void	*phi_live(void *phi_v)
{
	t_list	*phi;
	int		i;
	int		fl;

	i = 1;
	fl = 1;
	phi = (t_list *)phi_v;
	while (fl == 1 && i != phi->param->number_of_time_each_philosophers_must_eat)
	{
		fl = one_live(phi);
		i++;
	}
	phi->is_alive = 0;
	if (fl == 0 && !phi->param->stop)
		mes_about_phi(phi->numb, 'd');
	return (0);
}

int	philo_at_launch(t_param *param)
{
	size_t	i;

	i = 1;
	while (i <= param->phis->number_of_philosophers)
	{
		gettimeofday(ft_lstnum(param->lst_phi, i)->time_end_eat, NULL);
		if (pthread_create(param->lst_phi->thread, NULL,
				phi_live, (void *)ft_lstnum(param->lst_phi, i)) != 0)
			return (error_mess(1, 4, 0, 0));
		i++;
	}
	wait_phis(param->lst_phi);
	return (0);
}

int	main(int argc, char **argv)
{
	t_param	param;

	param.lst_phi = NULL;
	if (argc == 5 || argc == 6)
	{
		if (read_param(argc, argv, &param))
			return (error_mess(0, 2, 1, &param));
		if (init_philos(&param))
			return (0);
		philo_at_launch(&param);
		if (param.lst_phi != NULL)
			ft_lstdel(&(param.lst_phi));
		printf("That's all!\n");
	}
	else
		write(1, "Error arguments!\n", 17);
	return (0);
}
