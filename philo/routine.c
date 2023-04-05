//insert header

#include "philosophers.h"

void	put_philo_to_sleep(t_philo *philo, unsigned long time_to_sleep)
{
	unsigned long time_now;

	time_now = get_time();
	while ((get_time() - time_now) < time_to_sleep)
	{
		if (philo->stack->is_dead == 1)
			break;
		usleep(100);
	}
}

void	feed_philo(t_philo *philo, t_data *stack)
{
	pthread_mutex_lock(&philo->stack->fork[philo->left_fork]);
	put_message(philo, time_now(stack), philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->stack->fork[philo->right_fork]);
	put_message(philo, time_now(stack), philo->id, "has taken a fork");
	put_message(philo, time_now(stack), philo->id, "is eating");
	pthread_mutex_lock(&philo->stack->finish);
	philo->last_meal = time_now(stack);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->stack->finish);
	put_philo_to_sleep(philo, stack->time_to_sleep);
	pthread_mutex_unlock(&philo->stack->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->stack->fork[philo->right_fork]);
}

void	*start_routine(void *philosopher)
{
	t_philo	*philo;
	t_data	*stack;

	philo = (t_philo *)philosopher;
	stack = (philo->stack);
	if (philo->id % 2 == 0)
		usleep(stack->time_to_eat * 1000);
	if (stack->philo_total == 1)
	{
		put_message(philo, time_now(stack), philo->id, "has taken a fork");
		pthread_mutex_unlock(&philo->stack->finish);
		usleep(stack->time_till_death * 1000);
		put_message(philo, time_now(stack), philo->id, "is dead");
	}
	while (stack->philo_total > 1 && !(check_vitals(philo, stack)))
	{
		if (stack->is_dead == 0)
			feed_philo(philo, stack);
		put_message(philo, time_now(stack), philo->id, "is sleeping");
		put_philo_to_sleep(philo, stack->time_to_sleep);
		put_message(philo, time_now(stack), philo->id, "is thinking");
	}
	return (NULL);
}
