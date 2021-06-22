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
	usleep(phi->param->time_to_eat * 1000);
	gettimeofday(phi->time_end_eat, NULL);
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

void	phi_live(t_list* phi)
{
	int		i;
	int		fl;

	i = 1;
	printf("phi %d proc %d\n", phi->numb, phi->pid);
	if (phi->pid < 0)
	{
		exit(1);
		return ;
	}
	while ((fl = one_live(phi)) == 1 && i != phi->param->number_of_time_each_philosophers_must_eat)
		i++;
	phi->is_alive = 0;
	if (fl == 0 && !phi->param->stop)
		mes_about_phi(phi->numb, 'd');
	mes_about_phi(phi->numb, 'm');
	exit(0);
}

int		philo_at_launch(t_param *param)
{
	size_t	i;
	t_list	*temp;

	i = 1;
	while (i <= param->phis->number_of_philosophers)
	{
		temp = ft_lstnum(param->lst_phi, i);
		if (gettimeofday(temp->time_end_eat, NULL))
			return (error_mess(1, 3, 0, 0));
		if ((temp->pid = fork()) != 0)
			phi_live(temp);
		if (temp->pid < 0)
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
		usleep(1000000);
		printf("That's all!\n");
	}
	else
		write(1, "Error arguments!\n", 17);
	return (0);
}
