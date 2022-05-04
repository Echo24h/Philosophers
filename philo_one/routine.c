/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:40:35 by gborne            #+#    #+#             */
/*   Updated: 2022/05/02 00:32:26 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*last_philo(t_philo *philo)
{
	int	id_last;

	id_last = philo->id - 1;
	if (philo->id == -1)
		id_last = philo->data->nb_philo - 1;
	return (&philo->data->philos[id_last]);
}

static void	get_forks(t_philo *philo)
{
	t_philo	*philo_last;

	philo_last = last_philo(philo);
	pthread_mutex_lock(&philo->forks);
	msg(philo->data, philo->id, "has taken a fork", gettime());
	pthread_mutex_lock(&philo_last->forks);
	msg(philo->data, philo->id, "has taken a fork", gettime());
}

static void	clean_forks(t_philo *philo)
{
	t_philo	*philo_last;

	philo_last = last_philo(philo);
	pthread_mutex_unlock(&philo->forks);
	pthread_mutex_unlock(&philo_last->forks);
}

static void	philo_eat(t_philo *philo)
{
	philo->time = gettime();
	msg(philo->data, philo->id, "is eating", philo->time);
	usleep(philo->data->time_eat * 1000);
	philo->nb_eat++;
	if (philo->nb_eat == philo->data->nb_eat)
		philo->state = STATE_END;
}

void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	while (philo->state != STATE_END)
	{
		get_forks(philo);
		philo_eat(philo);
		clean_forks(philo);
		msg(philo->data, philo->id, "is sleeping", gettime());
		usleep(philo->data->time_sleep * 1000);
		msg(philo->data, philo->id, "is thinking", gettime());
	}
	philo->data->philos_end++;
	return (NULL);
}
