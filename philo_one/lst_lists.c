#include "includes.h"

t_list				*ft_lstnew(int numb, int is_alive, size_t time_end_eat, size_t number_times_eat)
{
	t_list *temp;

	if (!(temp = malloc(sizeof(t_list))))
		return (NULL);
	temp->numb = numb;
	temp->is_alive = is_alive;
	temp->time_end_eat = time_end_eat;
	temp->number_times_eat = number_times_eat;
	temp->next = NULL;
	return (temp);
}


void	ft_lstdel(t_list **lst)
{
	t_list *temp;

	if (*lst == 0)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
}

int					ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (new == 0)
		return (1);
	if (!(*lst))
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
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