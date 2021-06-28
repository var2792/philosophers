#include "functions.h"

int	take_fork(t_fork *fork)
{
	if (fork->num)
	{
		if (pthread_mutex_lock(fork->mutex))
			return (error_mess(0, 3, 0, 0));
		fork->num = 0;
	}
	else
		return (1);
	return (0);
}

int	retu_fork(t_fork *fork)
{
	if (pthread_mutex_unlock(fork->mutex))
		return (error_mess(1, 3, 0, 0));
	fork->num = 1;
	return (0);
}

int	read_param(int argc, char **argv, t_param *param)
{
	param->phis = malloc(sizeof(t_philos));
	if (!(param->phis))
		return (1);
	if (ft_atoi_end(argv[1], &(param->phis->number_of_philosophers)))
		return (1);
	if (param->phis->number_of_philosophers < 1)
		return (1);
	if (ft_atoi_end(argv[2], &(param->phis->time_to_die)))
		return (1);
	if (ft_atoi_end(argv[3], &(param->phis->time_to_eat)))
		return (1);
	if (ft_atoi_end(argv[4], &(param->phis->time_to_sleep)))
		return (1);
	param->phis->number_of_time_each_philosophers_must_eat = -1;
	if (argc == 6)
		if (ft_atoi_end(argv[5], (size_t *)
				(&(param->phis->number_of_time_each_philosophers_must_eat))))
			return (1);
	if (param->phis->number_of_time_each_philosophers_must_eat == 0)
		return (1);
	param->phis->stop = 0;
	param->phis->simul = 1;
	return (0);
}

void	wait_phis(t_list *lst_phi)
{
	size_t	i;

	i = 1;
	while (lst_phi->param->simul)
		NULL;
	while (i < lst_phi->param->number_of_philosophers && lst_phi)
	{
		pthread_join(*(lst_phi->thread), NULL);
		i++;
		lst_phi = lst_phi->next;
	}
	usleep(10 * 1000);
}

int	error_mess(int ret, int fl, int del, t_param *param)
{
	param->phis->stop = 1;
	if (fl == 1)
		write(1, "Some error!\n", 12);
	if (fl == 2)
		write(1, "Error of enter parameters!\n", 27);
	if (fl == 3)
		write(1, "Error of system - malloc or other function!\n", 44);
	if (fl == 4)
		write(1, "Error of threads!\n", 18);
	if (fl == 5)
		write(1, "Error of ...!\n", 14);
	if (del)
		ft_lstdel(&(param->lst_phi));
	return (ret);
}
