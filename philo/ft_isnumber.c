#include "philo.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || \
	c == ' ')
		return (1);
	else
		return (0);
}

int	ft_isnumber(char *str)
{
	while (*str && ft_isspace(*str))
		++str;
	if (!*str)
		return (0);
	if (*str == '-' || *str == '+')
		++str;
	if (!*str)
		return (0);
	while (*str)
	{
		if ((*str < '0' || *str > '9') && !ft_isspace(*str))
			return (0);
		else if (ft_isspace(*str))
		{
			while (ft_isspace(*str))
				++str;
			if (*str && !ft_isspace(*str))
				return (0);
			else
				return (1);
		}
		++str;
	}
	return (1);
}
