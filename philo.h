/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:05:27 by gborne            #+#    #+#             */
/*   Updated: 2022/02/12 16:18:06 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#	define PHILO_H

#	ifndef TRUE
#		define TRUE 1
#	endif

#	ifndef FALSE
#		define FALSE 0
#	endif

#	include <unistd.h>
#	include <stdlib.h>
#	include <stdio.h>
#	include <string.h>
#	include <pthread.h>
#	include <semaphore.h>
#	include <sys/time.h>

# define STATE_EAT		0
# define STATE_SLEEP	1
# define STATE_FORK		2
# define STATE_THINK	3
# define STATE_DIED		4
# define STATE_OVER		5

typedef struct s_philo
{
	char		state;
	pthread_t	thread;
}	t_philo;

typedef struct	s_data
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_eat;
	t_philo	*philos;
}	t_data;

// utils.c
int	ft_strisdigit(char *str);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

// init.c
int	init_data(char **argv, t_data *data);
int	init(char **argv, t_data *data);

#endif

