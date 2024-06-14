/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:13:14 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/10 20:46:25 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_params
{
	int n_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int must_eat;
}	t_params;
typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	int				status;
	struct s_philo	*next;
}	t_philo;
typedef struct s_utils
{
	t_params	params;
	t_philo		*philo;
	int			eating;
}	t_utils;
void  	init_utils(t_utils *utils, int argc, char **argv);
t_philo	*init_philo(int n_philo);
void  	init_params(t_params *params, int argc, char **argv);
int	  	str_is_number(char *str);
void  	control_argv(int argc, char **argv);
t_philo	*new_philo(void);
void  	philo_add_back(t_philo *philo, t_philo *new_philo);
void  	*think(void *status);
void	  *eat(void *status);
int     ft_atoi(const char *str);
void	  *ft_calloc(size_t count, size_t size);
void	  ft_putendl_fd(char *s, int fd);
int     ft_strlen(char *str);
#endif
