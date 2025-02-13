/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:21:07 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/13 12:33:09 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	__philo_init_single(t_table *table, size_t iter);

int	philo_parse(t_table *table, char **av)
{
	table->s_sett.nop = philo_atoi(av[1]);
	if (table->s_sett.nop <= 0)
		return (0);
	table->s_sett.ttd = philo_atoi(av[2]);
	table->s_sett.tte = philo_atoi(av[3]);
	table->s_sett.tts = philo_atoi(av[4]);
	if (av[5])
		table->s_sett.notepme = philo_atoi(av[5]);
	else
		table->s_sett.notepme = -1;
	return (table->s_sett.nop && table->s_sett.ttd
		&& table->s_sett.tte && table->s_sett.tts);
}

int	philo_init(t_table *table)
{
	size_t	_iter;

	table->philos = (t_philo *) malloc(table->s_sett.nop * sizeof(t_philo));
	table->frk = (t_mutex *) malloc(table->s_sett.nop * sizeof(t_mutex));
	pthread_mutex_init(&table->s_locks.mlock, NULL);
	pthread_mutex_init(&table->s_locks.flock, NULL);
	pthread_mutex_init(&table->s_locks.tlock, NULL);
	table->s_locks.fin = 0;
	_iter = -1;
	while (++_iter < (size_t) table->s_sett.nop)
		__philo_init_single(table, _iter);
	return (1);
}

static int	__philo_init_single(t_table *table, size_t iter)
{
	pthread_mutex_init(&table->frk[iter], NULL);
	table->philos[iter].id = iter + 1;
	table->philos[iter].table = table;
	table->philos[iter].lfrk = &table->frk[(iter + 1) % table->s_sett.nop];
	table->philos[iter].rfrk = &table->frk[iter];
	return (1);
}
