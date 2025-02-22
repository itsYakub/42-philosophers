/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:49:55 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/22 12:17:37 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_isfin(t_table *table)
{
	int	i;

	pthread_mutex_lock(&table->s_lck.mlock);
	i = table->s_lck.fin;
	pthread_mutex_unlock(&table->s_lck.mlock);
	return (i);
}

int	philo_eatcount(t_philo *ph)
{
	int	val;

	pthread_mutex_lock(&ph->table->s_lck.elock);
	val = ph->eat_count;
	pthread_mutex_unlock(&ph->table->s_lck.elock);
	return (val);
}

int	philo_eatlast(t_philo *ph)
{
	int	val;

	pthread_mutex_lock(&ph->table->s_lck.elock);
	val = ph->eat_lst;
	pthread_mutex_unlock(&ph->table->s_lck.elock);
	return (val);
}

int	philo_finish(t_table *table)
{
	pthread_mutex_lock(&table->s_lck.mlock);
	table->s_lck.fin = 1;
	pthread_mutex_unlock(&table->s_lck.mlock);
	return (1);
}

int	philo_isfull(t_table *table)
{
	int	i;

	if (table->s_sett.notepme == -1)
		return (0);
	i = -1;
	while (++i < table->s_sett.nop)
	{
		if (table->philos[i].eat_count < table->s_sett.notepme)
			return (0);
	}
	return (1);
}
