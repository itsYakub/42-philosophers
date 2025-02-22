/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:43:50 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/22 12:11:32 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if ((ac == 5 || ac == 6) && philo_atoi(av[1]))
	{
		if (!philo_parse(&table, av))
			return (write(2, "Error\n", 6));
		philo_init_table(&table);
		philo_start(&table);
		philo_free(&table);
		return (0);
	}
	return (write(2, "Error\n", 6));
}

void	*philo(void *dat)
{
	t_philo	*_philo;
	t_table	*_table;

	_philo = (t_philo *) dat;
	_table = _philo->table;
	while (!philo_isready(_table))
		;
	if (_philo->id % 2)
		usleep(2000);
	while (1)
	{
		philo_pickup(_philo);
		philo_eat(_philo);
		philo_putdown(_philo);
		philo_sleep(_philo);
		philo_think(_philo);
		if (philo_isfin(_table))
			break ;
	}
	return (NULL);
}

void	*philo_monitor(void *dat)
{
	t_table	*_tab;
	int		_tim;
	int		i;

	_tab = (t_table *) dat;
	while (!philo_isready(_tab))
		;
	while (!philo_isfin(_tab))
	{
		i = -1;
		while (++i < _tab->s_sett.nop)
		{
			_tim = philo_gettime() - philo_eatlast(&_tab->philos[i]);
			if (_tim >= _tab->s_sett.ttd)
			{
				philo_print(_tab, i + 1, "died");
				philo_finish(_tab);
				break ;
			}
			_tab->s_lck.fin = philo_isfull(_tab);
		}
	}
	return (NULL);
}

int	philo_free(t_table *table)
{
	size_t	_iter;

	_iter = -1;
	while (++_iter < (size_t) table->s_sett.nop)
	{
		pthread_join(table->philos[_iter].tid, NULL);
		pthread_mutex_destroy(&table->frk[_iter]);
	}
	pthread_mutex_lock(&table->s_lck.mlock);
	pthread_mutex_destroy(&table->s_lck.mlock);
	pthread_mutex_lock(&table->s_lck.elock);
	pthread_mutex_destroy(&table->s_lck.elock);
	free(table->frk);
	free(table->philos);
	return (1);
}
