#include "includes.h"

int		ft_atoi_end(char *str, size_t *num)
{
	int i;

	i = 0;
	*num = 0;
	while (str[i] > 47 && str[i] < 58)
	{
		*num = *num * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != 0 || str[0] == 0)
		return (1);
	return (0);
}
