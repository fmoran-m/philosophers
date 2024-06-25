/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:18:38 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/25 20:41:08 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	free_partial_mutex(t_utils *utils, t_philo *philo, int limit)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&utils->time_mutex);
	pthread_mutex_destroy(&utils->status_mutex);
	pthread_mutex_destroy(&utils->print_mutex);
	while(i < limit)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		i++;
	}
	return (0);
}

int	init_forks(t_utils *utils)
{
	int		i;
	t_philo	*head;
	t_philo	*list;

	i = 0;
	head = utils->philo;
	list = utils->philo;
	if (pthread_mutex_init(&utils->time_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&utils->status_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&utils->time_mutex), 0);
	if (pthread_mutex_init(&utils->print_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&utils->time_mutex),
			pthread_mutex_destroy(&utils->status_mutex), 0);
	while (i < utils->n_philo)
	{
		if (pthread_mutex_init(&list->fork, NULL) != 0)
			return (free_partial_mutex(utils, head, i));
	    list->time_mutex = &utils->time_mutex;
		list->status_mutex = &utils->status_mutex;
		list->print_mutex = &utils->print_mutex;
		list = list->next;
		i++;
	}
	return (1);
}
