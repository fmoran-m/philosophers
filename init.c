/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:38 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/10 21:02:22 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void  link_last_to_first(t_philo *philo)
{
  t_philo *head;

  head = philo;
  while(philo->next != NULL)
    philo = philo->next;
  philo->next = head;
  philo = head;
}

t_philo *init_philo(int n_philo, t_utils *utils)
{
    t_philo *current_philo;
    t_philo *philo;
    int     i;

	i = 1;
	philo = new_philo(i, utils);
	if (!philo)
		return (NULL);
  i++;
	while (i <= n_philo)
	{
    current_philo = new_philo(i, utils);
		if (!current_philo)
			return (NULL);
    philo_add_back(philo, current_philo);
    i++;
	}
  link_last_to_first(philo);
  return (philo);
}

void  init_forks(t_utils *utils)
{
  int i;
  t_philo *list;

  i = 0;
  list = utils->philo;
  pthread_mutex_init(&utils->time_mutex, NULL);
  while (i < utils->n_philo)
  {
    pthread_mutex_init(&list->fork, NULL);
    list->time_mutex = &utils->time_mutex;
    list = list->next;
    i++;
  }
}

void	init_utils(t_utils *utils, int argc, char **argv)
{
	utils->n_philo = ft_atoi(argv[1]);
	utils->time_die = ft_atoi(argv[2]);
	utils->time_eat = ft_atoi(argv[3]);
	utils->time_sleep = ft_atoi(argv[4]);
	utils->must_eat = -1;
	if (argc == 6)
		utils->must_eat = ft_atoi(argv[5]);
  utils->init_time = get_current_time();
	utils->philo = init_philo(utils->n_philo, utils);
  init_forks(utils);
}

