/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:17:49 by lbento            #+#    #+#             */
/*   Updated: 2025/11/25 11:23:42 by lbento           ###   ########.fr       */
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


	// #include <stdio.h>
	// #include <pthread.h>

	// void* minha_thread(void* arg)
	// {
 	//   int *id;
	//   id = (int *)arg;
 	//   printf("Olá! Eu sou a thread %i\n", *id);
 	//   return NULL;
	// }

	// int main()
	// {
	// 	pthread_t t1;
	// 	pthread_t t2;
	// 	pthread_attr_t attr;
	// 	int id1 = 1;
	// 	int id2 = 2;
	// 	int ret;

	// pthread_attr_init(&attr);
	// ret = pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
	// if (!ret)
	// 	printf("Erro ao setar o thread");
	
	// 	// Criando as threads
	// 	pthread_create(&t1, &attr, minha_thread, &id1); // <-------
	// 	pthread_create(&t2, &attr, minha_thread, &id2);

	// 	// Esperando elas terminarem
	// 	pthread_join(t1, NULL);
	// 	pthread_join(t2, NULL);
	// 	pthread_attr_destroy(&attr);

	// 	printf("Threads finalizadas.\n");
	// 	return 0;
	// }
