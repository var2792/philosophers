#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "includes.h"
# include "types.h"

int		ft_atoi_end(char *str, size_t *num);
float	dif_time_mc(struct timeval *t1, struct timeval *t2);
int		check_time(struct timeval *time_end_eat, size_t time_to_die);
int		die_while_sleep(t_list	phi);
int		mes_about_phi(int simul, size_t numb, char f);

t_list	*ft_lstnew(int numb);
void	ft_lstdel(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *newls);
t_list	*ft_lstnum(t_list *lst, int num);

int		read_param(int argc, char **argv, t_param *param);
int		init_philos(t_param *param);
void	wait_phis(t_list *lst_phi);
int		error_mess(int ret, int fl, int del, t_param *param);

int		take_fork(t_fork *fork);
int		retu_fork(t_fork *fork);
int		one_live(t_list	*phi);
#endif
