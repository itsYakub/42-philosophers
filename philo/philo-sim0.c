/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-sim0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:58:53 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/13 10:48:06 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_start(t_table *table)
{
	size_t	_iter;

	_iter = -1;
	table->inittime = philo_gettime();
	while (++_iter < (size_t) table->s_sett.nop)
	{
		table->philos[_iter].eat_now = 0;
		table->philos[_iter].eat_count = 0;
		table->philos[_iter].eat_lst = philo_gettime();
		pthread_create(&table->philos[_iter].tid, NULL,
			philo, &table->philos[_iter]);
		usleep(100);
	}
	pthread_create(&table->mid, NULL,
		philo_monitor, table);
	pthread_detach(table->mid);
	return (1);
}
