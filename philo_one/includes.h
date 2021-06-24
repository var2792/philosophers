#ifndef INCL_PHILO_ONE_H
# define INCL_PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

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
	struct s_list	*next;
}				t_list;

typedef struct s_param
{
	t_philos	*phis;
	t_list		*lst_phi;
}				t_param;

int		ft_atoi_end(char *str, size_t *num);
float	dif_time_mc(struct timeval *t1, struct timeval *t2);
int		check_time(struct timeval *time_end_eat, size_t time_to_die);
int		die_while_sleep(t_list	phi);
int		mes_about_phi(int simul, size_t numb, char f);

t_list	*ft_lstnew(int numb);
void	ft_lstdel(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnum(t_list *lst, int num);

int		read_param(int argc, char **argv, t_param *param);
int		init_philos(t_param *param);
void	wait_phis(t_list *lst_phi);
int		error_mess(int ret, int fl, int del, t_param *param);

int		take_fork(t_fork *fork);
int		retu_fork(t_fork *fork);
int		one_live(t_list	*phi);
#endif
