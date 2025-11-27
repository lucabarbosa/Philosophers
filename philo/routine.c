/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:25:45 by lbento            #+#    #+#             */
/*   Updated: 2025/11/27 18:21:01 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*routine(void *arg);
static void	ft_take_a_fork(t_philo *philo);
static void	print_status(t_rules *data, char *message);

void	*routine(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	if (data->id_philo % 2 == 0)
		ft_sleep(100);
	while (!data->rules->someone_died)
	{
		pthread_mutex_lock(&data->rules->death_lock);
		if (data->rules->someone_died)
		{
			pthread_mutex_unlock(&data->rules->death_lock);
			break ;
		}
		pthread_mutex_unlock(&data->rules->death_lock);
		ft_take_a_fork(data);
		// ft_eating();
		// ft_sleeping();
		// ft_thinking();
	}
	return (NULL);
}

static void	ft_take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo->rules, "\033[1;33m 🍴 has taken a fork\033[0m");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo->rules, "\033[1;33m 🍴 has taken a fork\033[0m");
}

static void	print_status(t_rules *data, char *message)
{
	long	time_philo;

	pthread_mutex_lock(&data->write_lock);
	pthread_mutex_lock(&data->death_lock);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->write_lock);
		pthread_mutex_unlock(&data->death_lock);
		return ;
	}
	pthread_mutex_unlock(&data->death_lock);
	time_philo = get_time() - data->start_time;
	printf("%ld %i %s\n", time_philo, data->philo->id_philo, message);
	pthread_mutex_unlock(&data->write_lock);
}
