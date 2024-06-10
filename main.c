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

void	launch_threads(t_utils *utils)
{
	int		i;
	t_philo	*head;

	i = 1;
	head = utils->philo;
	while (utils->philo)
	{
		if (i % 2 == 0)
			pthread_create(&utils->philo->thread, NULL,
				&eat, &utils->philo->status);
		else
			pthread_create(&utils->philo->thread, NULL,
				&think, &utils->philo->status);
		pthread_join(utils->philo->thread, NULL);
		utils->philo = utils->philo->next;
		i++;
	}
	utils->philo = head;
}

int	main(int argc, char **argv)
{
	t_utils	utils;

	control_argv(argc, argv);
	init_utils(&utils, argc, argv);
	launch_threads(&utils);
	return (0);
}
