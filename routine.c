/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liperman <liperman@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:58:56 by liperman          #+#    #+#             */
/*   Updated: 2023/05/26 10:42:57 by liperman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*feed_philo(t_philo *philo, t_data *stack)
{
	if (!(pthread_mutex_lock(&stack->fork[philo->left_fork])))
	{
		put_message(philo, time_now(stack), philo->id, "has taken a fork");
		if (!(pthread_mutex_lock(&stack->fork[philo->right_fork])))
		{
			put_message(philo, time_now(stack), philo->id, "has taken a fork");
			put_message(philo, time_now(stack), philo->id, "is eating");
			pthread_mutex_lock(&philo->stack->block);
			philo[stack->philo->id -1].last_meal = time_now(stack);
			philo->meal_count++;
			pthread_mutex_unlock(&philo->stack->block);
			wait_action(philo, stack->time_to_eat);
			pthread_mutex_unlock(&stack->fork[philo->right_fork]);
		}
		pthread_mutex_unlock(&stack->fork[philo->left_fork]);
	}
	return (NULL);
}

void	*routine(void *philosopher)
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
		pthread_mutex_unlock(&philo->stack->block);
		usleep(stack->time_till_starvation * 1000);
		put_message(philo, time_now(stack), philo->id, "is dead");
	}
	while (stack->philo_total > 1)
	{
		if (check_vitals(philo, stack))
			break ;
		if (stack->is_dead == 0)
			feed_philo(philo, stack);
		put_message(philo, time_now(stack), philo->id, "is sleeping");
		wait_action(philo, stack->time_to_sleep);
		put_message(philo, time_now(stack), philo->id, "is thinking");
	}
	return (NULL);
}
