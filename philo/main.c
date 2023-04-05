//add 42 header!

#include "philosophers.h"

void	feed_stack(int argc, char **argv)
{
	t_data	stack;
	int		philo_total;

	if (argc <= 6)
	{
		stack_init(&stack);
		philo_total = ft_atoi(argv[1]);
		stack.philo_total = ft_atoi(argv[1]);
		stack.time_till_death = ft_atoi(argv[2]);
		stack.time_to_eat = ft_atoi(argv[3]);
		stack.time_to_sleep = ft_atoi(argv[4]);
		stack.nbr_of_meals = -1;
		if (argc == 6)
			stack.nbr_of_meals = ft_atoi(argv[5]);
		else
			stack.nbr_of_meals = -1;
		if (!(stack.fork == malloc(sizeof(pthread_mutex_t) * philo_total)))
			return ;
		if (!(stack.philo == malloc(sizeof(t_philo) * philo_total)))
			return ;
		philo_init(&stack);
	}
}

int main (int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if ((philo_is_digit(argc, argv) == 0) && (philo_is_valid(argc, argv) == 0))
		{
			feed_stack(argc, argv);
		}
		return (0);
	}
}