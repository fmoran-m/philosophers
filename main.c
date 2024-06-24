/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:08:14 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/10 21:02:35 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void  launch_threads(t_utils *utils)
{
  int i;
  t_philo *head;
  i = 0;
  head = utils->philo;
  while(i < utils->n_philo)
  {
    if (utils->philo->index % 2 == 0)
      pthread_create(&utils->philo->thread, NULL, philo_routine, (void *)utils->philo);
    utils->philo = utils->philo->next;
    i++;
  }
  i = 0;
  utils->philo = head;
  usleep(10);
  while(i < utils->n_philo)
  {
    if (utils->philo->index % 2 != 0)
      pthread_create(&utils->philo->thread, NULL, philo_routine, (void *)utils->philo);
    utils->philo = utils->philo->next;
    i++;
  }
  utils->philo = head;
  pthread_create(&utils->monitor, NULL, monitor, (void *)utils);
}

void  join_threads(t_utils *utils)
{
  int i;

  i = 0;
  pthread_join(utils->monitor, NULL);
  while (i < utils->n_philo)
  {
    pthread_join(utils->philo->thread, NULL);
    utils->philo = utils->philo->next;
    i++;
  }
}

void  destroy_mutex(t_utils *utils)
{
  int i;

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

int	main(int argc, char **argv)
{
	t_utils	utils;

	if(!control_argv(argc, argv))
    return (1);
	init_utils(&utils, argc, argv);
  launch_threads(&utils);
  join_threads(&utils);
  destroy_mutex(&utils);
	return (0);
}
