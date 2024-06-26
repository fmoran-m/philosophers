/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:34:53 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/26 14:34:55 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	loop_condition(t_philo *philo)
{
	pthread_mutex_lock(philo->status_mutex);
	if (*philo->stop_exec)
	{
		pthread_mutex_unlock(philo->status_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->status_mutex);
	return (1);
}

void	print_on_thread(int index, char *str, t_philo *pointer)
{
	long int	milisec;

	pthread_mutex_lock(pointer->print_mutex);
	milisec = get_current_time() - pointer->init_time;
	if (loop_condition(pointer))
	{
		ft_putnbr_fd(milisec, 1);
		write(1, " ", 1);
		ft_putnbr_fd(index, 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(pointer->print_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*pointer;

	pointer = (t_philo *)arg;
	if (pointer->index % 2 != 0 && pointer->n_philo > 1)
		think(pointer);
	while (loop_condition(pointer))
	{
		if (pointer->n_philo == 1)
		{
			eat_one(pointer);
			return (NULL);
		}
		else
			eat(pointer);
		philo_sleep(pointer);
		think(pointer);
	}
	return (NULL);
}
