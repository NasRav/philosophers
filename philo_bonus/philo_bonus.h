#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_args
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_eats;
	int		is_died;
	sem_t	*waiter;
	sem_t	*sem_died;
	sem_t	*sem_print;
	sem_t	*sem_live;
	sem_t	*sem_fork;
	sem_t	*end_of_eat;
	sem_t	*exit;
}			t_args;

typedef struct s_philo
{
	int		philo_num;
	long	start_time;
	long	last_eating;
	int		num_of_eats;
	t_args	*args;
}			t_philo;

int		get_args(t_args *args, int ac, char **av);
void	ft_putstr_fd(char *s, int fd);
void	*simulation(void *philo);
void	init_philos(t_args *args);
long	get_time(void);
void	put_status(t_philo *philo, char *str, int flag);
char	*ft_itoa(int n);
int		ft_isnumber(char *str);

#endif
