/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by lbento            #+#    #+#             */
/*   Updated: 2025/12/07 16:09:43 by lbento           ###   ########.fr       */
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
	if (data->id_philo % 2 == 0)
		ft_wait(1, data);
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
	pthread_mutex_lock(&data->meal_lock);
	data->last_meal_time = get_time();
	data->meals_eaten++;
	pthread_mutex_unlock(&data->meal_lock);
	print_status(data, "\033[1;31m is eating 🍝\033[0m");
	ft_wait(data->rules->time_to_eat, data);
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
	time_t	time_since_last_eat;
	time_t	time_to_die;
	time_t	think_time;


	pthread_mutex_lock(&data->meal_lock);
	time_since_last_eat = get_time() - data->last_meal_time;
	pthread_mutex_unlock(&data->meal_lock);
	time_to_die = data->rules->time_to_die - time_since_last_eat;
	think_time = (time_to_die - data->rules->time_to_eat) / 2;
	if (think_time < 0)
		think_time = 0;
	if (think_time > 600)
		think_time = 200;
	print_status(data, "\033[1;32m is thinking 🧠\033[0m");
	ft_wait(think_time, data);
}
