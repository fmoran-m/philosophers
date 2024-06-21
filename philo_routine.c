#include "philo.h"

int  loop_condition(t_philo *philo)
{
  pthread_mutex_lock(philo->exec_mutex);
  if (*philo->stop_exec)
  {
    pthread_mutex_unlock(philo->exec_mutex);
    return(0);
  }
  pthread_mutex_unlock(philo->exec_mutex);
  return(1);
}

void  print_on_thread(int long milisec, int index, char *str, t_philo *pointer)
{
  if (loop_condition(pointer))
    printf("%ld %d %s\n", milisec, index, str);
}

void  updt_status(t_utils *utils)
{
  pthread_mutex_lock(&utils->exec_mutex);
  utils->stop_exec = 1;
  pthread_mutex_unlock(&utils->exec_mutex);
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
      updt_status(utils);
      printf("%ld %d has died\n", milisec, philo_list->index);
      pthread_mutex_unlock(philo_list->time_mutex);
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
  long int  time;
  long int  milisec;

  time = get_current_time();
  milisec = time - pointer->init_time;
  print_on_thread(milisec, pointer->index, "is thinking", pointer);
  if (pointer->n_philo % 2 != 0)
    usleep((pointer->time_sleep / 3) * 1000);
}

void  eat(t_philo *pointer)
{
  long int  time;
  long int  milisec;

  if (pointer->index % 2 == 0)
    pthread_mutex_lock(&pointer->fork);
  else
    pthread_mutex_lock(&pointer->next->fork);
  time = get_current_time();
  milisec = time - pointer->init_time;
  print_on_thread(milisec, pointer->index, "has taken a fork", pointer);
  if (pointer->index % 2 == 0)
    pthread_mutex_lock(&pointer->next->fork);
  else
    pthread_mutex_lock(&pointer->fork);
  time = get_current_time();
  milisec = time - pointer->init_time;
  print_on_thread(milisec, pointer->index, "has taken a fork", pointer);
  time = get_current_time();
  milisec = time - pointer->init_time;
  print_on_thread(milisec, pointer->index, "is eating", pointer);
  pthread_mutex_lock(pointer->time_mutex);
  pointer->ref_time = time;
  pthread_mutex_unlock(pointer->time_mutex);
  usleep(pointer->time_eat * 1000);
  pthread_mutex_unlock(&pointer->fork);
  pthread_mutex_unlock(&pointer->next->fork);
}

void  philo_sleep(t_philo *pointer)
{
  long int  time;
  long int  milisec;

  time = get_current_time();
  milisec = time - pointer->init_time;
  print_on_thread(milisec, pointer->index, "is sleeping", pointer);
  usleep(pointer->time_sleep * 1000);
}

void  *philo_odd_routine(void *arg)
{
  t_philo *pointer;

  pointer = (t_philo *)arg;
  while (loop_condition(pointer))
  {
    think(pointer);
    eat(pointer);
    philo_sleep(pointer);
  }
  return (NULL);
}

void  *philo_routine(void *arg)
{
  t_philo *pointer;

  pointer = (t_philo *)arg;
  while (loop_condition(pointer))
  {
    eat(pointer);
    philo_sleep(pointer);
    think(pointer);
  }
  return (NULL);
}
