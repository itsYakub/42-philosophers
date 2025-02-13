/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:25:18 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/13 12:52:41 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			eat_now;
	long		eat_lst;
	long		eat_count;
	t_thread	tid;
	t_mutex		*lfrk;
	t_mutex		*rfrk;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	struct
	{
		int		nop;
		int		ttd;
		int		tte;
		int		tts;
		int		notepme;
	}			s_sett;
	struct
	{
		t_mutex	mlock;
		t_mutex flock;
		t_mutex tlock;
		int		start;
		int		fin;
	}			s_locks;
	long		inittime;
	t_philo		*philos;
	t_mutex		*frk;
	t_thread	mid;
}	t_table;

/* ./philo/philo.c */
int		philo_free(t_table *table);

/* ./phlo/philo-parse.c */
int		philo_parse(t_table *table, char **av);
int		philo_init(t_table *table);

/* ./philo/philo-sim0.c ./philo/philo-sim1.c */
void	*philo(void *dat);
int		philo_eat(t_philo *ph);
int		philo_sleep(t_philo *ph);
int		philo_think(t_philo *ph);
int		philo_pickup(t_philo *ph);
int		philo_putdown(t_philo *ph);
int		philo_start(t_table *table);

/* ./philo/philo-utils0.c */
int		philo_atoi(const char *str);
int		philo_isnumer(const char *str);
size_t	philo_print(t_table *table, int id, const char *str);
long	philo_gettime(void);
int		philo_getbool(t_table *t);
int		philo_setbool(t_table *t, int val);

/* ./philo/philo-monitor.c */
void	*philo_monitor(void *dat);
int		philo_usleep(long usec);

#endif
