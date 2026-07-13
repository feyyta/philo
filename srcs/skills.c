/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skills.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:17:28 by mcastrat          #+#    #+#             */
/*   Updated: 2025/05/05 17:04:34 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	msg(t_philo *philo, char *str)
{
	long long	time;
	int			print;

	print = 0;
	pthread_mutex_lock(&philo->prog->stop);
	if (philo->prog->isdead == 0 || ft_strcmp(str, "died") == 0
		|| ft_strcmp(str, "all good") == 0)
		print = 1;
	pthread_mutex_unlock(&philo->prog->stop);
	if (print)
	{
		pthread_mutex_lock(&philo->prog->write);
		time = nowtime() - philo->prog->start;
		printf("%lld %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->prog->write);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first);
	pthread_mutex_lock(philo->second);
	msg(philo, "\033[31m" "has taken the first fork." "\033[0m");
	msg(philo, "\033[31m" "has taken the second fork." "\033[0m");
	pthread_mutex_lock(&philo->prog->stop);
	if (philo->prog->meal != -1 && philo->mealnb >= philo->prog->meal)
	{
		pthread_mutex_unlock(&philo->prog->stop);
		pthread_mutex_unlock(philo->second);
		pthread_mutex_unlock(philo->first);
		return ;
	}
	philo->eatat = nowtime();
	philo->mealnb++;
	pthread_mutex_unlock(&philo->prog->stop);
	msg(philo, "\033[35m""is eating.""\033[0m");
	nehess(philo, philo->prog->te);
	pthread_mutex_unlock(philo->second);
	pthread_mutex_unlock(philo->first);
	return ;
}

int	soisdead(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->stop);
	if (philo->prog->isdead)
	{
		pthread_mutex_unlock(&philo->prog->stop);
		return (0);
	}
	pthread_mutex_unlock(&philo->prog->stop);
	return (1);
}

void	*skills(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->prog->philonb > 1)
	{
		if (philo->id % 2 == 0)
			usleep(100);
		while (19)
		{
			if (!soisdead(philo))
				break ;
			eat(philo);
			msg(philo, "\033[32m" "is sleeping.""\033[0m");
			nehess(philo, philo->prog->ts);
			msg(philo, "\033[33m""is thinking.""\033[0m");
			usleep(100);
		}
	}
	else
	{
		msg(philo, "\033[31m""has taken a fork.""\033[0m");
		nehess(philo, philo->prog->td);
	}
	return (NULL);
}
