/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:40:35 by gborne            #+#    #+#             */
/*   Updated: 2022/07/14 12:35:10 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_next_fork(t_philo *philo)
{
	int	id_next;

	id_next = philo->id + 1;
	if (philo->id >= philo->data->nb_philo - 1)
		id_next = 0;
	return (id_next);
}

static void	get_forks(t_philo *philo, long long starttime)
{
	pthread_mutex_lock(&philo->forks);
	//printf("philo->id=%d fork : %d\n",philo->id, philo->id);
	msg(philo->data, philo->id, "has taken a fork", gettime() - starttime);
	pthread_mutex_lock(&philo->data->philos[get_next_fork(philo)].forks);
	//printf("philo->id=%d next fork : %d\n",philo->id, get_next_fork(philo));
	msg(philo->data, philo->id, "has taken a fork", gettime() - starttime);
}

static void	clean_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks);
	pthread_mutex_unlock(&philo->data->philos[get_next_fork(philo)].forks);
}

static void	philo_eat(t_philo *philo, long long starttime)
{
	philo->time = gettime();
	msg(philo->data, philo->id, "is eating", gettime() - starttime);
	ft_usleep(philo->data->time_eat);
	philo->nb_eat++;
	if (philo->nb_eat == philo->data->nb_eat)
		philo->state = STATE_END;
}

void	*routine(void *p_philo)
{
	t_philo		*philo;
	long long	starttime;

	philo = (t_philo *)p_philo;
	starttime = philo->data->starttime;
	while (philo->state != STATE_END)
	{
		get_forks(philo, starttime);
		philo_eat(philo, starttime);
		clean_forks(philo);
		msg(philo->data, philo->id, "is sleeping", gettime() - starttime);
		ft_usleep(philo->data->time_sleep);
		msg(philo->data, philo->id, "is thinking", gettime() - starttime);
		usleep(42);
	}
	philo->data->philos_end++;
	return (NULL);
}
