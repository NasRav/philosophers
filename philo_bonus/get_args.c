#include "philo_bonus.h"

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

void	init_sem(t_args *args)
{
	sem_unlink("sem_live");
	sem_unlink("sem_died");
	sem_unlink("sem_print");
	sem_unlink("sem_fork");
	sem_unlink("waiter");
	sem_unlink("exit");
	sem_unlink("end_of_eat");
	args->sem_live = sem_open("sem_live", O_CREAT, 0666, 1);
	args->sem_died = sem_open("sem_died", O_CREAT, 0666, 1);
	args->sem_print = sem_open("sem_print", O_CREAT, 0666, 1);
	args->sem_fork = sem_open("sem_fork", O_CREAT, 0666, args->num_of_philos);
	args->waiter = sem_open("waiter", O_CREAT, 0666, 1);
	args->exit = sem_open("exit", O_CREAT, 0666, 0);
	args->end_of_eat = sem_open("end_of_eat", O_CREAT, 0666, 0);
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
	init_sem(args);
	init_philos(args);
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
