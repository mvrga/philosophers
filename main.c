/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcribe <marcribe@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:54:53 by marcribe          #+#    #+#             */
/*   Updated: 2024/09/22 17:51:58 by marcribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosopher	*philosophers;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_data(&data, argc, argv) != 0)
		return (2);
	if (init_philosophers(&data, &philosophers) != 0)
		return (3);
	if (start_simulation(&data, philosophers) != 0)
		return (4);
	free(philosophers);
	free(data.forks);
	return (0);
}
