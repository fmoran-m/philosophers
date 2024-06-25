/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:38 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/25 20:23:54 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_list(t_philo *philo)
{
	t_philo	*temp;

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
		i++;
	}
	link_last_to_first(philo);
	return (philo);
}

static int	init_parameters(t_utils *utils, int argc, char **argv)
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
	{
		utils->must_eat = ft_atoi(argv[5]);
		if (utils->must_eat == 0)
			return (0);
	}
	utils->stop_exec = 0;
	utils->init_time = get_current_time();
	return (1);
}

int	init_utils(t_utils *utils, int argc, char **argv)
{
	if (!init_parameters(utils, argc, argv))
		return (0);
	utils->philo = init_philo(utils->n_philo, utils);
	if (!utils->philo)
		return (ft_putendl_fd("Error: Memory allocation", 2), 0);
	init_forks(utils);
	if (!init_forks(utils))
	{
		free_resources(utils);
		return (ft_putendl_fd("Error: Mutex init", 2), 0);
	}
	return (1);
}
