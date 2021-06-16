#include "includes.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

//защита всех маллоков в функции и mutex_init'ов
//printf("heeeeeeyyyyy\n");

int		one_live(t_list	*phi)
{
	if (sem_wait(phi->param->forks))
		return (0);
	if (sem_wait(phi->param->forks))
		return (0);
	if (check_time(phi->time_end_eat, phi->param->time_to_die))
	{
		if (sem_post(phi->param->forks))
			return (0);
		if (sem_post(phi->param->forks))
			return (0);
		return (0);
	}
	printf("timestamp_in_ms %d has taken a fork\n", phi->numb);
	printf("timestamp_in_ms %d is eating\n", phi->numb);
	usleep(phi->param->time_to_eat * 1000);
	gettimeofday(phi->time_end_eat, NULL);
	if (sem_post(phi->param->forks))
		return (0);
	if (sem_post(phi->param->forks))
		return (0);
	if (check_time(phi->time_end_eat, phi->param->time_to_die))
		return (0);
	printf("timestamp_in_ms %d is sleeping\n", phi->numb);
	if (die_while_sleep(*phi))
		return (0);
	printf("timestamp_in_ms %d is thinking\n", phi->numb);
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
	printf("timestamp_in_ms %d died\n", phi->numb);
	return (0);
}

int		philo_at_launch(t_param *param)
{
	size_t i;

	i = 1;
	while (i <= param->phis->number_of_philosophers)
	{
		gettimeofday(ft_lstnum(param->lst_phi, i)->time_end_eat, NULL);
		if (pthread_create(param->lst_phi->thread, NULL, phi_live, (void*)ft_lstnum(param->lst_phi, i)) != 0)
			return (1);
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
			return (error_mess(1, &param));
		if (init_philos(&param))
			return (error_mess(1, &param));
		if (philo_at_launch(&param))
			return (error_mess(1, &param));
		printf("That's all!\n");
	}
	else
		write(1, "Error arguments!\n", 17);
	return (0);
}
