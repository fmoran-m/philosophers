#include "philo.h"

int  loop_condition(t_philo *philo)
{
  pthread_mutex_lock(philo->status_mutex);
  if (*philo->stop_exec)
  {
    pthread_mutex_unlock(philo->status_mutex);
    return(0);
  }
  pthread_mutex_unlock(philo->status_mutex);
  return(1);
}

void  print_on_thread(int index, char *str, t_philo *pointer)
{
  long int milisec;
    
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

void  updt_status(t_utils *utils)
{
  pthread_mutex_lock(&utils->status_mutex);
  utils->stop_exec = 1;
  pthread_mutex_unlock(&utils->status_mutex);
}

int is_dead(t_utils *utils)
{
  long int current_time;
  long int milisec;
  t_philo *philo_list;
  int i;

  i = 0;
  philo_list = utils->philo;
  while(i < philo_list->n_philo)
  {
    current_time = get_current_time();
    milisec = current_time - philo_list->init_time;
    pthread_mutex_lock(philo_list->time_mutex);
    if ((current_time - philo_list->ref_time) >= philo_list->time_die)
    {
      pthread_mutex_unlock(philo_list->time_mutex);
      updt_status(utils);
      printf("%ld %d died\n", milisec, philo_list->index);
      return (1);
    }
    pthread_mutex_unlock(philo_list->time_mutex);
    philo_list = philo_list->next;
    i++;
  }
  return (0);
}

void  *monitor(void *arg)
{
  t_utils *utils;

  utils = (t_utils *)arg;
  while(1)
  {
    if (is_dead(utils))
      break;
  }
  return (NULL);
}

void think(t_philo *pointer)
{
  print_on_thread(pointer->index, "is thinking", pointer);
  if (pointer->n_philo % 2 != 0)
    usleep((pointer->time_sleep / 10) * 1000);
}

void  eat(t_philo *pointer)
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
  pthread_mutex_unlock(pointer->time_mutex);
  usleep(pointer->time_eat * 1000);
  pthread_mutex_unlock(&pointer->fork);
  pthread_mutex_unlock(&pointer->next->fork);
}

void  philo_sleep(t_philo *pointer)
{
  print_on_thread(pointer->index, "is sleeping", pointer);
  usleep(pointer->time_sleep * 1000);
}

void  *philo_routine(void *arg)
{
  t_philo *pointer;

  pointer = (t_philo *)arg;
  if (pointer->index % 2 != 0)
    think(pointer);
  while (loop_condition(pointer))
  {
    eat(pointer);
    philo_sleep(pointer);
    think(pointer);
  }
  return (NULL);
}
