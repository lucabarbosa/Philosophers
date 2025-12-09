/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:17:49 by lbento            #+#    #+#             */
/*   Updated: 2025/12/08 18:07:30 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_rules *limits);
static void	init_mutexes(t_rules *limits);
static int	n_philo_eat(t_rules *limits, char *argv);
static int	init_struct(t_rules *limits, char **argv, int argc);

int	main(int argc, char **argv)
{
	t_rules		data;

	if (argc == 1)
		return (0);
	if (argc == 5 || argc == 6)
	{
		if (init_struct(&data, argv, argc))
			return (1);
		if (argc == 6)
			if (n_philo_eat(&data, argv[5]))
				return (1);
		init_mutexes(&data);
		init_philos(&data);
		create_threads(&data);
		monitor_routine(&data);
		join_thread(&data);
		destroy_mutex(&data, 0);
		return (0);
	}
	else
		argument_error(0);
}

static int	n_philo_eat(t_rules *limits, char *argv)
{
	limits->n_philo_eat = ft_atoi(argv);
	if (limits->n_philo_eat < 1)
		if (argument_error(6))
			return (1);
	return (0);
}

static int	init_struct(t_rules *limits, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i++ < argc - 1)
		if (is_num(argv[i]) == 0)
			if (argument_error(1))
				return (1);
	limits->n_philos = ft_atoi(argv[1]);
	if (limits->n_philos > 200 || limits->n_philos < 1)
		if (argument_error(2))
			return (1);
	limits->time_to_die = ft_atoi(argv[2]);
	if (limits->time_to_die < 1)
		if (argument_error(3))
			return (1);
	limits->time_to_eat = ft_atoi(argv[3]);
	if (limits->time_to_eat < 1)
		if (argument_error(4))
			return (1);
	limits->time_to_sleep = ft_atoi(argv[4]);
	if (limits->time_to_sleep < 1)
		if (argument_error(5))
			return (1);
	limits->n_philo_eat = 0;
	return (0);
}

static void	init_mutexes(t_rules *limits)
{
	int	i;
	int	return_mut;

	i = 0;
	while (i < limits->n_philos)
	{
		return_mut = pthread_mutex_init(&limits->forks[i], NULL);
		if (return_mut)
			argument_error(7);
		return_mut = pthread_mutex_init(&limits->philo[i].meal_lock, NULL);
		if (return_mut)
			argument_error(7);
		i++;
	}
	return_mut = pthread_mutex_init(&limits->write_lock, NULL);
	if (return_mut)
		argument_error(7);
	return_mut = pthread_mutex_init(&limits->death_lock, NULL);
	if (return_mut)
		argument_error(7);
}

static void	init_philos(t_rules *limit)
{
	int	i;

	i = 0;
	limit->start_time = get_time();
	if (limit->start_time == -1)
		argument_error(8);
	while (i < limit->n_philos)
	{
		limit->philo[i].id_philo = i + 1;
		limit->philo[i].meals_eaten = 0;
		limit->philo[i].last_meal_time = limit->start_time;
		limit->philo[i].left_fork = &limit->forks[i];
		limit->philo[i].right_fork = &limit->forks[(i + 1) % limit->n_philos];
		limit->philo[i].rules = limit;
		i++;
	}
	limit->someone_died = 0;
	limit->ready = 0;
}
