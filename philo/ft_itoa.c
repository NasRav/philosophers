#include "philo.h"

static int	n_len(long int n)
{
	int			len;
	long int	tmp;

	if (n < 0)
	{
		len = 2;
		tmp = -n;
	}
	else
	{
		len = 1;
		tmp = n;
	}
	while (tmp >= 10)
	{
		tmp /= 10;
		len++;
	}
	return (len);
}

static int	current_pos(long int n)
{
	long int	cur_pos;
	long int	tmp;

	cur_pos = 1;
	if (n > 0)
		tmp = n;
	else
		tmp = -n;
	while (tmp >= 10)
	{
		tmp /= 10;
		cur_pos *= 10;
	}
	return (cur_pos);
}

char	*ft_itoa(int n)
{
	char		*s;
	long int	tmp;
	int			i;
	long int	cur_pos;

	i = 0;
	s = (char *)malloc(sizeof(char) * (n_len((long int)n) + 1));
	if (!s)
		return (0);
	cur_pos = current_pos((long int)n);
	if (n < 0)
	{
		s[i++] = '-';
		tmp = -(long int)n;
	}
	else
		tmp = (long int)n;
	while (cur_pos >= 1)
	{
		s[i++] = tmp / cur_pos + '0';
		tmp %= cur_pos;
		cur_pos /= 10;
	}
	s[i] = '\0';
	return (s);
}
