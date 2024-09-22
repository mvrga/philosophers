/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                            :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: marcribe <marcribe@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:54:53 by marcribe          #+#    #+#             */
/*   Updated: 2024/06/21 16:55:12 by marcribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->num_philosophers = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->num_meals = -1;
	if (argc == 6)
		data->num_meals = atoi(argv[5]);
	if (data->num_philosophers < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| (data->num_meals < 0 && argc == 6))
		return (1);
	data->all_alive = 1;
	if (init_forks(data))
		return (1);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->start_time = current_time();
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philosophers(t_data *data, t_philosopher **philosophers)
{
	int	i;

	*philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (!*philosophers)
		return (1);
	i = 0;
	while (i < data->num_philosophers)
	{
		init_philosopher(data, philosophers, i);
		i++;
	}
	return (0);
}

void	init_philosopher(t_data *data, t_philosopher **philosophers, int i)
{
	(*philosophers)[i].id = i + 1;
	(*philosophers)[i].last_meal_time = current_time();
	(*philosophers)[i].meals_eaten = 0;
	(*philosophers)[i].left_fork = &data->forks[i];
	(*philosophers)[i].right_fork = &data->forks[(i + 1)
		% data->num_philosophers];
	(*philosophers)[i].data = data;
	pthread_create(&(*philosophers)[i].thread, NULL, philosopher_routine,
		&(*philosophers)[i]);
}

void	cleanup(t_data *data, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(philosophers);
}
