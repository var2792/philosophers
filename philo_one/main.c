#include "functions.h"

void	*phi_live(void *phi_v)
{
	t_list	*phi;
	int		i;
	int		fl;

	i = 1;
	fl = 1;
	phi = (t_list *)phi_v;
	while (fl == 1
		&& i != phi->param->number_of_time_each_philosophers_must_eat)
	{
		fl = one_live(phi);
		i++;
	}
	phi->status = 0;
	if (phi->param->simul)
	{
		if (fl == 0 && !phi->param->stop)
		{
			phi->param->simul = 0;
			mes_about_phi(phi->param->simul, phi->numb, 'd');
		}
	}
	return (0);
}

int	philo_at_launch(t_param *param)
{
	size_t	i;

	i = 1;
	while (i <= param->phis->number_of_philosophers)
	{
		gettimeofday(ft_lstnum(param->lst_phi, i)->time_end_eat, NULL);
		if (pthread_create(param->lst_phi->thread, NULL,
				phi_live, (void *)ft_lstnum(param->lst_phi, i)) != 0)
			return (error_mess(1, 4, 0, 0));
		pthread_detach(*(param->lst_phi->thread));
		i++;
	}
	wait_phis(param->lst_phi);
	return (0);
}

int	main(int argc, char **argv)
{
	t_param	param;

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
	}
	else
		write(1, "Error arguments!\n", 17);
	return (0);
}
