/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:37:03 by jsobreir          #+#    #+#             */
/*   Updated: 2024/09/19 19:55:30 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Inittializes the args struct and the philosopher's threads attributing an initial value to each
/// @param args Pointer to the args struct
void init(t_args *args, t_philo *philo)
{
	int	i;

    args->max_eat = 0;
	args->nuke = 0;
	args->start = 0;
	i = 0;
	pthread_mutex_init(&args->time_lock, NULL);
	pthread_mutex_init(&args->mutex, NULL);
	while (i < args->num_philo)
	{
		pthread_mutex_init(&args->forks_lock[i], NULL);
		i++;
	}
	i = 0;
    while (i < args->num_philo)
    {
        philo[i].args = args;
		philo[i].died = 0;
        philo[i].thread = 0;
        philo[i].id = 0;
        philo[i].last_supper = 0;
		i++;
	}
}

// All philos start with left fork in hand but one starts with both forks

/// @brief Function to innitialize N philosopher threads
/// @param philo Pointer to the array of philo structs
/// @param args Pointer to the struct of arguments and program wide vars
void	init_philos(t_philo *philo, t_args *args)
{
	int	i;

	init_start_time(philo);
	i = 1;
	while (i <= args->num_philo)
	{
		philo[i - 1].id = i;
		if (pthread_create(&philo[i - 1].thread, NULL, routine, (void *)&philo[i - 1]) != 0)
			clean_exit(philo, "Error");
		i++;
	}
	// pthread_mutex_unlock(&args->mutex);
	monitoring(args, philo);
	i = 0;
	while (i < args->num_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			clean_exit(philo, "Error");
		i++;
	}
	exit(0);
}
