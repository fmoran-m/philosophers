/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:57:10 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/10 21:01:18 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*think(void *status)
{
	*(int *)status = 1;
	printf("is thinking\n");
	return (NULL);
}

void	*eat(void *status)
{
	printf("is eating\n");
	*(int *)status = 2;
	return (NULL);
}
