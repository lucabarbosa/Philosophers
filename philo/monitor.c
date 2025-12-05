/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:09:22 by lbento            #+#    #+#             */
/*   Updated: 2025/12/05 19:41:46 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_rules *data);
static int	check_meals(t_rules *data);
int			check_end_routine(t_philo *data);

void	*thread_monitor(void *arg)
{
	t_rules	*data;

	data = (t_rules *)arg;
	while (1)
	{
		if (check_death(data) == 1)
			return (NULL);
		if (data->n_philo_eat > 0)
			if (check_meals(data))
				return (NULL);
		ft_wait(1);
	}
	return (NULL);
}

static int	check_death(t_rules *data)
{
	int		i;
	long	real_time;
	long	time_since_last_meal;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->death_lock);
		real_time = get_time();
		time_since_last_meal = real_time - data->philo[i].last_meal_time;
		if (time_since_last_meal >= data->time_to_die)
		{
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_lock);
			pthread_mutex_lock(&data->write_lock);
			printf("%ld %i \033[1;33mdied 💀\n\033[0m",
				get_time() - data->start_time, data->philo[i].id_philo);
			pthread_mutex_unlock(&data->write_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->death_lock);
		i++;
	}
	return (0);
}

static int	check_meals(t_rules *data)
{
	int	i;
	int	all_eaten;

	i = 0;
	all_eaten = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->philo[i].meals_eaten >= data->n_philo_eat)
			all_eaten++;
		pthread_mutex_unlock(&data->death_lock);
		i++;
	}
	if (all_eaten == data->n_philos)
	{
		pthread_mutex_lock(&data->death_lock);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_lock);
		pthread_mutex_lock(&data->write_lock);
		printf("\n\033[1;32m all have eaten ✅\n\033[0m");
		pthread_mutex_unlock(&data->write_lock);
		return (1);
	}
	return (0);
}

int	check_end_routine(t_philo *data)
{
	int	flag;

	pthread_mutex_lock(&data->rules->death_lock);
	flag = data->rules->someone_died;
	pthread_mutex_unlock(&data->rules->death_lock);
	return (flag);
}
