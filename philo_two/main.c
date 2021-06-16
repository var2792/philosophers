#include "includes.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

//защита всех маллоков в функции и mutex_init'ов
//printf("heeeeeeyyyyy\n");

int		one_live(t_list	*phi)
{
	mes_about_phi(phi->numb, 't');
	if (sem_wait(phi->param->forks))
		return (error_mess(0, 3, 0, 0));
	if (sem_wait(phi->param->forks))
		return (error_mess(0, 3, 0, 0));
	if (check_time(phi->time_end_eat, phi->param->time_to_die))
	{
		if (sem_post(phi->param->forks))
			return (error_mess(0, 3, 0, 0));
		if (sem_post(phi->param->forks))
			return (error_mess(0, 3, 0, 0));
		return (0);
	}
	mes_about_phi(phi->numb, 'f');
	mes_about_phi(phi->numb, 'e');
	if (usleep(phi->param->time_to_eat * 1000))
		return (error_mess(0, 3, 0, 0));
	if (gettimeofday(phi->time_end_eat, NULL))
		return (error_mess(0, 3, 0, 0));
	if (sem_post(phi->param->forks))
		return (error_mess(0, 3, 0, 0));
	if (sem_post(phi->param->forks))
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

	i = 1;
	phi = (t_list*)phi_v;
	while (one_live(phi) && i != phi->param->number_of_time_each_philosophers_must_eat)
		i++;
	phi->is_alive = 0;
	if (!phi->param->stop)
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
