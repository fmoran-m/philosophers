#include "philo.h"

void  *is_dead(void *arg)
{
  long int time_to_dead;
  long int current_time;
  t_philo *philo_list;
  int i;

  philo_list = (t_philo *)arg;
  time_to_dead = philo_list->time_die;
  while (1)
  {
    i = 0;
    current_time = get_current_time();
    while(i <= philo_list->n_philo)
    {
      if ((current_time - philo_list->ref_time) > time_to_dead) //Creo que aquí tengo un data race
      {
       printf("%ld %d died\n", current_time, philo_list->index);
       exit(1);
      }
      philo_list = philo_list->next;
      i++;
    }
  }
  return (NULL);
}

void think(t_philo *pointer)
{
  long int  time;

  time = get_current_time();
  printf("%ld %d is thinking\n", time, pointer->index);
}

void  eat(t_philo *pointer)
{
  long int  time;
  if (pointer->index % 2 == 0)
     pthread_mutex_lock(&pointer->fork);
  else
    pthread_mutex_lock(&pointer->next->fork);
  time = get_current_time();
  printf("%ld %d has taken a fork\n", time, pointer->index);
  if (pointer->index % 2 == 0)
    pthread_mutex_lock(&pointer->next->fork);
  else 
    pthread_mutex_lock(&pointer->fork);
  time = get_current_time();
  pointer->ref_time = time;
  printf("%ld %d has taken a fork\n", time, pointer->index);
  time = get_current_time();
  printf("%ld %d is eating\n", time, pointer->index);
  usleep(pointer->time_eat);
  pthread_mutex_unlock(&pointer->fork);
  pthread_mutex_unlock(&pointer->next->fork);
}

void  philo_sleep(t_philo *pointer)
{
  long int  time;

  time = get_current_time();
  printf("%ld %d is sleeping\n", time, pointer->index);
  usleep(pointer->time_sleep);
}

void  *philo_routine(void *arg)
{
  t_philo *pointer;

  pointer = (t_philo *)arg;
  while (1)
  {
    think(pointer);
    eat(pointer);
    philo_sleep(pointer);
  }
  return (NULL);
}
