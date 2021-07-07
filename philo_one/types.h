#ifndef TYPES_H
# define TYPES_H

# include "includes.h"

typedef struct s_philos
{
	size_t			number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				number_of_time_each_philosophers_must_eat;
	int				stop;
	int				simul;
}				t_philos;

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
	int				num;
}				t_fork;

typedef struct s_list
{
	size_t			numb;
	pthread_t		*thread;
	t_philos		*param;
	struct timeval	*time_end_eat;
	size_t			number_times_eat;
	t_fork			*l_fork;
	t_fork			*r_fork;
	int				status;
	struct s_list	*next;
}				t_list;

typedef struct s_param
{
	t_philos	*phis;
	t_list		*lst_phi;
}				t_param;

#endif
