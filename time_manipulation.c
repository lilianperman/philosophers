/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liperman <liperman@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:59:09 by liperman          #+#    #+#             */
/*   Updated: 2023/05/26 10:19:30 by liperman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_action(t_philo *philo, unsigned long time_to_wait)
{
	unsigned long	action_begin;

	action_begin = get_time();
	while ((get_time() - action_begin) < time_to_wait)
	{
		pthread_mutex_lock(&philo->stack->block);
		if (philo->stack->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->stack->block);
			break ;
		}
		pthread_mutex_unlock(&philo->stack->block);
		usleep(100);
	}
}

unsigned long	time_now(t_data *stack)
{
	unsigned long	result;

	result = (get_time() - stack->start_time);
	return (result);
}

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	value;

	gettimeofday(&time, NULL);
	value = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (value);
}
