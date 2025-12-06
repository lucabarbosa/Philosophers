/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:47:41 by lbento            #+#    #+#             */
/*   Updated: 2025/12/06 20:07:38 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*only_one(void *arg);
void	join_thread(t_rules *data);
void	create_threads(t_rules *data);
void	destroy_mutex(t_rules *data, int flag);
void	print_status(t_philo *data, char *message);

void	create_threads(t_rules *data)
{
	int	i;
	int	n;

	i = 0;
	if (data->n_philos == 1)
	{
		pthread_create(&data->philo[i].thread,
			NULL, &only_one, &data->philo[0]);
		data->ready = 1;
		return ;
	}
	while (i < data->n_philos)
	{
		n = pthread_create(&data->philo[i].thread,
				NULL, &routine, &data->philo[i]);
		if (n != 0)
		{
			destroy_mutex(data, 1);
			return ;
		}
		i++;
	}
	pthread_mutex_lock(&data->death_lock);
	data->ready = 1;
	pthread_mutex_unlock(&data->death_lock);
}

void	*only_one(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	pthread_mutex_lock(data->left_fork);
	print_status(data, "\033[1;37m has taken a fork 🍴\033[0m");
	ft_wait(data->rules->time_to_die, data);
	pthread_mutex_unlock(data->left_fork);
	return (NULL);
}

void	destroy_mutex(t_rules *data, int flag)
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
	if (flag)
		argument_error(9);
}

void	print_status(t_philo *data, char *message)
{
	long	time_philo;

	pthread_mutex_lock(&data->rules->write_lock);
	pthread_mutex_lock(&data->rules->death_lock);
	if (data->rules->someone_died)
	{
		pthread_mutex_unlock(&data->rules->write_lock);
		pthread_mutex_unlock(&data->rules->death_lock);
		return ;
	}
	pthread_mutex_unlock(&data->rules->death_lock);
	time_philo = get_time() - data->rules->start_time;
	printf("%ld %i %s\n", time_philo, data->id_philo, message);
	pthread_mutex_unlock(&data->rules->write_lock);
}

void	join_thread(t_rules *data)
{
	int	i;

	i = 0;
	if (data->n_philos == 1)
	{
		pthread_join(data->philo[0].thread, NULL);
		return ;
	}
	while (i < data->n_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}
