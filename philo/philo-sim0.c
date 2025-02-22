/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-sim0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:58:53 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/22 12:33:52 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*philo_solo(void *dat)
{
	t_philo	*_philo;

	_philo = (t_philo *) dat;
	_philo->table->inittime = philo_gettime();
	philo_print(_philo->table, 1, "has taken a fork");
	philo_usleep(_philo->table->s_sett.ttd);
	philo_print(_philo->table, 1, "died");
	return (NULL);
}

int	philo_start(t_table *table)
{
	int	i;

	i = -1;
	table->s_lck.strt = 0;
	table->inittime = philo_gettime();
	while (++i < table->s_sett.nop)
	{
		philo_init_philo(table, i);
		if (table->s_sett.nop == 1)
			return (pthread_create(&table->philos[i].tid, NULL,
					philo_solo, &table->philos[i]));
		pthread_create(&table->philos[i].tid, NULL, philo, &table->philos[i]);
	}
	pthread_create(&table->mid, NULL, philo_monitor, table);
	pthread_detach(table->mid);
	table->s_lck.strt = 1;
	return (1);
}
