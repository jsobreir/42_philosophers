/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:56:26 by jsobreir          #+#    #+#             */
/*   Updated: 2024/09/19 19:49:37 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Main function of the program
/// @param argc Number of inputs to the program
/// @param argv Array containing the inputs of the program
int	main(int argc, char **argv)
{
	t_args	args;
	t_philo	philo[PHILO_MAX];

	parse_args(philo, &args, argc, argv);
	init(&args, philo);
	init_philos(philo, &args);
	clean_exit(philo, 0);
}

/// @brief This is the eat, sleep, think routine for each philo (thread).
/// @param phil The specific philo struct.
/// @return 
void	*routine(void *phil)
{
	t_philo *philo;

	philo = (t_philo *)phil;
	while (1)
	{
		printf("Here1\n");
		pthread_mutex_lock(&philo->args->mutex);
		if (philo->args->nuke == 1)
		{
			printf("Here\n");
			pthread_mutex_unlock(&philo->args->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->mutex);
		eating(philo);
		handler(philo, SLEEP);
		usleep(philo->args->tsleep);
		handler(philo, THINK);
	}
	return (NULL);
}

/// @brief Function to make current philo eat. Locks and unlocks the fork mutex while time_to_eat.
/// @param args Pointer to args struct. 
void	eating(t_philo *philo)
{
	int	id;
	int	l_fork;
	int	r_fork;

	id = philo->id;
	l_fork = id - 1;
	if (id != 1)
		r_fork = id - 2;
	else
		r_fork = philo->args->num_philo - 1;
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&philo->args->forks_lock[l_fork]); // Left
		pthread_mutex_lock(&philo->args->forks_lock[r_fork]); // Right
	}
	else
	{
		pthread_mutex_lock(&philo->args->forks_lock[r_fork]); //Right
		pthread_mutex_lock(&philo->args->forks_lock[l_fork]); //Left		
	}
	handler(philo, FORK);
	handler(philo, FORK);
	philo->last_supper = get_time();
	handler(philo, EAT);
	usleep(philo->args->teat);
	if (id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->args->forks_lock[r_fork]); // Right
		pthread_mutex_unlock(&philo->args->forks_lock[l_fork]); // Left
	}
	else
	{
		pthread_mutex_unlock(&philo->args->forks_lock[l_fork]); //Left		
		pthread_mutex_unlock(&philo->args->forks_lock[r_fork]); //Right
	}
}

/// @brief Function that monitors if the philosophers are alive. If not, exits program.
/// @param args Pointer to the args struct.
/// @param philo Pointer to the philo stucts array.
void	monitoring(t_args *args, t_philo *philo)
{
	int	i;
	long long	time_since_eat;

	while (1)
	{
		i = 0;
		while (i < args->num_philo)
		{
			pthread_mutex_lock(&args->time_lock);
			time_since_eat = get_time() - args->start - philo[i].last_supper;
			if (time_since_eat > args->tdie)
			{
				philo[i].died = 1;
				pthread_mutex_unlock(&args->time_lock);
				handler(&philo[i], DIED);
				return ;
			}
			pthread_mutex_unlock(&args->time_lock);
			i++;
		}
	}
}
