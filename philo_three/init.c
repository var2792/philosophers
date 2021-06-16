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
	sem_unlink("/forks");
	if (!(param->phis->forks = sem_open("/forks", O_CREAT, S_IROTH | S_IWOTH, param->phis->number_of_philosophers)))
		return (error_mess(1, 3, 1, param));
	while (i <= param->phis->number_of_philosophers)
	{
		if (!(temp = ft_lstnew(i)))
			return (error_mess(1, 3, 1, param));
		if (!(temp->time_end_eat = malloc(sizeof(struct timeval))))
			return (error_mess(1, 3, 1, param));
		temp->param = param->phis;
		if (i == param->phis->number_of_philosophers)
			temp->next = ft_lstnum(param->lst_phi, 1);
		ft_lstadd_back(&(param->lst_phi), temp);
		i++;
	}
	return (0);
}

void	wait_phis(t_list *lst_phi)
{
	size_t	i;
	int		status;

	i = 0;
	status = 0;
	printf("waaaaaiiiiit\n");
	while ((!status) && i < lst_phi->param->number_of_philosophers)
	{
		if (waitpid(-1, &status, 0) < 0)
			return ;
		i++;
		lst_phi = lst_phi->next;
	}
	printf("%d\n", status);
	usleep(3 * 1000);
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
