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

	i = 0;
  while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
    i++;
  if (str[i] == '+')
    i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
  while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
    i++;
  if (str[i])
    return (0);
	return (1);
}

int control_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		ft_putendl_fd("Error: Incorrect number of arguments", STDERR_FILENO);
    return (0);
	}
	while (i < argc)
	{
		if (!str_is_number(argv[i]) || !*argv[i])
		{
			ft_putendl_fd("Error: Incorrect format", STDERR_FILENO);
      return (0);
		}
		i++;
	}
  return (1);
}
