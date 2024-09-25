/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcribe <marcribe@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:54:53 by marcribe          #+#    #+#             */
/*   Updated: 2024/09/22 17:52:42 by marcribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	print_status(t_philosopher *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lld %d %s\n", current_time() - philo->data->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->data->num_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000); // Simula o tempo até morrer
		print_status(philo, "died");
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal_time = current_time();
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	*monitor_philosopher(void *arg)
{
	t_philosopher	*philo;
	long long		current;

	philo = (t_philosopher *)arg;
	while (1)
	{
		current = current_time();
		if (current - philo->last_meal_time > philo->data->time_to_die)
		{
			print_status(philo, "died");
			break ;
		}
		usleep(1000);  // Pequena pausa para não sobrecarregar a CPU
	}
	return (NULL);
}
