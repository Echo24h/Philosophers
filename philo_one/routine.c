/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:40:35 by gborne            #+#    #+#             */
/*   Updated: 2022/07/10 04:19:40 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep( unsigned long long time, unsigned long long starttime)
{
	usleep(0.95 * time);
	while (gettime() < starttime + time)
		usleep(1);
}

static t_philo	*last_philo(t_philo *philo)
{
	int	id_last;

	id_last = philo->id - 1;
	if (philo->id == -1)
		id_last = philo->data->nb_philo - 1;
	return (&philo->data->philos[id_last]);
}

static void	get_forks(t_philo *philo, long long tmp)
{
	t_philo	*philo_last;

	philo_last = last_philo(philo);
	pthread_mutex_lock(&philo->forks);
	msg(philo->data, philo->id, "has taken a fork", gettime() - tmp);
	pthread_mutex_lock(&philo_last->forks);
	msg(philo->data, philo->id, "has taken a fork", gettime() - tmp);
}

static void	clean_forks(t_philo *philo)
{
	t_philo	*philo_last;

	philo_last = last_philo(philo);
	pthread_mutex_unlock(&philo->forks);
	pthread_mutex_unlock(&philo_last->forks);
}

static void	philo_eat(t_philo *philo, long long tmp)
{
	philo->time = gettime();
	msg(philo->data, philo->id, "is eating", philo->time - tmp);
	ft_usleep(philo->data->time_eat, gettime());
	philo->nb_eat++;
	if (philo->nb_eat == philo->data->nb_eat)
		philo->state = STATE_END;
}

void	*routine(void *p_philo)
{
	t_philo	*philo;
	long long starttime = gettime();

	philo = (t_philo *)p_philo;
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
