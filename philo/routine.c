/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by lbento            #+#    #+#             */
/*   Updated: 2025/12/06 20:09:57 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eating(t_philo *philo);
static void	ft_sleeping(t_philo *data);
static void	ft_thinking(t_philo *data);
static void	ft_take_a_fork(t_philo *data);

void	*routine(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->rules->death_lock);
		if (data->rules->ready)
		{
			pthread_mutex_unlock(&data->rules->death_lock);
			break ;
		}
		pthread_mutex_unlock(&data->rules->death_lock);
		usleep(100);
	}
	if (data->id_philo % 2 == 0)
		ft_wait(data->rules->time_to_eat * 0.75 + 1, data);
	while (!check_end_routine(data))
	{
		ft_take_a_fork(data);
		ft_eating(data);
		ft_sleeping(data);
		ft_thinking(data);
	}
	return (NULL);
}

static void	ft_take_a_fork(t_philo *data)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = data->left_fork;
	second = data->right_fork;
	if (data->id_philo % 2 == 0)
	{
		first = data->right_fork;
		second = data->left_fork;
	}
	pthread_mutex_lock(first);
	print_status(data, "\033[1;37m has taken a fork \033[0m");
	pthread_mutex_lock(second);
	print_status(data, "\033[1;37m has taken a fork \033[0m");
}

static void	ft_eating(t_philo *data)
{
	pthread_mutex_lock(&data->rules->death_lock);
	data->last_meal_time = get_time();
	pthread_mutex_unlock(&data->rules->death_lock);
	print_status(data, "\033[1;31m is eating 🍝\033[0m");
	ft_wait(data->rules->time_to_eat, data);
	pthread_mutex_lock(&data->rules->death_lock);
	data->meals_eaten++;
	pthread_mutex_unlock(&data->rules->death_lock);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}

static void	ft_sleeping(t_philo *data)
{
	print_status(data, "\033[1;34m is sleeping 😴\033[0m");
	ft_wait(data->rules->time_to_sleep, data);
}

static void	ft_thinking(t_philo *data)
{
	print_status(data, "\033[1;32m is thinking 🧠\033[0m");
}
