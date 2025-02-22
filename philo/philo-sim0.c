/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-sim0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:58:53 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/22 09:52:03 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	philo_start(t_table *table)
{
	int	i;

	i = -1;
	table->inittime = philo_gettime();
	while (++i < table->s_sett.nop)
	{
		philo_init_philo(table, i);
		pthread_create(&table->philos[i].tid, NULL, philo, &table->philos[i]);
		usleep(1000);
	}
	pthread_create(&table->mid, NULL, philo_monitor, table);
	pthread_detach(table->mid);
	return (1);
}
