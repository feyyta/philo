/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:39:38 by mcastrat          #+#    #+#             */
/*   Updated: 2025/05/05 16:58:18 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_err(char *str)
{
	printf("%s\n", str);
	return (NULL);
}

void	freeprog(t_prog *prog)
{
	int	i;

	i = -1;
	if (prog)
	{
		while (++i < prog->philonb)
			pthread_mutex_destroy(&prog->fork[i]);
		pthread_mutex_destroy(&prog->write);
		pthread_mutex_destroy(&prog->stop);
		if (prog->philo)
			free(prog->philo);
		if (prog->philoz)
			free(prog->philoz);
		if (prog->fork)
			free(prog->fork);
	}
}

long long	nowtime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 0)
		return (time.tv_usec / 1000LL + time.tv_sec * 1000LL);
	return (0);
}

void	nehess(t_philo *philo, long long zzz)
{
	long long	start;

	start = nowtime();
	while ((nowtime() - start) < zzz)
	{
		pthread_mutex_lock(&philo->prog->stop);
		if (philo->prog->isdead)
		{
			pthread_mutex_unlock(&philo->prog->stop);
			break ;
		}
		pthread_mutex_unlock(&philo->prog->stop);
		usleep(200);
	}
}
