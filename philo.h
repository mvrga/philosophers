/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcribe <marcribe@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:55:18 by marcribe          #+#    #+#             */
/*   Updated: 2024/09/22 20:29:46 by marcribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data {
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		start_time;
	int				num_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
} t_data;

typedef struct s_philosopher {
	int				id;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
} t_philosopher;

int		init_data(t_data *data, int argc, char **argv);
int		init_philosophers(t_data *data, t_philosopher **philosophers);
long long	current_time(void);
void		*philosopher_routine(void *arg);
void		*monitor_philosopher(void *arg);
void		print_status(t_philosopher *philo, char *status);
int		start_simulation(t_data *data, t_philosopher *philosophers);
int		ft_atoi(const char *str);

#endif
