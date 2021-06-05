#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# include <string.h>

typedef struct	s_philos
{
	size_t		number_of_philosophers;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int		number_of_time_each_philosophers_must_eat;
}				t_philos;

typedef struct	s_list
{
	int			numb;
	int			is_alive;
	size_t		time_end_eat;
	size_t		number_times_eat;
	struct s_list * next;
}				t_list;

/*typedef struct	timeval
{
	time_t		tv_sec;     // seconds
    suseconds_t	tv_usec;    // microseconds
}				t_timeval;*/

int		ft_atoi_end(char *str, size_t *num);
t_list	*ft_lstnew(int numb, int is_alive, size_t time_end_eat, size_t number_times_eat);
void	ft_lstdel(t_list **lst);
int		ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnum(t_list *lst, int num);

#endif
