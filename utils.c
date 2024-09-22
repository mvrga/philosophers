/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcribe <marcribe@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:54:53 by marcribe          #+#    #+#             */
/*   Updated: 2024/06/21 16:55:12 by marcribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

long long	current_time(void)
{
	struct timeval	tv;
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
	return (ms);
}

void	print_status(t_philosopher *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->all_alive)
		printf("%lld %d %s\n",
			current_time() - philo->data->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
