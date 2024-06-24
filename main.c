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
}

void  join_threads(t_utils *utils)
{
  int i;

  i = 0;
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
  if (utils.n_philo <= 0)
  {
    ft_putendl_fd("Error: At least 1 philo needed to start the simulation", 2);
    //LIBERAR LISTAS 
    return (1);
  }
  if (utils.n_philo == 1)
    pthread_create(&utils.philo->thread, NULL, philo_routine, (void *)utils.philo);
  else
    launch_threads(&utils);
  monitor(&utils);
  join_threads(&utils);
  destroy_mutex(&utils);
	return (0);
}
