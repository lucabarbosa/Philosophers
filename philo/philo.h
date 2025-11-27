/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:06:52 by lbento            #+#    #+#             */
/*   Updated: 2025/11/27 16:32:26 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILOS 200

typedef struct s_philo
{
	struct s_rules	*rules;

	int				id_philo;
	pthread_t		thread;
	int				meals_eaten;
	long			last_meal_time;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_rules
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_philo_eat;

	long			start_time;
	int				someone_died;

	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;

	t_philo			philo[MAX_PHILOS];
}	t_rules;

long	get_time(void);
int		is_num(char *str);
void	routine(void *arg);
void	argument_error(int each);
int		ft_atoi(const char *nptr);
void	ft_sleep(long milliseconds);
void	destroy_mutex(t_rules *data);
int		create_threads(t_rules *data);

#endif