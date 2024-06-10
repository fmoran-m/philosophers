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

t_philo	*new_philo(void)
{
	t_philo	*philo_list;

	philo_list = ft_calloc(1, sizeof(t_philo));
	if (!philo_list)
		return (NULL);
	philo_list->next = NULL;
	return (philo_list);
}

void	philo_add_back(t_philo *philo_list, t_philo *new_philo)
{
	t_philo	*head;

	head = philo_list;
	while (philo_list->next != NULL)
		philo_list = philo_list->next;
	new_philo = philo_list->next;
	philo_list = head;
}