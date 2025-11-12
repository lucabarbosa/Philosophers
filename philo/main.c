/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:17:49 by lbento            #+#    #+#             */
/*   Updated: 2025/11/12 20:31:11 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	argument_error(int each);
static void	init_struct(t_rules *limits, char **argv, int argc);

int	main(int argc, char **argv)
{
	t_rules		limits;
	pthread_t	philos;

	if (argc == 1)
		return (0);
	if (argc == 5 || argc == 6)
	{
		init_struct(&limits, argv, argc);
	}
	else
		argument_error(0);
}

static void	init_struct(t_rules *limits, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i <= argc - 1)
	{
		if (is_num(argv[i]) == 0)
			argument_error(1);
		i++;
	}
	limits->n_philos = ft_atoi(argv[1]);
	if (limits->n_philos > 200)
		argument_error(2);
	limits->time_to_die = ft_atoi(argv[2]);
	limits->time_to_eat = ft_atoi(argv[3]);
	limits->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		limits->n_philo_eat = ft_atoi(argv[5]);
	else
		limits->n_philo_eat = 0;
}

static void	argument_error(int each)
{
	if (each == 0)
		printf("Error: Wrong number of arguments!");
	else if (each == 1)
		printf("Error: The arguments must be positive integers!");
	else if (each == 2)
		printf("Error: Too many philosophers, the number must be below 200.");
	exit (1);
}


// ./philo_bonus 5 800 200 200 7 // valgrind --tool=helgrind ./philo 2 400 200 200