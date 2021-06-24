#include "includes.h"

t_list	*ft_lstnew(int numb)
{
	t_list	*temp;

	temp = malloc(sizeof(t_list));
	if (!temp)
		return (NULL);
	temp->numb = numb;
	temp->number_times_eat = 0;
	temp->next = NULL;
	return (temp);
}

void	ft_lstdel(t_list **lst)
{
	t_list	*temp;
	size_t	i;

	if (*lst == 0)
		return ;
	i = 1;
	while (i <= (*lst)->param->number_of_philosophers && (*lst))
	{
		temp = (*lst)->next;
		free((*lst)->thread);
		free((*lst)->time_end_eat);
		pthread_mutex_destroy((*lst)->l_fork->mutex);
		free((*lst)->l_fork->mutex);
		free((*lst)->l_fork);
		if (i == (*lst)->param->number_of_philosophers)
		{
			free((*lst)->param);
			free(*lst);
			return ;
		}
		free(*lst);
		*lst = temp;
		i++;
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new)
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

t_list	*ft_lstnum(t_list *lst, int num)
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
