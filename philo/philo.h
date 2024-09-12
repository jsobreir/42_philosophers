/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:56:55 by jsobreir          #+#    #+#             */
/*   Updated: 2024/09/12 19:26:16 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Mandatory part
 * @{
 * 
 * @file philo.h
 * @brief Program Header
*/

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

/// @brief Max number of philosophers to sit at table
# define PHILO_MAX 200


/// @brief Struct for program inputs and other program-wide vars
/// @param num_philo Program arg: number_of_philos
/// @param tdie Program argument: time_to_die
/// @param teat Program argument: time_to_eat
/// @param tsleep Program argument: time_to_sleep
/// @param max_eat Program argument: number_of_times_each_philosopher_must_eat 
typedef struct s_args
{
	int				died;
	int				num_philo;
	int				tdie;
	int				teat;
	int				tsleep;
	int				max_eat;
	pthread_mutex_t	forks_lock[PHILO_MAX];
	struct timeval	start_time;
}	t_args;

/// @brief Struct for each philosopher specific values (threads)
/// @param fork_lock Pointer to the fork mutex
/// @param id Number of the philo: from 1 to num_philo - 1
/// @param
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				alive;
	int				last_supper;
	pthread_mutex_t	philo_mutex;
	t_args			*args;
}	t_philo;

// INIT
void	init_philos(t_philo *philo, t_args *args);
void	init(t_args *args, t_philo *philo);


// PARSER
void	parse_args(t_philo *philo, t_args *args, int argc, char **argv);
int		ft_atoi(const char *nptr);

// ROUTINE
void	*routine(void *arg);

// UTILS
void	clean_exit(t_philo *philo, char *print_msg);
int		get_time(t_args *args);

void	eating(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	monitoring(t_args *args, t_philo *philo);

#endif