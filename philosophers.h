//include header

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_data
{
	int				philo_total;
	int				time_till_starvation;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_till_satiation;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
	int				is_full;
	int				is_dead;
	pthread_mutex_t	block;
	unsigned long	start_time;
}	t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_data		*stack;
	int			meal_count;
	int			left_fork;
	int			right_fork;
	long long	last_meal;
}	t_philo;

//MAIN.c
void	fill_stack(int argc, char **argv);
void	stack_init(t_data *stack);

//UTILS.c:
int	philo_is_digit(int argc, char **argv);
int	philo_atoi(char *str);
int	philo_is_valid(int argc, char **argv);
void	put_message(t_philo *philo, unsigned long time, int id, char *messagem);
void	clear_mutexes(t_philo *philo, t_data *stack);

//BUILD_AND_CHECK.C:
void	philo_init(t_data *stack);
void	philo_create(t_data *stack);
int		check_vitals(t_philo *philo, t_data *stack);
void	*checker(void *stack_struct);

//TIME_MANIPULATION.C:
unsigned long	get_time(void);
unsigned long	time_now(t_data *stack);
void			wait_action(t_philo *philo, unsigned long time_to_wait);

//ROUTINE.C:
void	*routine(void *philosopher);
void	*feed_philo(t_philo *philo, t_data *stack);

#endif
