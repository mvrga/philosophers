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

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}

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
		(*philosophers)[i].left_fork
			= &data->forks[i];
		(*philosophers)[i].right_fork
			= &data->forks[(i + 1) % data->num_philosophers];
		(*philosophers)[i].last_meal_time = data->start_time;
		(*philosophers)[i].meals_eaten = 0;
		(*philosophers)[i].data = data;
		pthread_mutex_init(&(*philosophers)[i].mutex, NULL);
		i++;
	}
	return (0);
}

static void	*monitor_philosopher(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d has taken a fork\n",
			current_time() - philo->data->start_time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d has taken a fork\n",
			current_time() - philo->data->start_time, philo->id);
		printf("%lld %d is eating\n",
			current_time() - philo->data->start_time, philo->id);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("%lld %d is sleeping\n",
			current_time() - philo->data->start_time, philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		printf("%lld %d is thinking\n",
			current_time() - philo->data->start_time, philo->id);
	}
	return (NULL);
}

int	start_simulation(t_data *data, t_philosopher *philosophers)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * data->num_philosophers);
	if (!threads)
		return (1);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_create(&threads[i], NULL,
			monitor_philosopher, &philosophers[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_detach(threads[i]);
		i++;
	}
	free(threads);
	return (0);
}
