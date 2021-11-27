#include "philo_bonus.h"

static void	init_one_philo(t_philo *philo, t_args *args, int nmb)
{
	philo->philo_num = nmb;
	philo->args = args;
	philo->num_of_eats = args->num_of_eats;
}

static void	end_of_eating(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->num_of_philos)
		sem_wait(args->end_of_eat);
	sem_post(args->exit);
}

static void	ft_close_sem(t_args *args)
{
	sem_close(args->sem_live);
	sem_close(args->sem_died);
	sem_close(args->sem_print);
	sem_close(args->sem_fork);
	sem_close(args->waiter);
	sem_close(args->exit);
	sem_close(args->end_of_eat);
	sem_unlink("sem_live");
	sem_unlink("sem_died");
	sem_unlink("sem_print");
	sem_unlink("sem_fork");
	sem_unlink("waiter");
	sem_unlink("exit");
	sem_unlink("end_of_eat");
}

static void	life_cycle(int *i, t_args *args, t_philo *philo, pid_t *pid)
{
	while (++(*i) < args->num_of_philos)
	{
		init_one_philo(&philo[*i], args, *i);
		pid[*i] = fork();
		if (pid[*i] < 0)
			exit(1);
		else if (pid[*i] == 0)
			simulation((void *)&philo[*i]);
	}
}

void	init_philos(t_args *args)
{
	t_philo	*philo;
	pid_t	*pid;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * args->num_of_philos);
	if (!philo)
		return ;
	pid = (pid_t *)malloc(sizeof(pid_t) * args->num_of_philos + 1);
	if (!pid)
		return ;
	life_cycle(&i, args, philo, pid);
	pid[i] = fork();
	if (pid[i] < 0)
		exit(1);
	else if (pid[i] == 0)
		end_of_eating(args);
	sem_wait(args->exit);
	i = -1;
	while (++i < args->num_of_philos)
		kill(pid[i], SIGKILL);
	ft_close_sem(args);
	free(philo);
	free(pid);
}
