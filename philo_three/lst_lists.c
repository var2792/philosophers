#include "includes.h"

t_list				*ft_lstnew(int numb)
{
	t_list *temp;

	if (!(temp = malloc(sizeof(t_list))))
		return (NULL);
	temp->numb = numb;
	temp->is_alive = 1;
	temp->number_times_eat = 0;
	temp->next = NULL;
	return (temp);
}


void	ft_lstdel(t_list **lst)
{
	t_list *temp;
	size_t	i;

	if (*lst == 0)
		return ;
	i = 1;
	while (i <= (*lst)->param->number_of_philosophers && (*lst))
	{
		temp = (*lst)->next;
		free((*lst)->time_end_eat);
		kill((*lst)->pid, SIGTERM);
		if (i == (*lst)->param->number_of_philosophers)
		{
			sem_close((*lst)->param->forks);
			sem_unlink("/forks");
			free((*lst)->param);
			free(*lst);
			return ;
		}
		free(*lst);
		*lst = temp;
		i++;
	}
}

void					ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!(*lst))
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_list				*ft_lstnum(t_list *lst, int num)
{
	t_list	*temp;
	int		i;

	temp = lst;
	i = 1;
	while (temp && i < num)
	{
		if (temp->next == 0)
			break ;
		else
			temp = temp->next;
		i++;
	}
	if (i == num)
		return (temp);
	else
		return (NULL);
}
