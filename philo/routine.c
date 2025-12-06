/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:25:45 by lbento            #+#    #+#             */
/*   Updated: 2025/12/05 20:57:47 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*routine(void *arg);
static void	ft_eating(t_philo *philo);
static void	ft_take_a_fork(t_philo *philo);
static void	ft_sleeping(t_philo *data);
static void	ft_thinking(t_philo *data);

void	*routine(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	if (data->id_philo % 2 == 0)
		ft_wait(data->rules->time_to_eat / 2, data);
	while (1)
	{
		if (check_end_routine(data) == 1)
			break ;
		ft_take_a_fork(data);
		ft_eating(data);
		ft_sleeping(data);
		ft_thinking(data);
	}
	return (NULL);
}

static void	ft_take_a_fork(t_philo *data)
{
	if (check_end_routine(data))
		return ;
	pthread_mutex_lock(data->left_fork);
	print_status(data, "\033[1;37m has taken a fork 🍴\033[0m");
	if (check_end_routine(data))
	{
		pthread_mutex_unlock(data->left_fork);
		return ;
	}
	pthread_mutex_lock(data->right_fork);
	print_status(data, "\033[1;37m has taken a fork 🍴\033[0m");
}

static void	ft_eating(t_philo *data)
{
	if (check_end_routine(data))
	{
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		return ;
	}
	print_status(data, "\033[1;31m is eating 🍝\033[0m");
	pthread_mutex_lock(&data->rules->death_lock);
	data->last_meal_time = get_time();
	data->meals_eaten++;
	pthread_mutex_unlock(&data->rules->death_lock);
	ft_wait(data->rules->time_to_eat, data);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}

static void	ft_sleeping(t_philo *data)
{
	if (check_end_routine(data))
		return ;
	print_status(data, "\033[1;34m is sleeping 😴\033[0m");
	ft_wait(data->rules->time_to_sleep, data);
}

static void	ft_thinking(t_philo *data)
{
	if (check_end_routine(data))
		return ;
	print_status(data, "\033[1;32m is thinking 🧐\033[0m");
}
