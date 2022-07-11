/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:40:35 by gborne            #+#    #+#             */
/*   Updated: 2022/07/11 13:39:52 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*get_next_fork(t_philo *philo)
{
	int	id_next;

	id_next = philo->id + 1;
	if (philo->id > philo->data->nb_philo - 1)
		id_next = 0;
	return (&philo->data->philos[id_next].forks);
}

static void	get_forks(t_philo *philo, long long starttime)
{
	pthread_mutex_lock(&philo->forks);
	msg(philo->data, philo->id, "has taken a fork", gettime() - starttime);
	pthread_mutex_lock(get_next_fork(philo));
	msg(philo->data, philo->id, "has taken a fork", gettime() - starttime);
}

static void	clean_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks);
	pthread_mutex_unlock(get_next_fork(philo));
}

static void	philo_eat(t_philo *philo, long long starttime)
{
	philo->time = gettime();
	msg(philo->data, philo->id, "is eating", philo->time - starttime);
	ft_usleep(philo->data->time_eat, gettime());
	philo->nb_eat++;
	if (philo->nb_eat == philo->data->nb_eat)
		philo->state = STATE_END;
}

void	*routine(void *p_philo)
{
	t_philo		*philo;
	long long	starttime;

	philo = (t_philo *)p_philo;
	starttime = gettime();
	while (philo->state != STATE_END)
	{
		get_forks(philo, starttime);
		philo_eat(philo, starttime);
		clean_forks(philo);
		msg(philo->data, philo->id, "is sleeping", gettime() - starttime);
		ft_usleep(philo->data->time_sleep, gettime());
		msg(philo->data, philo->id, "is thinking", gettime() - starttime);
	}
	philo->data->philos_end++;
	return (NULL);
}
