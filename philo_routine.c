#include "philo.h"

int is_dead(t_philo *philo_list)
{
  long int current_time;
  long int milisec;
  int i;

  i = 0;
  while(i < philo_list->n_philo)
  {
    current_time = get_current_time();
    milisec = current_time - philo_list->init_time;
    pthread_mutex_lock(philo_list->time_mutex);
    if ((current_time - philo_list->ref_time) > philo_list->time_die)
    {
      printf("%ld %d died\n", milisec, philo_list->index);
      return (1);
    }
    pthread_mutex_unlock(philo_list->time_mutex);
    philo_list = philo_list->next;
    i++;
  }
  return (0);
}

void  updt_status(t_philo *philo_list)
{
  int i;

  i = 0;
  pthread_mutex_lock(philo_list->exec_mutex);
  while(i < philo_list->n_philo)
  {
    philo_list->stop_exec = 1;
    philo_list = philo_list->next;
    i++;
  }
  pthread_mutex_unlock(philo_list->exec_mutex);
}

void  *monitor(void *arg)
{
  t_philo *philo_list;

  philo_list = (t_philo *)arg;
  while(1)
  {
    if (is_dead(philo_list))
    {
      updt_status(philo_list);
      return (NULL);
    }
  }
  return (NULL);
}

void think(t_philo *pointer)
{
  long int  time;
  long int  milisec;

  time = get_current_time();
  milisec = time - pointer->init_time;
  printf("%ld %d is thinking\n", milisec, pointer->index);
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
  pthread_mutex_lock(pointer->exec_mutex);
  if (pointer->stop_exec)
    return ;
  pthread_mutex_unlock(pointer->exec_mutex);
  printf("%ld %d has taken a fork\n", milisec, pointer->index);
  if (pointer->index % 2 == 0)
    pthread_mutex_lock(&pointer->next->fork);
  else
    pthread_mutex_lock(&pointer->fork);
  time = get_current_time();
  milisec = time - pointer->init_time;
  pthread_mutex_lock(pointer->exec_mutex);
  if (pointer->stop_exec)
    return ;
  pthread_mutex_unlock(pointer->exec_mutex);
  printf("%ld %d has taken a fork\n", milisec, pointer->index);
  time = get_current_time();
  milisec = time - pointer->init_time;
  pthread_mutex_lock(pointer->exec_mutex);
  if (pointer->stop_exec)
    return ;
  pthread_mutex_unlock(pointer->exec_mutex);
  printf("%ld %d is eating\n", milisec, pointer->index);
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
  printf("%ld %d is sleeping\n", milisec, pointer->index);
  usleep(pointer->time_sleep * 1000);
}

void  *philo_odd_routine(void *arg)
{
  t_philo *pointer;

  pointer = (t_philo *)arg;
  while (1)
  {
    pthread_mutex_lock(pointer->exec_mutex);
    if (pointer->stop_exec)
      break;
    pthread_mutex_unlock(pointer->exec_mutex);
    think(pointer);
    pthread_mutex_lock(pointer->exec_mutex);
    if (pointer->stop_exec)
      break;
    pthread_mutex_unlock(pointer->exec_mutex);
    eat(pointer);
    pthread_mutex_lock(pointer->exec_mutex);
    if (pointer->stop_exec)
        break;
    pthread_mutex_unlock(pointer->exec_mutex);
    philo_sleep(pointer);
  }
  return (NULL);
}

void  *philo_routine(void *arg)
{
  t_philo *pointer;

  pointer = (t_philo *)arg;
  while (1)
  {
    pthread_mutex_lock(pointer->exec_mutex);
    if (pointer->stop_exec)
      break;
    pthread_mutex_unlock(pointer->exec_mutex);
    eat(pointer);
    pthread_mutex_lock(pointer->exec_mutex);
    if (pointer->stop_exec)
      break;
    pthread_mutex_unlock(pointer->exec_mutex);
    philo_sleep(pointer);
    pthread_mutex_lock(pointer->exec_mutex);
    if (pointer->stop_exec)
      break;
    pthread_mutex_unlock(pointer->exec_mutex);
    think(pointer);
  }
  return (NULL);
}
