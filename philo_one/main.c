#include "includes.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

void	print_phils(t_list *lst_phi)
{
	while (lst_phi)
	{
		printf("phi %i: alive-%i, time_eat-%lu, num_eat-%lu\n", lst_phi->numb, lst_phi->is_alive, lst_phi->time_end_eat, lst_phi->number_times_eat);
		lst_phi = lst_phi->next;
	}
}

int		philo_at_launch(t_philos phis, t_list **lst_phi)
{
	(void)phis;
	(void)lst_phi;

	struct timeval start;
	gettimeofday(&start, NULL);
	printf("gettime %lu %lu\n", start.tv_sec, start.tv_usec);
	gettimeofday(&start, NULL);
	printf("gettime %lu %lu\n", start.tv_sec, start.tv_usec);
	return (0);
}

int		init_philos(t_philos phis, t_list **lst_phi)
{
	size_t i;

	i = 1;
	while (i <= phis.number_of_philosophers)
	{
		if (ft_lstadd_back(lst_phi, ft_lstnew(i, 1, 0, 0)))
			return (1);
		i++;
	}
	return (0);
}

int		main(int argc, char** argv)
{
	t_philos	phis;
	t_list		*lst_phi;

	lst_phi = 0;
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi_end(argv[1], &(phis.number_of_philosophers)))
			return (0);
		if (ft_atoi_end(argv[2], &(phis.time_to_die)))
			return (0);
		if (ft_atoi_end(argv[3], &(phis.time_to_eat)))
			return (0);
		if (ft_atoi_end(argv[4], &(phis.time_to_sleep)))
			return (0);
		if (argc == 5)
			phis.number_of_time_each_philosophers_must_eat = -1;
		else
			if (ft_atoi_end(argv[5], (size_t*)(&(phis.number_of_time_each_philosophers_must_eat))))
				return (0);
		//printf("%s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);
		printf("Arguments: num-%lu, die-%lu mc, eat-%lu mc, sleep-%lu mc\n", phis.number_of_philosophers, phis.time_to_die, phis.time_to_eat, phis.time_to_sleep);
		if (init_philos(phis, &lst_phi))
			return (0); //error free t_list
		print_phils(lst_phi);
		if (philo_at_launch(phis, &lst_phi))
			return (0); //error free t_list
	}
	else
		write(1, "Error arguments!\n", 17);
	return (0);
}
