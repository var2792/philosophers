#include "includes.h"

int		read_param(int argc, char** argv, t_param* param)
{
		if (!(param->phis = malloc(sizeof(t_philos))))
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
		if (argc == 5)
			param->phis->number_of_time_each_philosophers_must_eat = -1;
		else
			if (ft_atoi_end(argv[5], (size_t*)(&(param->phis->number_of_time_each_philosophers_must_eat))))
				return (1);
		if (param->phis->number_of_time_each_philosophers_must_eat == 0)
			return(1);
		param->phis->stop = 0;
		printf("Arguments: num-%lu, die-%lu mc, eat-%lu mc, sleep-%lu mc\n", param->phis->number_of_philosophers, param->phis->time_to_die, param->phis->time_to_eat, param->phis->time_to_sleep);
		return (0);
}

int		init_philos(t_param *param)
{
	size_t i;
	t_list *temp;

	i = 1;
	while (i <= param->phis->number_of_philosophers)
	{
		if (!(temp = ft_lstnew(i)))
			return (1);
		if (i == 1)
		{
			if (!(temp->l_fork = malloc(sizeof(t_fork))))
				return (error_mess(1, 3, 1, param));
			if (!(temp->l_fork->mutex = malloc(sizeof(pthread_mutex_t))))
				return (error_mess(1, 3, 1, param));
			temp->l_fork->num = i;
		}
		else
			temp->l_fork = ft_lstnum(param->lst_phi, i - 1)->r_fork;
		if (param->phis->number_of_philosophers != 1)
		{
			if (i != param->phis->number_of_philosophers)
			{
				if (!(temp->r_fork = malloc(sizeof(t_fork))))
					return (error_mess(1, 3, 1, param));
				if (!(temp->r_fork->mutex = malloc(sizeof(pthread_mutex_t))))
					return (error_mess(1, 3, 1, param));
				temp->r_fork->num = i + 1;
			}
			else
			{
				temp->r_fork = ft_lstnum(param->lst_phi, 1)->l_fork;
				temp->next = ft_lstnum(param->lst_phi, 1);
			}
		}
		else
			temp->r_fork = NULL;
		if (pthread_mutex_init(temp->l_fork->mutex, NULL))
			return (error_mess(1, 3, 1, param));
		if (!(temp->thread = malloc(sizeof(pthread_t))))
			return (error_mess(1, 3, 1, param));
		if (!(temp->time_end_eat = malloc(sizeof(struct timeval))))
			return (error_mess(1, 3, 1, param));
		temp->param = param->phis;
		ft_lstadd_back(&(param->lst_phi), temp);
		i++;
	}
	return (0);
}

void	wait_phis(t_list *lst_phi)
{
	size_t i;

	i = 0;
	while (i < lst_phi->param->number_of_philosophers)
	{
		if (lst_phi->is_alive == 0)
			i++;
		else
			i = 0;
		if (lst_phi->param->number_of_philosophers !=1)
			lst_phi = lst_phi->next;
	}
	usleep(1 * 1000);
}

int		error_mess(int ret, int fl, int del, t_param *param)
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
