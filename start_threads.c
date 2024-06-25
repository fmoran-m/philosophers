/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:09:03 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/25 21:12:36 by fmoran-m         ###   ########.fr       */
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

static int	start_even(t_utils *utils)
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
	utils->philo = head;
	return (1);
}

static int	start_odd(t_utils *utils)
{
	int		i;
	t_philo	*head;

	i = 0;
	head = utils->philo;
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

int start_threads(t_utils *utils)
{
	if (!start_even(utils))
		return (0);
	usleep(10);
	if (!start_odd(utils))
		return (0);
    return (1);
}
