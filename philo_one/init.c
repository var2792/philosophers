#include "includes.h"

int		read_param(int argc, char** argv, t_param* param)
{
		if (!(param->phis = malloc(sizeof(t_philos))))
			return (1);
		if (ft_atoi_end(argv[1], &(param->phis->number_of_philosophers)))
			return (1);
		if (param->phis->number_of_philosophers < 2)
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
			temp->l_fork = malloc(sizeof(t_fork));
			temp->l_fork->mutex = malloc(sizeof(pthread_mutex_t));
			temp->l_fork->num = i;
		}
		else
			temp->l_fork = ft_lstnum(param->lst_phi, i - 1)->r_fork;
		if (i != param->phis->number_of_philosophers)
		{
			temp->r_fork = malloc(sizeof(t_fork));
			temp->r_fork->mutex = malloc(sizeof(pthread_mutex_t));
			temp->l_fork->num = i;
		}
		else
		{
			temp->r_fork = ft_lstnum(param->lst_phi, 1)->l_fork;
			temp->next = ft_lstnum(param->lst_phi, 1);
		}
		pthread_mutex_init(temp->r_fork->mutex, NULL);
		temp->thread = malloc(sizeof(pthread_t));
		temp->time_end_eat = malloc(sizeof(struct timeval));
		temp->pphi = param->phis;
		ft_lstadd_back(&(param->lst_phi), temp);
		i++;
	}
	return (0);
}
