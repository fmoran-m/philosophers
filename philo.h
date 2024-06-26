/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:13:14 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/26 20:46:31 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*time_mutex;
	pthread_mutex_t	*status_mutex;
	pthread_mutex_t	*print_mutex;
	int				index;
	int				n_philo;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	int				n_eat;
	int				*must_eat;
	int				*stop_exec;
	long int		init_time;
	long int		ref_time;
	struct s_philo	*next;
}					t_philo;
typedef struct s_utils
{
	int				n_philo;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	int				must_eat;
	int				stop_exec;
	long int		init_time;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
}					t_utils;
int					init_utils(t_utils *utils, int argc, char **argv);
int					control_argv(int argc, char **argv);
t_philo				*new_philo(int index, t_utils *utils);
void				philo_add_back(t_philo *philo, t_philo *new_philo);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
void				ft_putendl_fd(char *s, int fd);
int					ft_strlen(char *str);
void				*philo_routine(void *utils);
int					start_threads(t_utils *utils);
void				think(t_philo *pointer);
void				eat(t_philo *pointer);
void				eat_one(t_philo *pointer);
void				philo_sleep(t_philo *pointer);
long int			get_current_time(void);
void				*monitor(void *philo_list);
void				ft_putnbr_fd(long int n, int fd);
void				free_resources(t_utils *utils);
int					init_forks(t_utils *utils);
void				*monitor(void *arg);
void				print_on_thread(int index, char *str, t_philo *pointer);
#endif
