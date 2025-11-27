/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:25:45 by lbento            #+#    #+#             */
/*   Updated: 2025/11/27 17:23:13 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void *arg);

void	routine(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	if (data->id_philo % 2 == 0)
		ft_sleep(100);
	while (!data->rules->someone_died)
	{
		pthread_mutex_lock(&data->rules->someone_died);
		if (data->rules->someone_died)
		{
			pthread_mutex_unlock(&data->rules->someone_died);
			break ;
		}
		pthread_mutex_unlock(&data->rules->someone_died);
		ft_take_a_fork(data);
		// ft_eating();
		// ft_sleeping();
		// ft_thinking();
	}
}

static void	ft_take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "\033[1;33m 🍴 has taken a fork\033[0m");
}

void	print_status()
{
	
}
