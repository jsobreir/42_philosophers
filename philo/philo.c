/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:56:26 by jsobreir          #+#    #+#             */
/*   Updated: 2024/09/12 19:38:28 by jsobreir         ###   ########.fr       */
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
	if (philo->id == 1)
		gettimeofday(&philo->args->start_time, 0);
	while (1)
	{
		// pthread_mutex_lock(&philo->philo_mutex);
		if (philo->args->died == 1)
			break ;
		// pthread_mutex_unlock(&philo->philo_mutex);
		eating(philo);
		sleeping(philo);
		thinking(philo);
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
	printf("%d %d has taken a fork\n", get_time(philo->args), philo->id);
	if (philo->id == 1)
		printf("%d %d is eating\n", get_time(philo->args), philo->id);
	usleep(philo->args->teat);
	philo->last_supper = get_time(philo->args);
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

void	thinking(t_philo *philo)
{
	printf("%d %d is thinking\n", get_time(philo->args), philo->id);
}

void	sleeping(t_philo *philo)
{
	printf("%d %d is sleeping\n", get_time(philo->args), philo->id);
	usleep(philo->args->tsleep);
}

/// @brief Function that monitors if the philosophers are alive. If not, exits program.
/// @param args Pointer to the args struct.
/// @param philo Pointer to the philo stucts array.
void	monitoring(t_args *args, t_philo *philo)
{
	int	i;
	int	time_since_eat;

	i = 0;
	while (i < args->num_philo)
	{
		printf("Philo %d in monitoring\n", philo[i].id);
		// Implement number of times philosopher has eated check here
		time_since_eat = get_time(args) - philo[i].last_supper;
		if (time_since_eat > args->teat)
		{
			philo[i].alive = 0;
			pthread_mutex_lock(&philo->philo_mutex);
			args->died = 1;
			printf("%d %d died\n", get_time(args), philo[i].id);
			pthread_mutex_unlock(&philo->philo_mutex);
			break;
		}
		i++;
	}
	// Two options from here: either the philosophers check if they are dead and
	// alter a variable that is external to all philos, or the monitoring function
	// checks if each philo is dead in a loop
}
