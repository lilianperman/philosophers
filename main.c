#include "philosophers.h"

void	stack_init(t_data *stack)
{
	stack->philo_total = 0;
	stack->time_till_starvation = 0;
	stack->time_to_eat = 0;
	stack->time_to_sleep = 0;
	stack->meals_till_satiation = 0;
	stack->fork = 0;
	stack->is_full = 0;
	stack->is_dead = 0;
	stack->start_time = 0;
}

void	fill_stack(int argc, char **argv)
{
	t_data	stack;
	int	philo_total;

	if (argc == 5 || argc == 6)
	{
		stack_init(&stack);
		philo_total = philo_atoi(argv[1]);
		stack.philo_total = philo_atoi(argv[1]);
		stack.time_till_starvation = philo_atoi(argv[2]);
		stack.time_to_eat = philo_atoi(argv[3]);
		stack.time_to_sleep = philo_atoi(argv[4]);
		stack.is_dead = 0;
		stack.is_full = 0;
		stack.start_time = 0;
		stack.meals_till_satiation = -1;
		if (argv[5])
			stack.meals_till_satiation = philo_atoi(argv[5]);
		stack.fork = malloc(sizeof(pthread_mutex_t) * philo_total);
		if (!stack.fork)
			return ;
		stack.philo = malloc(sizeof(t_philo) * philo_total);
		if (!stack.philo)
			return ;
		philo_init(&stack);
	}
}

int main (int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (philo_is_digit(argc, argv) == 0 && (philo_is_valid(argc, argv) == 0))
			fill_stack(argc, argv);
	}
	return (0);
}
