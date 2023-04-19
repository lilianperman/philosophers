//add 42 header

#include "philosophers.h"

void	philo_create(t_data *stack)
{
	int			i;
	int			philo_total;
	t_philo		*philo;
	pthread_t	monitor;

	i = 0;
	philo = stack->philo;
	philo_total = stack->philo_total;
	stack->start_time = get_time();
	while (i < philo_total)
	{
		pthread_create(&(philo[i].thread), NULL, &routine, &philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, &checker, stack);
	i = 0;
	while (i < philo_total)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	clear_mutexes(philo, stack);
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
		i++;
	}
	pthread_mutex_init(&stack->block, NULL);
	philo_create(stack);
}

int	check_vitals(t_philo *philo, t_data *stack)
{
	pthread_mutex_lock(&philo->stack->block);
	if (philo->stack->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->stack->block);
		return (1);
	}
	else if (stack->meals_till_satiation == philo->meal_count)
		stack->is_full++;
	pthread_mutex_unlock(&philo->stack->block);
	return (0);
}

void	*checker(void *stack_struct)
{
	int		i;
	t_data	*stack;

	i = 0;
	stack = (t_data *)stack_struct;
	while (i < stack->philo_total)
	{
		if (stack->is_full == stack->philo_total)
		{
			pthread_mutex_lock(&stack->block);
			printf("all philosophers are full");
			stack->is_dead = 1;
			pthread_mutex_unlock(&stack->block);
			break;
		}
		else if (((get_time() - stack->start_time) - stack->philo[i].last_meal) >= (unsigned long) stack->time_till_starvation)
		{
			printf("%lu philosopher %d died.\n", (time_now(stack)), stack->philo[i].id);
			pthread_mutex_lock(&stack->block);
			stack->is_dead = 1;
			pthread_mutex_unlock(&stack->block);
			break;
		}
		i = (i + 1) % stack->philo_total;
	}
		return (NULL);
}
