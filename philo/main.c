#include "philo.h"

int	main(int argc, char **argv)
{
	t_args		args;

	if (get_args(&args, argc, argv))
		return (1);
	if (args.num_of_philos > 1)
		init_philos(&args);
	else if (args.num_of_philos == 1)
		one_philo(&args);
	return (0);
}
