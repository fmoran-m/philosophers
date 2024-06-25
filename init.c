/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:38 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/25 16:49:12 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void free_list(t_philo *philo)
{
    t_philo *temp;

    while (philo)
    {
        temp = philo;
        philo = philo->next;
        free(temp);
    }
}

void	link_last_to_first(t_philo *philo)
{
	t_philo	*head;

	head = philo;
	while (philo->next != NULL)
		philo = philo->next;
	philo->next = head;
	philo = head;
}

t_philo	*init_philo(int n_philo, t_utils *utils)
{
	t_philo	*current_philo;
	t_philo	*philo;
	int		i;

	i = 1;
	philo = new_philo(i, utils);
	if (!philo)
		return (NULL);
	i++;
	while (i <= n_philo)
	{
		current_philo = new_philo(i, utils);
		if (!current_philo)
        {
            free_list(philo);
			return (NULL);
        }
		philo_add_back(philo, current_philo);
		i++;;
	}
	link_last_to_first(philo);
	return (philo);
}

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

int	init_utils(t_utils *utils, int argc, char **argv)
{
	utils->n_philo = ft_atoi(argv[1]);
   	if (utils->n_philo <= 0)
	{
		ft_putendl_fd("Error: At least 1 philo needed to start the simulation",
			2);
		return (0);
	}
	utils->time_die = ft_atoi(argv[2]);
	utils->time_eat = ft_atoi(argv[3]);
	utils->time_sleep = ft_atoi(argv[4]);
	utils->must_eat = -1;
	if (argc == 6)
		utils->must_eat = ft_atoi(argv[5]);
	utils->stop_exec = 0;
	utils->init_time = get_current_time();
	utils->philo = init_philo(utils->n_philo, utils);
	if (!utils->philo)
		return(ft_putendl_fd("Error: Memory allocation", 2), 0);
	init_forks(utils);
	if (!init_forks(utils))
	{
		free_resources(utils);
		return(ft_putendl_fd("Error: Mutex init", 2), 0);
	}
    return (1);
}
