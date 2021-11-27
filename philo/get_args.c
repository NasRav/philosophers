#include "philo.h"

static int	ft_atoi(const char *nptr)
{
	int			sign;
	long int	num;

	num = 0;
	sign = 1;
	while (*nptr && (*nptr == '\t' || *nptr == '\n' || *nptr == '\v' || \
			*nptr == '\f' || *nptr == '\r' || *nptr == ' '))
		++nptr;
	if (*nptr == '-')
	{
		sign = -1;
		++nptr;
	}
	else if (*nptr == '+')
		++nptr;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (num > num * 10 + (*nptr - '0') && sign == 1)
			return (-1);
		else if (num > num * 10 + (*nptr - '0') && sign == -1)
			return (0);
		num = num * 10 + (*nptr - '0');
		++nptr;
	}
	return (sign * num);
}

static void	init_forks(t_args *args)
{
	int		i;

	i = 0;
	args->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
	args->num_of_philos);
	if (!(args->mutex_fork))
		return ;
	while (i < args->num_of_philos)
		pthread_mutex_init(&args->mutex_fork[i++], NULL);
}

static int	init_args(t_args *args, int ac, char **av)
{
	args->num_of_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		args->num_of_eats = ft_atoi(av[5]);
		if (args->num_of_eats < 0)
			return (1);
	}
	else
		args->num_of_eats = -1;
	if (args->num_of_philos < 0 || args->time_to_die < 0 || \
	args->time_to_eat < 0 || args->time_to_sleep < 0)
		return (1);
	args->is_died = 0;
	args->printed_died = 0;
	pthread_mutex_init(&args->mutex_live, NULL);
	pthread_mutex_init(&args->mutex_died, NULL);
	pthread_mutex_init(&args->mutex_print, NULL);
	init_forks(args);
	return (0);
}

int	get_args(t_args *args, int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Wrong number of arguments\n", STDERR_FILENO);
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (!ft_isnumber(av[i]))
		{
			ft_putstr_fd("Arguments should be numbers\n", STDERR_FILENO);
			return (1);
		}
		++i;
	}
	if (init_args(args, ac, av))
	{
		ft_putstr_fd("Invalid arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
