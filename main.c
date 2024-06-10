/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:08:14 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/10 18:48:49 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	str_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	control_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Incorrect number of arguments", STDERR_FILENO);
		exit (1);
	}
	while (argv[i])
	{
		if (!str_is_number(argv[i]) || !*argv[i])
		{
			ft_putendl_fd("Incorrect format", STDERR_FILENO);
			exit (1);
		}
		i++;
	}
}

void	init_params(t_params *params, int argc, char **argv)
{
	params->n_philo = ft_atoi(argv[1]);
	params->time_die = ft_atoi(argv[2]);
	params->time_eat = ft_atoi(argv[3]);
	params->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->must_eat = ft_atoi(argv[5]);
	else
		params->must_eat = -1;
}

void	init_utils(t_utils *utils, int argc, char **argv)
{
	init_params(&utils->params, argc, argv);
}

int main	(int argc, char **argv)
{
	t_utils	utils;

	control_argv(argc, argv);
	init_utils(&utils, argc, argv);
	return (0);
}
