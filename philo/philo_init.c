//add 42 header!

#include "philosophers.h"

void	philo_create(t_data *stack)
{
	int	i;
	int	philo_total;
	t_philo	*philo;
	pthread_t	monitor;

	i = 0;
	philo = stack->philo;
	philo_total = stack->philo_total;
	stack->start_time = get_time();
	while (i < philo_total)
	{
		pthread_create(&(philo[i].thread), NULL, &start_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo_total)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_create(&monitor, NULL, &checker, stack);
	clear_mutexes(philo, stack);
}

void	stack_init(t_data *stack)
{
	stack->philo_total = 0;
	stack->time_till_death = 0;
	stack->time_to_eat = 0;
	stack->time_to_sleep = 0;
	stack->nbr_of_meals = 0;
	stack->fork = 0;
	stack->full = 0;
	stack->is_dead = 0;
	stack->start_time = 0;
}

void	philo_init(t_data *stack)
{
	int i;

	i = 0;
	while (i < stack->philo_total)
	{
		stack->philo[i].id = i + 1;
		stack->philo[i].left_fork = i;
		stack->philo[i].right_fork = (i + 1) % stack->philo_total;
		stack->philo[i].last_meal = 0;
		stack->philo[i].meal_count = 0;
		stack->philo[i].stack = stack;
		pthread_mutex_init(&stack->fork[i], NULL);
		//inicializa os mutexes com os atibutos padrão. o mutex agora está inicializado e destravado.
		i++;
	}
	pthread_mutex_init(&stack->finish, NULL);
	//inicializa o mutex finish_philo com os atributos padrão, destravando-o.
	philo_create(stack);
}
