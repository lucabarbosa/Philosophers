/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:19:48 by lbento            #+#    #+#             */
/*   Updated: 2025/12/03 20:33:43 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void);
int		is_num(char *str);
void	argument_error(int each);
int		ft_atoi(const char *nptr);
void	ft_sleep(long milliseconds);

long	get_time(void)
{
	long				time;
	struct timeval		current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_sleep(long milliseconds)
{
	long	starting_time;

	starting_time = get_time();
	while ((get_time() - starting_time) < milliseconds)
		usleep(100);
}

void	argument_error(int each)
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
		printf("Error: The times the phylos eat needs to be at least 1.\n");
	else if (each == 7)
		printf("Error: Mutex initialization failed.\n");
	else if (each == 8)
		printf("Error: gettimeofday() can't take the time of the system.\n");
	else if (each == 9)
		printf("Error: pthread_create can't creat a thread.\n");
	exit (1);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	total;
	int	signal;

	total = 0;
	i = 0;
	signal = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signal *= -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		total = (nptr[i] - '0') + (total * 10);
		i++;
	}
	return (total * signal);
}
