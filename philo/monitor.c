/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by lbento            #+#    #+#             */
/*   Updated: 2025/12/06 19:45:22 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals(t_rules *data);
static int	check_death(t_philo *philo);
void		monitor_routine(t_rules *data);
int			check_end_routine(t_philo *data);

void	monitor_routine(t_rules *data)
{
	int	i;

	while (!data->ready)
		continue ;
	while (!data->someone_died)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (check_death(&data->philo[i]))
				return ;
			i++;
		}
		if (data->n_philo_eat > 0)
			if (check_meals(data))
				return ;
		usleep(1000);
	}
}

static int	check_death(t_philo *philo)
{
	long	real_time;
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->rules->death_lock);
	real_time = get_time();
	time_since_last_meal = real_time - philo->last_meal_time;
	if (time_since_last_meal >= philo->rules->time_to_die)
	{
		philo->rules->someone_died = 1;
		pthread_mutex_unlock(&philo->rules->death_lock);
		pthread_mutex_lock(&philo->rules->write_lock);
		printf("%ld %i \033[1;33m died 💀\n\033[0m",
			get_time() - philo->rules->start_time, philo->id_philo);
		pthread_mutex_unlock(&philo->rules->write_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->death_lock);
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
		printf("\n\033[1;32m All philosophers have eaten %d times ✅\n\033[0m",
			data->n_philo_eat);
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
