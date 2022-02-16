/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 23:23:16 by gborne            #+#    #+#             */
/*   Updated: 2022/02/16 21:54:32 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks);
	write(1, "eat\n", 5);
	usleep(philo->data->time_to_eat);
	philo->nb_eat++;
	if (philo->nb_eat == philo->data->nb_eat)
		philo->state = STATE_END;
	pthread_mutex_unlock(&philo->forks);
}

void	philo_sleep(t_philo *philo)
{
	write(1, "sleep\n", 7);
	usleep(philo->data->time_to_sleep);
}

void*	routine(void *p_philo)
{
	t_philo *philo;

	philo = (t_philo*)p_philo;
	while (philo->state != STATE_END)
	{
		philo_eat(philo);
		philo_sleep(philo);
		write(1, "think\n", 7);
	}
	return NULL;
}

void	start_thread(t_data *data)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
	{
		pthread_create(&data->philos[i].thread, NULL, &routine, (void*)&data->philos[i]);
	}
	pthread_mutex_lock(&data->end);
	while (data->nb_philo != data->nb_philo_end)
		usleep(10);
	pthread_mutex_unlock(&data->end);
}

void	clear_data(t_data *data)
{
	while (data->nb_philo--)
		pthread_mutex_destroy(&data->philos->forks);
	pthread_mutex_destroy(&data->end);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 6 || init(argv, &data))
		return (write(1, "ERROR: Mauvais arguments.\n", 27));
	start_thread(&data);
	pthread_mutex_lock(&data.end);
	pthread_mutex_unlock(&data.end);
	clear_data(&data);
	return EXIT_SUCCESS;
}
