/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:06:52 by lbento            #+#    #+#             */
/*   Updated: 2025/11/25 11:25:06 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILOS 200

typedef struct s_rules
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_philo_eat;
}	t_rules;

typedef struct s_philo
{
    int				id_philo;
    int				meals_eaten;
    long			last_meal_time;
    pthread_t		thread;

    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;

    t_rules			*rules;
    pthread_mutex_t	*write_lock;
    pthread_mutex_t	*death_lock;
    int				*someone_died;
}	t_philo;

int	is_num(char *str);
int	ft_atoi(const char *nptr);

#endif