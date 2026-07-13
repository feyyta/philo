/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:54:26 by mcastrat          #+#    #+#             */
/*   Updated: 2025/05/05 17:12:12 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	alloctime(t_prog *prog)
{
	prog->philoz = malloc(sizeof(pthread_t) * prog->philonb);
	if (!prog->philoz)
		return (0);
	prog->philo = malloc(sizeof(t_philo) * prog->philonb);
	if (!prog->philo)
		return (free(prog->philoz), 0);
	prog->fork = malloc(sizeof(pthread_mutex_t) * prog->philonb);
	if (!prog->fork)
	{
		free(prog->philo);
		free(prog->philoz);
		return (0);
	}
	if (!initstuff(prog))
	{
		free(prog->philo);
		free(prog->philoz);
		free(prog->fork);
		return (0);
	}
	return (1);
}

void	setfork(t_prog *prog, int right, int left)
{
	int	i;

	i = -1;
	if (prog->philonb == 1)
	{
		prog->philo[0].first = &prog->fork[0];
		prog->philo[0].second = NULL;
		return ;
	}
	while (++i < prog->philonb)
	{
		right = i;
		left = (i - 1 + prog->philonb) % prog->philonb;
		if (prog->philo[i].id % 2 == 0)
		{
			prog->philo[i].first = &prog->fork[right];
			prog->philo[i].second = &prog->fork[left];
		}
		else
		{
			prog->philo[i].first = &prog->fork[left];
			prog->philo[i].second = &prog->fork[right];
		}
	}
}

void	initforks(t_prog *prog)
{
	int	i;

	i = -1;
	while (++i < prog->philonb)
	{
		if (pthread_mutex_init(&prog->fork[i], NULL) != 0)
		{
			while (--i < prog->philonb)
				pthread_mutex_destroy(&prog->fork[i]);
			return ;
		}
	}
	setfork(prog, 0, 0);
}

/*inti mutex then set values for each philo
then init forks*/
int	initstuff(t_prog *prog)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&prog->stop, NULL) != 0)
		return (pthread_mutex_destroy(&prog->stop), free(prog), 0);
	if (pthread_mutex_init(&prog->write, NULL) != 0)
		return (pthread_mutex_destroy(&prog->stop),
			pthread_mutex_destroy(&prog->write), free(prog), 0);
	while (++i < prog->philonb)
	{
		prog->philo[i].prog = prog;
		prog->philo[i].id = i + 1;
		prog->philo[i].mealnb = 0;
		prog->philo[i].eatat = 0;
		prog->philo[i].done = 0;
	}
	initforks(prog);
	return (1);
}
