/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:38 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/10 21:02:22 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_philo *init_philo(int n_philo)
{
    t_philo *current_philo;
    t_philo *philo;
	int		i;

	i = 1;
	philo = new_philo(); // Al loro si el numero de philos es 0
	if (!philo)
		return (NULL);
	while (i < n_philo)
	{
        current_philo = new_philo();
		if (!current_philo)
			return (NULL);
        philo_add_back(philo, current_philo);
        i++;
	}
    return (philo);
}

void	init_utils(t_utils *utils, int argc, char **argv)
{
	init_params(&utils->params, argc, argv);
	utils->philo = init_philo(utils->params.n_philo);
	if (!utils->philo)
		exit (1);
}