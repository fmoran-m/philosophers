#include "philo.h"

void  *philo_routine(void *arg)
{
  t_philo *pointer;

  pointer = (t_philo *)arg;
  while (1)
  {
    printf("%d is thinking\n", pointer->index);
    if (pointer->index % 2 == 0)
     pthread_mutex_lock(&pointer->fork);
    else
     pthread_mutex_lock(&pointer->next->fork);
    printf("%d has taken a fork\n", pointer->index);
    if (pointer->index % 2 == 0)
     pthread_mutex_lock(&pointer->next->fork);
    else 
     pthread_mutex_lock(&pointer->fork);
    printf("%d has taken a fork\n", pointer->index);
    printf("%d is eating\n", pointer->index);
    usleep(pointer->time_eat);
    pthread_mutex_unlock(&pointer->fork);
    pthread_mutex_unlock(&pointer->next->fork);
    printf("%d is sleeping\n", pointer->index);
    usleep(pointer->time_sleep);
  }
  return (NULL);
}
