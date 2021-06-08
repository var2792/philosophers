#include "includes.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

void	print_phils(t_list *lst_phi)
{
	while (lst_phi)
	{
		printf("phi %i: alive-%i, num_eat-%lu\n", lst_phi->numb, lst_phi->is_alive, lst_phi->number_times_eat);
		lst_phi = lst_phi->next;
	}
}

void	*phi_live(void *param_v)
{
	t_param	*param;
	t_list	*phi;
	int	nb;
	struct timeval	*tnow;

	param = (t_param*)param_v;
	nb = param->nb;
	if (!(tnow = malloc(sizeof(struct timeval))))
	{
		param->fl = 0;
		return (0);
	}
	phi = ft_lstnum(param->lst_phi, nb);
	while (phi->number_forks != 2)
	{
		pthread_mutex_lock(param->fork.mutex);
		if (param->fork.num >= 2)
		{
			param->fork.num -= 2;
			phi->number_forks = 2;
			printf("timestamp_in_ms %d has taken a fork\n", nb);
		}
		pthread_mutex_unlock(param->fork.mutex);
	}
	printf("timestamp_in_ms %d is eating\n", nb);
	usleep(param->phis.time_to_eat * 1000);
	gettimeofday(phi->time_end_eat, NULL);
	phi->number_forks = 0;
	param->fork.num += 2;
	gettimeofday(tnow, NULL);
	printf("timestamp_in_ms %d is sleeping\n", nb);
	while (dif_time_mc(tnow, phi->time_end_eat) < param->phis.time_to_sleep * 1000)
	{
		if (dif_time_mc(tnow, phi->time_end_eat) > param->phis.time_to_die)
		{
			phi->is_alive = 0;
			break ;
		}
		usleep(3 * 1000);
		gettimeofday(tnow, NULL);
	}
	if (!phi->is_alive)
	{
		printf("timestamp_in_ms %d died\n", nb);
		return (0);
	}
	else
		printf("timestamp_in_ms %d is thinking\n", nb);
	//printf("live phi %i\n", phi->numb);
	return (0);
}

int		philo_at_launch(t_param *param)
{
	pthread_t threads[param->phis.number_of_philosophers];
	size_t i;

	i = 0;
	printf("heeeeeeyyyyy\n");
	pthread_mutex_init(param->fork.mutex, NULL);
	printf("heeeeeeyyyyy\n");
	if (!(param->st_time = malloc(sizeof(struct timeval))))
		return (1);
	gettimeofday(param->st_time, NULL);
	while (i < param->phis.number_of_philosophers)
	{
		param->nb = i;
		if (pthread_create(&(threads[i]), NULL, &phi_live, (void*)param) != 0)
			return (1);
		if (param->fl == 0)
			return (1);
		i++;
	}
	return (0);
}

int		init_philos(t_param *param)
{
	size_t i;

	i = 1;
	while (i <= param->phis.number_of_philosophers)
	{
		if (ft_lstadd_back(&(param->lst_phi), ft_lstnew(i)))
			return (1);
		i++;
	}
	return (0);
}

int		main(int argc, char** argv)
{
	t_param		param;

	param.lst_phi = NULL;
	param.fl = 1;
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi_end(argv[1], &(param.phis.number_of_philosophers)))
			return (0);
		param.fork.num = param.phis.number_of_philosophers;
		if (ft_atoi_end(argv[2], &(param.phis.time_to_die)))
			return (0);
		if (ft_atoi_end(argv[3], &(param.phis.time_to_eat)))
			return (0);
		if (ft_atoi_end(argv[4], &(param.phis.time_to_sleep)))
			return (0);
		if (argc == 5)
			param.phis.number_of_time_each_philosophers_must_eat = -1;
		else
			if (ft_atoi_end(argv[5], (size_t*)(&(param.phis.number_of_time_each_philosophers_must_eat))))
				return (0);
		//printf("%s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);
		printf("Arguments: num-%lu, die-%lu mc, eat-%lu mc, sleep-%lu mc\n", param.phis.number_of_philosophers, param.phis.time_to_die, param.phis.time_to_eat, param.phis.time_to_sleep);
		if (init_philos(&param))
			return (0); //error free t_list
		print_phils(param.lst_phi);
		if (philo_at_launch(&param))
			return (0); //error free t_list
	}
	else
		write(1, "Error arguments!\n", 17);
	return (0);
}
