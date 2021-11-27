#include "philo.h"

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

static void	*death(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	pthread_mutex_lock(&philo->args->mutex_live);
	while ((get_time() - philo->last_eating) <= philo->args->time_to_die && \
	philo->num_of_eats != 0 && philo->args->is_died == 0)
	{
		pthread_mutex_unlock(&philo->args->mutex_live);
		usleep(10);
		pthread_mutex_lock(&philo->args->mutex_live);
	}
	pthread_mutex_unlock(&philo->args->mutex_live);
	if (philo->num_of_eats == 0)
		return (NULL);
	else
	{
		pthread_mutex_lock(&philo->args->mutex_died);
		philo->args->is_died = 1;
		put_status((t_philo *)philo, "died");
		philo->args->printed_died = 1;
		pthread_mutex_unlock(&philo->args->mutex_died);
	}
	return (NULL);
}

static void	eating(t_philo *philo)
{
	if (philo->philo_num % 2 == 1)
		pthread_mutex_lock(&philo->args->mutex_fork[philo->philo_num]);
	else
		pthread_mutex_lock(&philo->args->mutex_fork[(philo->philo_num + 1) % \
		philo->args->num_of_philos]);
	put_status((t_philo *)philo, "has taken a fork");
	if (philo->philo_num % 2 == 1)
		pthread_mutex_lock(&philo->args->mutex_fork[(philo->philo_num + 1) % \
		philo->args->num_of_philos]);
	else
		pthread_mutex_lock(&philo->args->mutex_fork[philo->philo_num]);
	put_status(philo, "has taken a fork");
	put_status(philo, "is eating");
	philo->last_eating = get_time();
	ft_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(&philo->args->mutex_fork[(philo->philo_num + 1) % \
	philo->args->num_of_philos]);
	pthread_mutex_unlock(&philo->args->mutex_fork[philo->philo_num]);
	put_status(philo, "is sleeping");
	--philo->num_of_eats;
	ft_usleep(philo->args->time_to_sleep);
	put_status(philo, "is thinking");
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
