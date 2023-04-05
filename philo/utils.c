//add 42 header!

#include "philosophers.h"

int	philo_is_digit(int argc, char **argv)
{
	int	arguments = 1;
	int	i = 0;

	while(arguments < argc && argv[arguments])
	{
		while (argv[arguments][i])
		{
			if (argv[arguments][i] >= 48 && argv[arguments][i] <= 57)
				i++;
			else if (argv[arguments][i] && (argv[arguments][i] < 48 || argv[arguments][i] > 57))
			{
				printf("Error: invalid arguments\n");
				return (1);
			}
		}
		i = 0;
		arguments++;
	}
	return (0);
}

int	philo_is_valid(int argc, char **argv)
{
	int	i = 1;

	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 1)
		{
			printf("Error: invalid arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int num = 0;
	int sign = 1;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - 48;
		str++;
	}
	return (num * sign);
}

void	put_message(t_philo *philo, unsigned long time, int id, char *message)
{
	pthread_mutex_lock(&philo->stack->finish);
	if (philo->stack->is_dead == 0)
		printf("%lu %d %s\n", time, id, message);
	pthread_mutex_unlock(&philo->stack->finish);
}

void	clear_mutexes(t_philo *philo, t_data *stack)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&(stack->finish));
	while (i < stack->philo_total)
	{
		pthread_mutex_destroy(&(stack->fork[i]));
		i++;
	}
	free(philo);
}
