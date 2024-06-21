/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:49:44 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/10 20:48:07 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int  get_current_time(void)
{
  struct timeval  time;
  long int        miliseconds;

  gettimeofday(&time, NULL);
  miliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
  return (miliseconds);
}

t_philo	*new_philo(int index, t_utils *utils)
{
	t_philo	*philo;
	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
  philo->stop_exec = &utils->stop_exec;
  philo->index = index;
  philo->time_eat = utils->time_eat;
  philo->time_sleep = utils->time_sleep;
  philo->time_die = utils->time_die;
  philo->must_eat = utils->must_eat;
  philo->n_philo = utils->n_philo;
  philo->init_time = utils->init_time;
  philo->ref_time = utils->init_time;
	philo->next = NULL;
	return (philo);
}

void	philo_add_back(t_philo *philo, t_philo *new_philo)
{
	t_philo	*head;

	head = philo;
	while (philo->next != NULL)
		philo = philo->next;
	philo->next = new_philo;
	philo = head;
}
