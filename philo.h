/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcribe <marcribe@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:55:18 by marcribe          #+#    #+#             */
/*   Updated: 2024/09/22 16:05:35 by marcribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include	<pthread.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<sys/time.h>

typedef struct s_philosopher
{
	int					id;
	pthread_t			thread;
	long long			ast_meal_time;
	int					meals_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_data		*data;
}t_philosopher;

typedef struct s_data
{
	int				num_philophers;
	int				time_to_die;
	int				time_to_sleep;
	int				num_to_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	long long		start_time;
	int				all_alive;
}t_data;

/* utility and incial functions*/
long long	current_time(void);
void		print_status(t_philosopher *philo, char *status);
void		*philosopher_routine(void *arg);
int			init_data(t_data *data, int argc, char **argv);
int			init_philosophers(t_data *data, t_philosopher *philosophers);
void		cleanup(t_data *data, t_philosopher *philosophers);

#endif
