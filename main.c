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

int	print_error(char *message)
{
	printf("%s\n", message);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosopher	*philosophers;

	if (argc != 5 && argc != 6)
		return (print_error("Error: Invalid number of arguments"));
	if (init_data(&data, argc, argv))
		return (print_error("Error: Initialization failed"));
	if (init_philosophers(&data, &philosophers))
		return (print_error("Error: Philosopher initialization failed"));
	if (start_simulation(&data, philosophers))
		return (print_error("Error: Simulation failed"));
	free(philosophers);
	free(data.forks);
	return (0);
}
