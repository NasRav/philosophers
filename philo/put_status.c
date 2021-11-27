#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i])
			++i;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

static void	status_msg(t_philo *philo, char *str)
{
	char	msg[255];
	char	*s1;
	char	*s2;
	int		i;
	int		j;

	s1 = ft_itoa(get_time() - philo->start_time);
	s2 = ft_itoa(philo->philo_num + 1);
	i = -1;
	while (s1[++i])
		msg[i] = s1[i];
	msg[i++] = ' ';
	free(s1);
	j = -1;
	while (s2[++j])
		msg[i++] = s2[j];
	msg[i++] = ' ';
	free(s2);
	j = -1;
	while (str[++j])
		msg[i++] = str[j];
	msg[i++] = '\n';
	msg[i] = '\0';
	ft_putstr_fd(msg, STDOUT_FILENO);
}

void	put_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->args->mutex_print);
	if (philo->args->is_died && philo->args->printed_died)
	{
		pthread_mutex_unlock(&philo->args->mutex_print);
		return ;
	}
	status_msg(philo, str);
	pthread_mutex_unlock(&philo->args->mutex_print);
}
