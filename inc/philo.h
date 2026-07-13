/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:41:41 by mcastrat          #+#    #+#             */
/*   Updated: 2025/05/05 16:56:52 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
// struct

# define DEAD 1
# define DONE 2
# define RUNNING 0

typedef struct s_prog	t_prog;

typedef struct s_philo
{
	int					id;
	int					done;
	long long			eatat;
	int					mealnb;
	pthread_mutex_t		*first;
	pthread_mutex_t		*second;
	t_prog				*prog;

}						t_philo;

typedef struct s_prog
{
	long long			td;
	long long			te;
	long long			ts;
	long long			start;
	int					meal;
	int					isdead;
	long long			philonb;
	long long			philodone;
	pthread_mutex_t		*fork;
	t_philo				*philo;
	pthread_mutex_t		stop;
	pthread_mutex_t		write;
	pthread_t			*philoz;

}						t_prog;

// fctn
void					setfork(t_prog *prog, int a, int b);
int						isthisdigit(char *av);
long long				ft_atoll(const char *av);
int						checkarg(char **av);
void					*ft_err(char *str);
long long				nowtime(void);
void					*skills(void *arg);
void					msg(t_philo *philo, char *str);
void					nehess(t_philo *philo, long long zzz);
void					eat(t_philo *philo);
void					bosscheck(t_prog *prog);
void					freeprog(t_prog *prog);
int						initprog(t_prog *prog, char **av, int ac);
int						initstuff(t_prog *prog);
void					initforks(t_prog *prog);
int						threadtime(t_prog *prog);
int						inithread(t_prog *prog);
int						alloctime(t_prog *prog);
int						soisdead(t_philo *philo);
int						eatall(t_prog *prog, int i);
int						ft_strcmp(const char *s1, const char *s2);

#endif