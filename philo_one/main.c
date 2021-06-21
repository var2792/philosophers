#include "includes.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

//защита всех маллоков в функции и mutex_init'ов
//printf("heeeeeeyyyyy\n");

int		one_live(t_list	*phi)
{
	t_fork	*fork;
	int	i;

	mes_about_phi(phi->numb, 't');
	fork = (phi->numb % 2) ? phi->l_fork : phi->r_fork;
	i = 0;
	if (phi->param->number_of_philosophers == 1)
	{
		while (die_while_sleep(*phi) == 0);
		return (0);
	}
	while (i < 2)
	{
		if (pthread_mutex_lock(fork->mutex))
			return (error_mess(0, 3, 0, 0));
		if (check_time(phi->time_end_eat, phi->param->time_to_die))
			return (0);
		if (i == 0)
			fork = (phi->numb % 2) ? phi->r_fork : phi->l_fork;
		else
			break;
		i++;
	}
	if (check_time(phi->time_end_eat, phi->param->time_to_die))
	{
		if (pthread_mutex_unlock(phi->l_fork->mutex))
			return (error_mess(0, 3, 0, 0));
		if (pthread_mutex_unlock(phi->r_fork->mutex))
			return (error_mess(0, 3, 0, 0));
		return (0);
	}
	//printf("%lu000 %d has taken a fork %d %d\n", time_ret(), phi->numb, phi->l_fork->num, phi->r_fork->num);
	mes_about_phi(phi->numb, 'f');
	mes_about_phi(phi->numb, 'e');
	if (gettimeofday(phi->time_end_eat, NULL))
		return (error_mess(0, 3, 0, 0));
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
	phi = (t_list*)phi_v;
	while ((fl = one_live(phi)) == 1 && i != phi->param->number_of_time_each_philosophers_must_eat)
		i++;
	phi->is_alive = 0;
	if (fl == 0 && !phi->param->stop)
			mes_about_phi(phi->numb, 'd');
	return (0);
}

int		philo_at_launch(t_param *param)
{
	size_t i;

	i = 1;
	while (i <= param->phis->number_of_philosophers)
	{
		if (gettimeofday(ft_lstnum(param->lst_phi, i)->time_end_eat, NULL))
			return (error_mess(1, 3, 0, 0));
		if (pthread_create(param->lst_phi->thread, NULL, phi_live, (void*)ft_lstnum(param->lst_phi, i)) != 0)
			return (error_mess(1, 4, 0, 0));
		i++;
	}
	wait_phis(param->lst_phi);
	return (0);
}

int		main(int argc, char** argv)
{
	t_param		param;

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
