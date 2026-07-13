/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:41:01 by mcastrat          #+#    #+#             */
/*   Updated: 2025/05/05 17:00:50 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*init values , alloc thread and struct
then call init stuff*/
int	inithread(t_prog *prog)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&prog->stop);
	prog->start = nowtime();
	while (++i < prog->philonb)
		prog->philo[i].eatat = prog->start;
	i = -1;
	while (++i < prog->philonb)
	{
		if (pthread_create(&prog->philoz[i], NULL, skills,
				&prog->philo[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(prog->philoz[i], NULL);
			return (0);
		}
	}
	pthread_mutex_unlock(&prog->stop);
	return (1);
}

int	threadtime(t_prog *prog)
{
	int	i;

	i = -1;
	if (!inithread(prog))
	{
		return (0);
	}
	usleep(100);
	bosscheck(prog);
	while (++i < prog->philonb)
	{
		if (pthread_join(prog->philoz[i], NULL) != 0)
			return (0);
	}
	return (1);
}

int	initprog(t_prog *prog, char **av, int ac)
{
	if (!checkarg(av))
		return (0);
	prog->philodone = 0;
	prog->start = 0;
	prog->philo = NULL;
	prog->philonb = ft_atoll(av[1]);
	prog->td = ft_atoll(av[2]);
	prog->te = ft_atoll(av[3]);
	prog->ts = ft_atoll(av[4]);
	if (ac == 6)
		prog->meal = ft_atoll(av[5]);
	else
		prog->meal = -1;
	if (prog->td <= 0 || prog->te <= 0 || prog->ts <= 0)
		return (0);
	if (!alloctime(prog))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_prog	prog;

	memset(&prog, 0, sizeof(prog));
	if (ac < 5 || ac > 6)
		return (ft_err("invalid arg"), 1);
	if (!initprog(&prog, av, ac))
		return (ft_err("err at the prog init"), 1);
	if (!threadtime(&prog))
		return (freeprog(&prog), ft_err("err at the thread creation"), 1);
	freeprog(&prog);
	return (0);
}
