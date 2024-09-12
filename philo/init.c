/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:37:03 by jsobreir          #+#    #+#             */
/*   Updated: 2024/09/12 19:42:39 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Inittializes the args struct and the philosopher's threads attributing an initial value to each
/// @param args Pointer to the args struct
void init(t_args *args, t_philo *philo)
{
	int	i;

    args->max_eat = 0;
    args->died = 0;
	i = 0;
	while (i < args->num_philo)
	{
		pthread_mutex_init(&args->forks_lock[i], NULL);
		i++;
	}
	i = 0;
    while (i < args->num_philo)
    {
		pthread_mutex_init(&philo[i].philo_mutex, NULL);
        philo[i].args = args;
        philo[i].thread = 0;
        philo[i].id = 0;
        philo[i].alive = 1;
        philo[i].last_supper = 0;
		i++;
	}
}

// fork[0] = philo[0] (id == 1) Right fork && philo[N - 1] (id == N) Left fork
// fork[1] = philo[1] (id == 2) Right fork && philo[2] (id = 3) Left fork
// fork[N - 1] = philo[N - 1] (id == N) Right fork && ...

// All philos start with left fork in hand but one starts with both forks

/// @brief Function to innitialize N philosopher threads
/// @param philo Pointer to the array of philo structs
/// @param args Pointer to the struct of arguments and program wide vars
void	init_philos(t_philo *philo, t_args *args)
{
	int	i;

	i = 1;
	while (i <= args->num_philo)
	{
		philo[i - 1].id = i;
		if (pthread_create(&philo[i - 1].thread, NULL, routine, (void *)&philo[i - 1]) != 0)
			clean_exit(philo, "Error");
		i++;
	}
	monitoring(args, philo);
	i = 1;
	exit(0);
	while (i <= args->num_philo)
	{
		if (pthread_join(philo[i - 1].thread, NULL) != 0)
			clean_exit(philo, "Error");
		i++;
	}
}
