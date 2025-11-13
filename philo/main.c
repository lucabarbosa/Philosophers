/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:17:49 by lbento            #+#    #+#             */
/*   Updated: 2025/11/13 12:34:01 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	argument_error(int each);
static void	init_struct(t_rules *limits, char **argv, int argc);

int	main(int argc, char **argv)
{
	t_rules		limits;

	if (argc == 1)
		return (0);
	if (argc == 5 || argc == 6)
	{
		init_struct(&limits, argv, argc);
		printf("%i\n", limits.n_philos);
		printf("%i\n", limits.time_to_die);
		printf("%i\n", limits.time_to_eat);
		printf("%i\n", limits.time_to_sleep);
		printf("%i\n", limits.n_philo_eat);
	}
	else
		argument_error(0);
}

static void	init_struct(t_rules *limits, char **argv, int argc)
{
	int i;
	
	i = 0;
	while (i++ < argc - 1)
		if (is_num(argv[i]) == 0)
			argument_error(1);
	limits->n_philos = ft_atoi(argv[1]);
	if (limits->n_philos > 200 || limits->n_philos < 1)
		argument_error(2);
	limits->time_to_die = ft_atoi(argv[2]);
	if (limits->time_to_die < 1)
		argument_error(3);
	limits->time_to_eat = ft_atoi(argv[3]);
	if (limits->time_to_eat < 1)
		argument_error(4);
	limits->time_to_sleep = ft_atoi(argv[4]);
	if (limits->time_to_sleep < 1)
		argument_error(5);
	limits->n_philo_eat = 0;
	if (argc == 5)
		return ;
	limits->n_philo_eat = ft_atoi(argv[5]);
	if (limits->time_to_sleep < 1)
		argument_error(6);
}

static void	argument_error(int each)
{
	if (each == 0)
		printf("Error: Wrong number of arguments.\n");
	else if (each == 1)
		printf("Error: The arguments must be positive integers.\n");
	else if (each == 2)
		printf("Error: The num of philos must be more than 1 and below 200.\n");
	else if (each == 3)
		printf("Error: Time_to_die must be at least 1.\n");
	else if (each == 4)
		printf("Error: Time_to_eat must be at least 1.\n");
	else if (each == 5)
		printf("Error: Time_to_sleep must be at least 1.\n");
	else if (each == 6)
		printf("Error: Number_of_times_each_philosopher_must_eat \
			must be at least 1.\n");
	exit (1);
}


// ./philo_bonus 5 800 200 200 7 // valgrind --tool=helgrind ./philo 2 400 200 200