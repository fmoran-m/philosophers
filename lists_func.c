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
	t_philo	*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
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