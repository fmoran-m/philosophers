/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:08:14 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/25 20:14:06 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_utils *utils)
{
	int	i;

	i = 0;
	while (i < utils->n_philo)
	{
		pthread_join(utils->philo->thread, NULL);
		utils->philo = utils->philo->next;
		i++;
	}
}

static void	destroy_mutex(t_utils *utils)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&utils->time_mutex);
	pthread_mutex_destroy(&utils->status_mutex);
	pthread_mutex_destroy(&utils->print_mutex);
	while (i < utils->n_philo)
	{
		pthread_mutex_destroy(&utils->philo->fork);
		utils->philo = utils->philo->next;
		i++;
	}
}

void	free_resources(t_utils *utils)
{
	t_philo	*temp;
	int		i;

	i = 0;
	while (i < utils->n_philo)
	{
		temp = utils->philo;
		utils->philo = utils->philo->next;
		free(temp);
		temp = NULL;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_utils	utils;

	if (!control_argv(argc, argv))
		return (1);
	if (!init_utils(&utils, argc, argv))
		return (1);
	if (utils.n_philo == 1)
	{
		if (pthread_create(&utils.philo->thread, NULL, philo_routine,
			(void *)utils.philo) != 0)
			return(destroy_mutex(&utils), free_resources(&utils), 1);
	}
	else
	{
		if (!start_threads(&utils))
			return(destroy_mutex(&utils), free_resources(&utils), 1);
	}
	monitor(&utils);
	join_threads(&utils);
	destroy_mutex(&utils);
	free_resources(&utils);
	return (0);
}
