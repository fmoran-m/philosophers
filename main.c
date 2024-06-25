/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:08:14 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/25 18:41:47 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  join_even_threads(t_philo *philo, int limiter)
{
	int		i;
	t_philo *head;

	i = 0;
	head = philo;
	while (i < limiter && philo->index % 2 == 0)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
	philo = head;
	return (0);
}

static int  join_mid_threads(t_philo *philo, int limiter)
{
	int		i;
	t_philo *head;

	i = 0;
	head = philo;
	while (i < limiter)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
	philo = head;
	return (0);
}

int launch_threads(t_utils *utils)
{
	int		i;
	t_philo	*head;

	i = 0;
	head = utils->philo;
	while (i < utils->n_philo)
	{
		if (utils->philo->index % 2 == 0)
        {
			if (pthread_create(&utils->philo->thread, NULL, philo_routine,
				(void *)utils->philo) != 0)
                return (join_even_threads(head, i));
        }
		utils->philo = utils->philo->next;
		i++;
	}
	i = 0;
	utils->philo = head;
	usleep(10);
	while (i < utils->n_philo)
	{
		if (utils->philo->index % 2 != 0)
		{
			if (pthread_create(&utils->philo->thread, NULL, philo_routine,
				(void *)utils->philo) != 0)
				return (join_mid_threads(head, i));
		}
		utils->philo = utils->philo->next;
		i++;
	}
	utils->philo = head;
    return (1);
}

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

void	destroy_mutex(t_utils *utils)
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
		if (!launch_threads(&utils))
			return(destroy_mutex(&utils), free_resources(&utils), 1);
	}
	monitor(&utils);
	join_threads(&utils);
	destroy_mutex(&utils);
	free_resources(&utils);
	return (0);
}
