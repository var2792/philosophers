#include "includes.h"

int	take_fork(t_fork *fork)
{
	if (fork->num)
	{
		if (pthread_mutex_lock(fork->mutex))
			return (error_mess(0, 3, 0, 0));
		fork->num = 0;
	}
	else
		return (1);
	return (0);
}

int	retu_fork(t_fork *fork)
{
	if (pthread_mutex_unlock(fork->mutex))
		return (error_mess(1, 3, 0, 0));
	fork->num = 1;
	return (0);
}
