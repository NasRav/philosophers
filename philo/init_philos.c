#include "philo.h"

static void	init_one_philo(t_philo *philo, t_args *args, int num)
{
	philo->philo_num = num;
	philo->args = args;
	philo->num_of_eats = args->num_of_eats;
}

void	init_philos(t_args *args)
{
	t_philo		*philo;
	pthread_t	*thread;
	int			i;

	philo = (t_philo *)malloc(sizeof(t_philo) * args->num_of_philos);
	if (!philo)
		return ;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * args->num_of_philos);
	if (!thread)
		return ;
	i = -1;
	while (++i < args->num_of_philos)
	{
		init_one_philo(&philo[i], args, i);
		pthread_create(&thread[i], NULL, simulation, &philo[i]);
	}
	i = -1;
	while (++i < args->num_of_philos)
		pthread_join(thread[i], NULL);
	i = -1;
	while (++i < args->num_of_philos)
		pthread_mutex_destroy(&args->mutex_fork[i]);
	free(args->mutex_fork);
	free(philo);
	free(thread);
}

void	one_philo(t_args *args)
{
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * args->num_of_philos);
	if (!philo)
		return ;
	init_one_philo(&philo[0], args, 0);
	philo->start_time = get_time();
	put_status(philo, "has taken a fork");
	usleep(args->time_to_die * 1000);
	put_status(philo, "is died");
	pthread_mutex_destroy(&args->mutex_fork[0]);
	free(args->mutex_fork);
	free(philo);
}
