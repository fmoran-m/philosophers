#include "philo.h"

void  *is_dead(void *arg)
{
  long int time_to_dead;
  long int current_time;
  long int milisec;
  t_philo *philo_list;
  int i;

  philo_list = (t_philo *)arg;
  time_to_dead = philo_list->time_die;
  while (1)
  {
    i = 0;
    while(i <= philo_list->n_philo)
    {
      current_time = get_current_time();
      milisec = current_time - philo_list->init_time;
      pthread_mutex_lock(&philo_list->time_mutex);
      if ((current_time - philo_list->ref_time) > time_to_dead)
      {
       printf("%ld %d died\n", milisec, philo_list->index);
       exit(1);
      }
      pthread_mutex_unlock(&philo_list->time_mutex);
      philo_list = philo_list->next;
      i++;
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
  printf("%ld %d has taken a fork\n", milisec, pointer->index);
  if (pointer->index % 2 == 0)
    pthread_mutex_lock(&pointer->next->fork);
  else
    pthread_mutex_lock(&pointer->fork);
  time = get_current_time();
  milisec = time - pointer->init_time;
  printf("%ld %d has taken a fork\n", milisec, pointer->index);
  time = get_current_time();
  milisec = time - pointer->init_time;
  printf("%ld %d is eating\n", milisec, pointer->index);
  pointer->ref_time = time;
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
    think(pointer);
    eat(pointer);
    philo_sleep(pointer);
    usleep((pointer->time_sleep / 3) * 1000);
  }
  return (NULL);
}

void  *philo_routine(void *arg)
{
  t_philo *pointer;

  pointer = (t_philo *)arg;
  while (1)
  {
    eat(pointer);
    philo_sleep(pointer);
    usleep((pointer->time_sleep / 3) * 1000);
    think(pointer);
  }
  return (NULL);
}
