#include "philo_bonus.h"

long	get_time(void)
{
	long			time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

static void	ft_usleep(int time)
{
	long	start;
	long	stop;
	long	diff;

	start = get_time();
	stop = get_time();
	diff = stop - start;
	while (diff < time)
	{
		stop = get_time();
		diff = stop - start;
		usleep(10);
	}
}

void	*death(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	sem_wait(philo->args->sem_live);
	while ((get_time() - philo->last_eating) <= philo->args->time_to_die && \
	philo->num_of_eats != 0)
	{
		sem_post(philo->args->sem_live);
		usleep(10);
		sem_wait(philo->args->sem_live);
	}
	sem_post(philo->args->sem_live);
	if (philo->num_of_eats == 0)
	{
		sem_post(philo->args->end_of_eat);
		exit(0);
	}
	else
	{
		sem_wait(philo->args->sem_died);
		put_status(philo, "died", 1);
		sem_post(philo->args->exit);
	}
	return (NULL);
}

static void	eating(t_philo *philo)
{
	sem_wait(philo->args->waiter);
	sem_wait(philo->args->sem_fork);
	put_status(philo, "has taken a fork", 0);
	sem_wait(philo->args->sem_fork);
	put_status(philo, "has taken a fork", 0);
	sem_post(philo->args->waiter);
	put_status(philo, "is eating", 0);
	philo->last_eating = get_time();
	ft_usleep(philo->args->time_to_eat);
	sem_post(philo->args->sem_fork);
	sem_post(philo->args->sem_fork);
	put_status(philo, "is sleeping", 0);
	--philo->num_of_eats;
	ft_usleep(philo->args->time_to_sleep);
	put_status(philo, "is thinking", 0);
}

void	*simulation(void *philos)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)philos;
	philo->start_time = get_time();
	philo->last_eating = philo->start_time;
	pthread_create(&thread, NULL, death, philo);
	while (philo->num_of_eats != 0 && !philo->args->is_died)
		eating(philo);
	pthread_join(thread, NULL);
	return (NULL);
}
