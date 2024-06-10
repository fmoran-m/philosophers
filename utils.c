/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:45:52 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/10 20:43:26 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	str_is_number(char *str)
{
	int	i;

	i = -1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	control_argv(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 4 || argc > 6)
	{
		ft_putendl_fd("Incorrect number of arguments", STDERR_FILENO);
		exit (0);
	}
	while (argv[i])
	{
		if (!str_is_number(argv[i]) || !*argv[i])
		{
			ft_putendl_fd("Incorrect format", STDERR_FILENO);
			exit (0);
		}
		i++;
	}
}
