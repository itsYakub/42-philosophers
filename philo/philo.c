/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:43:50 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/13 12:54:35 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if ((ac == 5 || ac == 6) && philo_atoi(av[1]))
	{
		if (!philo_parse(&table, av))
			return (printf("Error\n"));
		philo_init(&table);
		philo_start(&table);
		philo_free(&table);
		return (0);
	}
	return (printf("Error\n"));
}

void	*philo(void *dat)
{
	t_philo	*_philo;

	_philo = (t_philo *) dat;
	while (!philo_getbool(_philo->table))
	{
		philo_eat(_philo);
		philo_sleep(_philo);
		philo_think(_philo);
	}
	return (NULL);
}

static int	__philo_geteattim(t_table *t, size_t iter)
{
	int	_tim;

	pthread_mutex_lock(&t->s_locks.tlock);
	_tim = philo_gettime() - t->philos[iter].eat_lst;
	pthread_mutex_unlock(&t->s_locks.tlock);
	return (_tim);
}

void	*philo_monitor(void *dat)
{
	t_table	*_table;
	size_t	_iter;
	int		_tim;

	_table = (t_table *) dat;
	while (!philo_getbool(_table))
	{
		_iter = -1;
		while (++_iter < (size_t) _table->s_sett.nop)
		{
			_tim = __philo_geteattim(_table, _iter);
			if (!_table->philos[_iter].eat_now && _tim > _table->s_sett.ttd)
			{
				philo_print(_table, _table->philos[_iter].id, "died");
				philo_setbool(_table, 1);
			}
			else if (_table->s_sett.notepme != -1
				&& _table->philos[_iter].eat_count >= _table->s_sett.notepme)
				philo_setbool(_table, 1);
		}
		usleep(100);
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
	pthread_mutex_lock(&table->s_locks.mlock);
	pthread_mutex_destroy(&table->s_locks.mlock);
	pthread_mutex_lock(&table->s_locks.flock);
	pthread_mutex_destroy(&table->s_locks.flock);
	pthread_mutex_lock(&table->s_locks.tlock);
	pthread_mutex_destroy(&table->s_locks.tlock);
	free(table->frk);
	free(table->philos);
	return (1);
}
