/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcribe <marcribe@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:23:47 by marcribe          #+#    #+#             */
/*   Updated: 2024/09/22 18:24:37 by marcribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

long long	time_since_last_meal(t_philosopher *philo)
{
	return (current_time() - philo->last_meal_time);
}

static int	check_all_fed(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (data->philosophers[i].meals_eaten < data->num_meals)
			return (0);
		i++;
	}
	return (1);
}

static int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_lock(&data->forks[i]);
		if (time_since_last_meal(&data->philosophers[i]) > data->time_to_die)
		{
			print_status(&data->philosophers[i], "died");
			data->all_alive = 0;
			pthread_mutex_unlock(&data->forks[i]);
			return (1);
		}
		pthread_mutex_unlock(&data->forks[i]);
		i++;
	}
	return (0);
}

void	*monitor_philosophers(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (data->all_alive)
	{
		if (check_death(data))
			return (NULL);
		if (data->num_meals > 0 && check_all_fed(data))
		{
			data->all_alive = 0;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
