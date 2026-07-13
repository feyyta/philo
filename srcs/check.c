/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:56:48 by mcastrat          #+#    #+#             */
/*   Updated: 2025/05/05 16:58:01 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	isthisdigit(char *av)
{
	int	i;

	i = 0;
	if (!av)
		return (0);
	while (av[i])
	{
		if (av[i] >= '0' && av[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

long long	ft_atoll(const char *av)
{
	int			i;
	int			signe;
	long long	nb;

	nb = 0;
	signe = 1;
	i = 0;
	while ((av[i] == 32) || (av[i] >= 9 && av[i] <= 13))
		i++;
	if (av[i] == '-' || av[i] == '+')
	{
		if (av[i] == '-')
			signe = -1;
		i++;
	}
	while (av[i] >= '0' && av[i] <= '9')
	{
		nb = nb * 10 + (av[i] - 48);
		i++;
	}
	if (av[i] == '\0')
		return (nb * signe);
	else
		return (-1);
}

int	checkarg(char **av)
{
	int			i;
	long long	nb;

	i = 0;
	while (av[++i])
	{
		if (!isthisdigit(av[i]))
			return (0);
		nb = ft_atoll(av[i]);
		if (nb < 0 || nb > INT_MAX || ft_atoll(av[1]) > 200)
			return (0);
		if (nb == 0 && i == 1)
			return (0);
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
