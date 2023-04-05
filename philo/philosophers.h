//include header

#ifndef PHILOSOPHERS_H
# define PHILOSOFERS_H

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_data
{
	int				philo_total;
	int				time_till_death;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
	int				full;
	int				is_dead;
	pthread_mutex_t	finish;
	unsigned long	start_time;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_data			*stack;
	int				meal_count;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
}	t_philo;


//UTILS:
int	philo_is_digit(int argc, char **argv);
int	philo_is_valid(int argc, char **argv);
int	ft_atoi(char *str);
void	put_message(t_philo *philo, unsigned long time_now, int id, char *message);
void	clear_mutexes(t_philo *philo, t_data *stack);

//PHILO_INIT:
void	stack_init(t_data *stack);
void	philo_init(t_data *stack);
void	philo_create(t_data *stack);

//CHECKER:
int				check_vitals(t_philo *philo, t_data *stack);
unsigned long	get_time(void);
unsigned long	time_now(t_data *stack);
void			*checker(void *philo);

//ROUTINE:
void	put_philo_to_sleep(t_philo *philo, unsigned long time_to_sleep);
void	*start_routine(void *philosopher);
void	feed_philo(t_philo *philo, t_data *stack);

//MAIN:
void	feed_stack(int argc, char **argv);

#endif
