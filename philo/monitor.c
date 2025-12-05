/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbento <lbento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:09:22 by lbento            #+#    #+#             */
/*   Updated: 2025/12/05 13:27:39 by lbento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_monitor(void *arg)
{
	t_rules	*data;

	data = (t_rules *)arg;
	data->someone_died = 0;
	printf("\033[1;33m monitor 💀\033[0m");
	return (NULL);
	
}
