/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:08:14 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/10 18:13:00 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
static void	*thread_function(void * pointer)
{
	printf("%s\n", (char *)pointer);
	return (NULL);
}
*/

static int	str_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	control_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Incorrect number of arguments", STDERR_FILENO);
		exit (1);
	}
	while (argv[i])
	{
		if (!str_is_number(argv[i]) || !*argv[i])
		{
			ft_putendl_fd("Incorrect format", STDERR_FILENO);
			exit (1);
		}
		i++;
	}
}

int main	(int argc, char **argv)
{
//	pthread_t hilo;
//	char	*str;

	control_argv(argc, argv);
/*
	str = "hola";
	if (pthread_create(&hilo, NULL, &thread_function, str) != 0)
	h	exit(1);
	if (pthread_join(hilo, NULL) != 0)
		exit(1);
*/
	return (0);
}
