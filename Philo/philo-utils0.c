/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-utils0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 07:43:24 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/22 12:32:20 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

int	philo_atoi(const char *str)
{
	int	_nbr;
	int	_sgn;

	_nbr = 0;
	_sgn = 1;
	while ((*str >= 7 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			_sgn = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		_nbr *= 10;
		_nbr += (*str++ - '0') * _sgn;
	}
	if (*str && !(*str >= '0' && *str <= '9'))
		exit(write(2, "Error\n", 6));
	return (_nbr);
}

size_t	philo_print(t_table *table, int id, const char *str)
{
	size_t	_bytes;
	long	_tim;

	if (philo_isfin(table))
		return (0);
	pthread_mutex_lock(&table->s_lck.mlock);
	_tim = philo_gettime() - table->inittime;
	_bytes = printf("%ld %d %s\n", _tim, id, str);
	pthread_mutex_unlock(&table->s_lck.mlock);
	return (_bytes);
}

long	philo_gettime(void)
{
	struct timeval	_timeval;

	if (gettimeofday(&_timeval, NULL) < 0)
		return (0);
	return ((_timeval.tv_sec * 1000) + (_timeval.tv_usec / 1000));
}

int	philo_usleep(long usec)
{
	long	_ms;

	_ms = philo_gettime();
	while ((philo_gettime() - _ms) < usec)
		;
	return (1);
}

int	philo_isready(t_table *table)
{
	int	val;

	pthread_mutex_lock(&table->s_lck.mlock);
	val = table->s_lck.strt;
	pthread_mutex_unlock(&table->s_lck.mlock);
	return (val);
}
