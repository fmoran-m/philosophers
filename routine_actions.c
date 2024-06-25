/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:54:10 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/25 20:55:41 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *pointer)
{
	print_on_thread(pointer->index, "is thinking", pointer);
	if (pointer->n_philo % 2 != 0)
		usleep((pointer->time_sleep / 10) * 1000);
}

void	eat(t_philo *pointer)
{
	if (pointer->index % 2 == 0)
		pthread_mutex_lock(&pointer->fork);
	else
		pthread_mutex_lock(&pointer->next->fork);
	print_on_thread(pointer->index, "has taken a fork", pointer);
	if (pointer->index % 2 == 0)
		pthread_mutex_lock(&pointer->next->fork);
	else
		pthread_mutex_lock(&pointer->fork);
	print_on_thread(pointer->index, "has taken a fork", pointer);
	print_on_thread(pointer->index, "is eating", pointer);
	pthread_mutex_lock(pointer->time_mutex);
	pointer->ref_time = get_current_time();
	if (*pointer->must_eat != -1)
		pointer->n_eat++;
	pthread_mutex_unlock(pointer->time_mutex);
	usleep(pointer->time_eat * 1000);
	pthread_mutex_unlock(&pointer->fork);
	pthread_mutex_unlock(&pointer->next->fork);
}

void	eat_one(t_philo *pointer)
{
	pthread_mutex_lock(&pointer->fork);
	print_on_thread(pointer->index, "has taken a fork", pointer);
	usleep((pointer->time_sleep * 1000));
	pthread_mutex_unlock(&pointer->fork);
}

void	philo_sleep(t_philo *pointer)
{
	print_on_thread(pointer->index, "is sleeping", pointer);
	usleep(pointer->time_sleep * 1000);
}