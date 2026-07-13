/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 02:22:32 by mcastrat          #+#    #+#             */
/*   Updated: 2025/05/05 17:10:34 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eatall(t_prog *prog, int i)
{
	if (prog->meal != -1 && prog->philo[i].mealnb >= prog->meal
		&& prog->philo[i].done == 0)
	{
		prog->philo[i].done = 1;
		prog->philodone++;
	}
	if (prog->philodone == prog->philonb)
	{
		prog->isdead = DONE;
		pthread_mutex_unlock(&prog->stop);
		return (0);
	}
	return (1);
}

void	bosscheck(t_prog *prog)
{
	int			i;
	long long	time;

	i = 0;
	while (19)
	{
		pthread_mutex_lock(&prog->stop);
		time = nowtime() - prog->philo[i].eatat;
		if (time > prog->td)
		{
			prog->isdead = DEAD;
			pthread_mutex_unlock(&prog->stop);
			msg(&prog->philo[i], "died");
			return ;
		}
		if (!eatall(prog, i))
			break ;
		pthread_mutex_unlock(&prog->stop);
		i = (i + 1) % prog->philonb;
		usleep(100);
	}
	if (prog->isdead == DONE)
		msg(&prog->philo[i], "all good");
}
