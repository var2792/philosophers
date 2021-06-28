#include "functions.h"

int	right_fork_for_phi(t_param *param, t_list	*temp, size_t i)
{
	if (param->phis->number_of_philosophers != 1)
	{
		if (i != param->phis->number_of_philosophers)
		{
			temp->r_fork = malloc(sizeof(t_fork));
			if (!(temp->r_fork))
				return (error_mess(1, 3, 1, param));
			temp->r_fork->mutex = malloc(sizeof(pthread_mutex_t));
			if (!(temp->r_fork->mutex))
				return (error_mess(1, 3, 1, param));
			temp->r_fork->num = 1;
		}
		else
		{
			temp->r_fork = ft_lstnum(param->lst_phi, 1)->l_fork;
			temp->next = ft_lstnum(param->lst_phi, 1);
		}
	}
	else
		temp->r_fork = NULL;
	return (0);
}

int	left_fork_for_phi(t_param *param, t_list	*temp, size_t i)
{
	if (i == 1)
	{
		temp->l_fork = malloc(sizeof(t_fork));
		if (!(temp->l_fork))
			return (error_mess(1, 3, 1, param));
		temp->l_fork->mutex = malloc(sizeof(pthread_mutex_t));
		if (!(temp->l_fork->mutex))
			return (error_mess(1, 3, 1, param));
		temp->l_fork->num = 1;
	}
	else
		temp->l_fork = ft_lstnum(param->lst_phi, i - 1)->r_fork;
	return (0);
}

int	init_philos(t_param *param)
{
	size_t	i;
	t_list	*temp;

	i = 1;
	while (i <= param->phis->number_of_philosophers)
	{
		temp = ft_lstnew(i);
		if (!(temp))
			return (1);
		if (left_fork_for_phi(param, temp, i)
			|| right_fork_for_phi(param, temp, i))
			return (1);
		if (pthread_mutex_init(temp->l_fork->mutex, NULL))
			return (error_mess(1, 3, 1, param));
		temp->thread = malloc(sizeof(pthread_t));
		if (!(temp->thread))
			return (error_mess(1, 3, 1, param));
		temp->time_end_eat = malloc(sizeof(struct timeval));
		if (!(temp->time_end_eat))
			return (error_mess(1, 3, 1, param));
		temp->param = param->phis;
		ft_lstadd_back(&(param->lst_phi), temp);
		i++;
	}
	return (0);
}
