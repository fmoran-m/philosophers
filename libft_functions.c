/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:34:40 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/26 14:34:42 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	acum;
	int	i;
	int	flag;

	acum = 0;
	i = 0;
	flag = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			flag = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		acum = acum * 10 + (str[i] - 48);
		i++;
	}
	if (flag == 1)
		acum = acum * -1;
	return (acum);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;
	size_t	total_amount;

	i = 0;
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	total_amount = size * count;
	ptr = malloc(total_amount);
	if (ptr == 0)
		return (0);
	while (i < total_amount)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
