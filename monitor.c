/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:44:21 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/25 20:49:44 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	updt_status(t_utils *utils)
{
	pthread_mutex_lock(&utils->status_mutex);
	utils->stop_exec = 1;
	pthread_mutex_unlock(&utils->status_mutex);
}

static int	count_meals(t_philo *philo)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < philo->n_philo)
	{
		if (philo->n_eat >= *philo->must_eat && *philo->must_eat != -1)
			counter++;
		philo = philo->next;
		i++;
	}
	if (counter == philo->n_philo)
		return (1);
	else
		return (0);
}

static int	check_status(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(philo->time_mutex);
	if (get_current_time() - philo->ref_time >= philo->time_die)
		flag = 1;
	else if (count_meals(philo) && *philo->must_eat != -1)
		flag = 2;
	pthread_mutex_unlock(philo->time_mutex);
	return (flag);
}

static int	is_dead(t_utils *utils)
{
	long int	milisec;
	t_philo		*philo_list;
	int			flag;
	int			i;

	i = 0;
	philo_list = utils->philo;
	while (i < philo_list->n_philo)
	{
		flag = check_status(philo_list);
		if (flag > 0)
		{
			updt_status(utils);
			milisec = get_current_time() - philo_list->init_time;
			if (flag == 1)
				printf("%ld %d died\n", milisec, philo_list->index);
			return (1);
		}
		philo_list = philo_list->next;
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_utils	*utils;

	utils = (t_utils *)arg;
	while (1)
	{
		if (is_dead(utils))
			break ;
	}
	return (NULL);
}
