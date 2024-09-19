/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:56:55 by jsobreir          #+#    #+#             */
/*   Updated: 2024/09/19 19:09:49 by jsobreir         ###   ########.fr       */
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
# define FORK		"has taken a fork\n"
# define EAT		"is eating\n"
# define SLEEP		"is sleeping\n"
# define DIED		"died\n"
# define THINK		"is thinking\n"

/// @brief Struct for program inputs and other program-wide vars
/// @param num_philo Program arg: number_of_philos
/// @param tdie Program argument: time_to_die
/// @param teat Program argument: time_to_eat
/// @param tsleep Program argument: time_to_sleep
/// @param max_eat Program argument: number_of_times_each_philosopher_must_eat 
typedef struct s_args
{
	int				nuke;
	int				num_philo;
	int				tdie;
	int				teat;
	int				tsleep;
	int				max_eat;
	long long		start;
	pthread_mutex_t	forks_lock[PHILO_MAX];
	pthread_mutex_t	time_lock;
	pthread_mutex_t	mutex;
}	t_args;

/// @brief Struct for each philosopher specific values (threads)
/// @param fork_lock Pointer to the fork mutex
/// @param id Number of the philo: from 1 to num_philo - 1
/// @param
typedef struct s_philo
{
	pthread_t		thread;
	int				died;
	int				id;
	long long		last_supper;
	t_args			*args;
}	t_philo;

// INIT
void	init_philos(t_philo *philo, t_args *args);
void	init(t_args *args, t_philo *philo);


// PARSER
void	parse_args(t_philo *philo, t_args *args, int argc, char **argv);
int		ft_atoi(const char *nptr);
void	check_args(int argc, t_philo *philo, t_args *args);

// ROUTINE
void	*routine(void *arg);

// UTILS
void		clean_exit(t_philo *philo, char *print_msg);
long long	get_time(void);
void		handler(t_philo *philo, char *event);
void		init_start_time(t_philo *philo);

void		eating(t_philo *philo);
void		monitoring(t_args *args, t_philo *philo);

#endif