//add header

#include "philosophers.h"

int	check_vitals(t_philo *philo, t_data *stack)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo->stack->finish);
	if (philo->stack->is_dead == 1)
	{
		result = 1;
		return (result);
	}
	else if (stack->nbr_of_meals == philo->meal_count)
		stack->full++;
	pthread_mutex_unlock(&philo->stack->finish);
	return (result);
}

unsigned long	time_now(t_data *stack)
{
	unsigned long result;

	result = (get_time() - stack->start_time);
	return (result);
}

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	value;

	gettimeofday(&time, NULL);
	value = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	//segundos para milisegundos + microsegundos para milisegundos.
	return(value);
}

void	*checker(void *philo)
{
	int		i;
	t_data	*stack;

	i = 0;
	stack = (t_data *)philo;
	while (i < stack->philo_total)
	{
		if (stack->full == stack->philo_total)
		{
			pthread_mutex_lock(&stack->finish);
			printf("all philosophers are full");
			stack->is_dead = 1;
			pthread_mutex_unlock(&stack->finish);
			break;
		}
		if (((get_time() - stack->start_time) - stack->philo[i].last_meal) >= (unsigned long) stack->time_till_death)
		{
			printf("%lu philosopher %d died.\n", (get_time() - stack->start_time), i + 1);
			pthread_mutex_lock(&stack->finish);
			stack->is_dead = 1;
			pthread_mutex_unlock(&stack->finish);
			break;
		}
		i++;
	}
	return(NULL);
}
