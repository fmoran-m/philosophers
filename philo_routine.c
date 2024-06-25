#include "philo.h"

int	loop_condition(t_philo *philo)
{
	pthread_mutex_lock(philo->status_mutex);
	if (*philo->stop_exec)
	{
		pthread_mutex_unlock(philo->status_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->status_mutex);
	return (1);
}

void	print_on_thread(int index, char *str, t_philo *pointer)
{
	long int	milisec;

	pthread_mutex_lock(pointer->print_mutex);
	milisec = get_current_time() - pointer->init_time;
	if (loop_condition(pointer))
	{
		ft_putnbr_fd(milisec, 1);
		write(1, " ", 1);
		ft_putnbr_fd(index, 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(pointer->print_mutex);
}

void	updt_status(t_utils *utils)
{
	pthread_mutex_lock(&utils->status_mutex);
	utils->stop_exec = 1;
	pthread_mutex_unlock(&utils->status_mutex);
}

int	count_meals(t_philo *philo)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < philo->n_philo)
	{
		if (philo->n_eat >= *philo->must_eat && *philo->must_eat != -1)
			counter++;
		philo = philo->next;
		i++;
	}
	if (counter == philo->n_philo)
		return (1);
	else
		return (0);
}

int	check_status(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(philo->time_mutex);
	if (get_current_time() - philo->ref_time >= philo->time_die)
		flag = 1;
	if (count_meals(philo) && *philo->must_eat != -1)
		flag = 2;
	pthread_mutex_unlock(philo->time_mutex);
	return (flag);
}

int	is_dead(t_utils *utils)
{
	long int	milisec;
	t_philo		*philo_list;
	int			flag;
	int			i;

	i = 0;
	philo_list = utils->philo;
	while (i < philo_list->n_philo)
	{
		flag = check_status(philo_list);
		if (flag > 0)
		{
			updt_status(utils);
			milisec = get_current_time() - philo_list->init_time;
			if (flag == 1)
				printf("%ld %d died\n", milisec, philo_list->index);
			return (1);
		}
		philo_list = philo_list->next;
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_utils	*utils;

	utils = (t_utils *)arg;
	while (1)
	{
		if (is_dead(utils))
			break ;
	}
	return (NULL);
}

void	think(t_philo *pointer)
{
	print_on_thread(pointer->index, "is thinking", pointer);
	if (pointer->n_philo % 2 != 0)
		usleep((pointer->time_sleep / 10) * 1000);
}

void	eat(t_philo *pointer)
{
	if (pointer->index % 2 == 0)
		pthread_mutex_lock(&pointer->fork);
	else
		pthread_mutex_lock(&pointer->next->fork);
	print_on_thread(pointer->index, "has taken a fork", pointer);
	if (pointer->index % 2 == 0)
		pthread_mutex_lock(&pointer->next->fork);
	else
		pthread_mutex_lock(&pointer->fork);
	print_on_thread(pointer->index, "has taken a fork", pointer);
	print_on_thread(pointer->index, "is eating", pointer);
	pthread_mutex_lock(pointer->time_mutex);
	pointer->ref_time = get_current_time();
	if (*pointer->must_eat != -1)
		pointer->n_eat++;
	pthread_mutex_unlock(pointer->time_mutex);
	usleep(pointer->time_eat * 1000);
	pthread_mutex_unlock(&pointer->fork);
	pthread_mutex_unlock(&pointer->next->fork);
}

void	eat_one(t_philo *pointer)
{
	pthread_mutex_lock(&pointer->fork);
	print_on_thread(pointer->index, "has taken a fork", pointer);
	usleep((pointer->time_sleep * 1000));
	pthread_mutex_unlock(&pointer->fork);
}

void	philo_sleep(t_philo *pointer)
{
	print_on_thread(pointer->index, "is sleeping", pointer);
	usleep(pointer->time_sleep * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*pointer;

	pointer = (t_philo *)arg;
	if (pointer->index % 2 != 0 && pointer->n_philo > 1)
		think(pointer);
	while (loop_condition(pointer))
	{
		if (pointer->n_philo == 1)
		{
			eat_one(pointer);
			return (NULL);
		}
		else
			eat(pointer);
		philo_sleep(pointer);
		think(pointer);
	}
	return (NULL);
}
