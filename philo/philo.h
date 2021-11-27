#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_args
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eats;
	int				is_died;
	int				printed_died;
	pthread_mutex_t	mutex_died;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_live;
	pthread_mutex_t	*mutex_fork;
}					t_args;

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
int		ft_isnumber(char *str);
void	init_philos(t_args *args);
void	one_philo(t_args *args);
long	get_time(void);
void	*simulation(void *philo);
void	put_status(t_philo *philo, char *str);
char	*ft_itoa(int n);

#endif
