/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 23:23:16 by gborne            #+#    #+#             */
/*   Updated: 2022/04/20 20:51:53 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static t_philo	*last_philo(t_philo *philo)
{
	int id_last;

	id_last = philo->id - 1;
	if (philo->id == -1)
		id_last = philo->data->nb_philo - 1;
	return (&philo->data->philos[id_last]);
}

void	get_forks(t_philo *philo)
{
	t_philo	*philo_last;

	philo_last = last_philo(philo);
	msg(philo->data, philo->id, "died", 5);
	pthread_mutex_lock(&philo->forks);
	msg(philo->data, philo->id, "has taken a fork", 17);
	pthread_mutex_lock(&philo_last->forks);
	msg(philo->data, philo->id, "has taken a fork", 17);
}

void	clean_forks(t_philo *philo)
{
	t_philo	*philo_last;

	philo_last = last_philo(philo);
	pthread_mutex_unlock(&philo->forks);
	pthread_mutex_unlock(&philo_last->forks);
}

int	philo_eat(t_philo *philo)
{
	if (gettime() > philo->time + philo->data->time_die)
	{
		philo->data->philos_end = philo->data->nb_philo;
		pthread_mutex_unlock(&philo->data->end);
		return EXIT_FAILURE;
	}
	philo->time = gettime();
	msg(philo->data, philo->id, "is eating", 10);
	usleep(philo->data->time_eat * 1000);
	philo->nb_eat++;
	if (philo->nb_eat == philo->data->nb_eat)
		philo->state = STATE_END;
	return (EXIT_SUCCESS);
}

void*	routine(void *p_philo)
{
	t_philo *philo;

	philo = (t_philo*)p_philo;
	while (philo->state != STATE_END)
	{
		get_forks(philo);
		if (philo_eat(philo) == EXIT_FAILURE)
			return NULL;
		clean_forks(philo);
		msg(philo->data, philo->id, "is sleeping", 12);
		usleep(philo->data->time_sleep * 1000);
		msg(philo->data, philo->id, "is thinking", 12);
	}
	philo->data->philos_end++;
	return NULL;
}

int		end(int died, t_data *data)
{
	if (died == TRUE)
		free(data->philos);
	return (0);
}

void	start_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		if (pthread_create(&data->philos[i].thread, NULL, &routine, (void*)&data->philos[i]) != 0 )
			ft_error("Can't create thread.\n");
}

void	clear_data(t_data *data)
{
	while (data->nb_philo--)
		pthread_mutex_destroy(&data->philos->forks);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->end);
}

int	monitoring(t_data *data)
{
	int i;
	unsigned long long	time;

	i = -1;
	time = gettime();
	while (++i < data->nb_philo)
	{
		if (data->philos->time + data->time_die < time)
		{

			msg(data, i, "died", 5);
			return end(TRUE, data);
		}
	}
	if (data->nb_philo <= data->philos_end)
			return end(FALSE, data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data				data;

	if (argc != 6 || init(argv, &data))
		return (write(1, "ERROR: Mauvais arguments.\n", 27));
	start_thread(&data);
	while (1)
		if (monitoring(&data) == 0)
			break;
	pthread_mutex_lock(&data.end);
	pthread_mutex_unlock(&data.end);
	//clear_data(&data);
	printf("END\n");
	return EXIT_SUCCESS;
}
