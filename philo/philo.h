/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:25:18 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/22 12:12:04 by joleksia         ###   ########.fr       */
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
		t_mutex	elock;
		int		strt;
		int		fin;
	}			s_lck;
	long		inittime;
	t_philo		*philos;
	t_mutex		*frk;
	t_thread	mid;
}	t_table;

/* ./philo/philo.c */
void	*philo(void *dat);
void	*philo_monitor(void *dat);
int		philo_free(t_table *table);

/* ./phlo/philo-parse.c */
int		philo_parse(t_table *table, char **av);
int		philo_init_table(t_table *table);
int		philo_init_philo(t_table *table, size_t iter);

/* ./philo/philo-sim0.c ./philo/philo-sim1.c */
int		philo_eat(t_philo *ph);
int		philo_sleep(t_philo *ph);
int		philo_think(t_philo *ph);
int		philo_pickup(t_philo *ph);
int		philo_putdown(t_philo *ph);
int		philo_start(t_table *table);
void	*philo_solo(void *dat);

/* ./philo/philo-utils0.c */
int		philo_atoi(const char *str);
size_t	philo_print(t_table *table, int id, const char *str);
long	philo_gettime(void);
int		philo_usleep(long usec);
int		philo_isfin(t_table *table);
int		philo_eatcount(t_philo *ph);
int		philo_eatlast(t_philo *ph);
int		philo_finish(t_table *table);
int		philo_isfull(t_table *table);
int		philo_isready(t_table *table);

#endif
