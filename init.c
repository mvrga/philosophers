/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcribe <marcribe@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:54:53 by marcribe          #+#    #+#             */
/*   Updated: 2024/09/22 17:50:02 by marcribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = current_time();
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL); // Inicializa o mutex para impressão
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
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].left_fork = &data->forks[i];
		(*philosophers)[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
		(*philosophers)[i].last_meal_time = data->start_time;
		(*philosophers)[i].meals_eaten = 0;
		(*philosophers)[i].data = data;
		i++;
	}
	return (0);
}

int	start_simulation(t_data *data, t_philosopher *philosophers)
{
	pthread_t	*threads;
	pthread_t	*monitors;
	int			i;

	threads = malloc(sizeof(pthread_t) * data->num_philosophers);
	monitors = malloc(sizeof(pthread_t) * data->num_philosophers);
	if (!threads || !monitors)
		return (1);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
		pthread_create(&monitors[i], NULL, monitor_philosopher, &philosophers[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(threads[i], NULL);
		pthread_join(monitors[i], NULL);
		i++;
	}
	free(threads);
	free(monitors);
	return (0);
}
