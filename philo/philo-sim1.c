/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-sim1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:01:06 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/04 14:33:15 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *ph)
{
	philo_pickup(ph);
	philo_print(ph->table, ph->id, "is eating");
	ph->eat_lst = philo_gettime();
	ph->eat_now = 1;
	philo_usleep(ph->table->s_sett.tte);
	ph->eat_now = 0;
	philo_putdown(ph);
	if (ph->table->s_sett.notepme != -1)
		ph->eat_count++;
	return (1);
}

int	philo_sleep(t_philo *ph)
{
	philo_print(ph->table, ph->id, "is sleeping");
	philo_usleep(ph->table->s_sett.tts);
	return (1);
}

int	philo_think(t_philo *ph)
{
	philo_print(ph->table, ph->id, "is thinking");
	return (1);
}

int	philo_pickup(t_philo *ph)
{
	if (ph->id % 2)
	{
		pthread_mutex_lock(ph->lfrk);
		philo_print(ph->table, ph->id, "has taken a fork");
		pthread_mutex_lock(ph->rfrk);
		philo_print(ph->table, ph->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(ph->rfrk);
		philo_print(ph->table, ph->id, "has taken a fork");
		pthread_mutex_lock(ph->lfrk);
		philo_print(ph->table, ph->id, "has taken a fork");
	}
	return (1);
}

int	philo_putdown(t_philo *ph)
{
	pthread_mutex_unlock(ph->lfrk);
	pthread_mutex_unlock(ph->rfrk);
	return (1);
}
