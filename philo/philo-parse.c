/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:21:07 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/22 12:34:40 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (table->s_sett.nop && table->s_sett.ttd && table->s_sett.tte
		&& table->s_sett.tts && ((table->s_sett.notepme != -1
				&& table->s_sett.notepme) || table->s_sett.notepme == -1));
}

int	philo_init_table(t_table *table)
{
	size_t	_iter;

	table->philos = (t_philo *) malloc(table->s_sett.nop * sizeof(t_philo));
	table->frk = (t_mutex *) malloc(table->s_sett.nop * sizeof(t_mutex));
	table->inittime = philo_gettime();
	pthread_mutex_init(&table->s_lck.mlock, NULL);
	pthread_mutex_init(&table->s_lck.elock, NULL);
	_iter = -1;
	while (++_iter)
		pthread_mutex_init(&table->frk[_iter], NULL);
	table->s_lck.fin = 0;
	return (1);
}

int	philo_init_philo(t_table *table, size_t iter)
{
	table->philos[iter].id = iter + 1;
	table->philos[iter].eat_lst = philo_gettime();
	table->philos[iter].eat_count = 0;
	table->philos[iter].table = table;
	table->philos[iter].lfrk = &table->frk[(iter + 1) % table->s_sett.nop];
	table->philos[iter].rfrk = &table->frk[iter % table->s_sett.nop];
	return (1);
}
