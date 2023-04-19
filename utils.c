#include "philosophers.h"

int	philo_is_digit(int argc, char **argv)
{
	int	arg;
	int	i;

	arg = 1;
	i = 0;
	while (arg < argc && argv[arg])
	{
		while (argv[arg][i])
		{
			if (argv[arg][i] >= 48 && argv[arg][i] <= 57)
				i++;
			else if (argv[arg][i] && (argv[arg][i] < 48 || argv[arg][i] > 57))
			{
				printf("Error: argument is invalid\n");
				return(1);
			}
		}
		i = 0;
		arg++;
	}
	return (0);
}

int	philo_is_valid(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (philo_atoi(argv[i]) < 1)
		{
			printf("Error: argument is invalid\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int philo_atoi(char *str)
{
	int num;
	int sign;

	num = 0;
	sign = 1;
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
	pthread_mutex_lock(&philo->stack->block);
	if (philo->stack->is_dead == 0)
		printf("%lu %d %s\n", time, id, message);
	pthread_mutex_unlock(&philo->stack->block);
}

void	clear_mutexes(t_philo *philo, t_data *stack)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&(stack->block));
	while (i < stack->philo_total)
	{
		pthread_mutex_destroy(&(stack->fork[i]));
		i++;
	}
	free(philo);
}
