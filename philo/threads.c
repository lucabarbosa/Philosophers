/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:47:41 by lbento            #+#    #+#             */
/*   Updated: 2025/11/27 16:32:21 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_rules *data);
int		create_threads(t_rules *data);

int	create_threads(t_rules *data)
{
	int	i;
	int	r;

	i = 0;
	while (i < data->n_philos)
	{
	r = pthread_create(data->philo[i].thread, NULL, &routine, &data->philo[i]);
		if (r != 0)
			return (1);
		i++;
	}
	return (0);
}

void	destroy_mutex(t_rules *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->death_lock);
}
