/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:05:27 by gborne            #+#    #+#             */
/*   Updated: 2022/04/20 20:59:20 by gborne           ###   ########.fr       */
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

// State of thread
# define STATE_EAT		0
# define STATE_SLEEP	1
# define STATE_FORK		2
# define STATE_THINK	3
# define STATE_DIED		4
# define STATE_END		5

# define DELAY_SECOND	1000

// Struct of thread
typedef struct s_philo
{
	int					id;
	char				state;
	int					nb_eat;
	struct s_data		*data;
	pthread_t			thread;
	pthread_mutex_t		forks;
	unsigned long long	time;
}	t_philo;

typedef struct	s_data
{
	int				nb_philo;
	int				nb_eat;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	t_philo			*philos;
	int				philos_end;
	pthread_mutex_t	write;
	pthread_mutex_t	end;
}	t_data;

// ---------- utils.c ----------
int					ft_strisdigit(char *str);
int					ft_isdigit(int c);
unsigned long long	gettime(void);
// Print text and use mutex
void				msg(t_data *data, int id, char *text, unsigned long long time);

// Convert string number to int
int					ft_atoi(const char *str);

// Print error and exit program
void				ft_error(char *error_msg);

// Init data and philosophers
int					init(char **argv, t_data *data);

#endif

