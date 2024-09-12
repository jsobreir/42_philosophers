/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:12:28 by jsobreir          #+#    #+#             */
/*   Updated: 2024/09/12 15:22:46 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Function that exits the program. If error, print message and exit with EXIT_FAILURE code
/// @param args Pointer to the args struct.
/// @param print_msg Error message to print. If existing, the program will exit with EXIT_FAILURE code.
void	clean_exit(t_philo *philo, char *print_msg)
{
	int	i;

	i = 0;
	if (philo->args)
		free(philo->args);
	if (philo->args->forks_lock)
	{
		while (i++ < philo->args->num_philo)
			pthread_mutex_destroy(&philo->args->forks_lock[i]);
	}
	i = 0;
	if (&philo->philo_mutex)
		while (i++ < philo->args->num_philo)
			pthread_mutex_destroy(&philo[i].philo_mutex);		
	if (print_msg != 0)
	{
		printf("%s\n", print_msg);
		exit(1);
	}
	exit(0);
}

/// @brief Function to get the current time elapsed since start of program in ms
/// @param args Pointer to args struct where the start_time is stored
/// @return Time elapsed since start of the program.
int	get_time(t_args *args)
{
	struct timeval	time_of_day;
	int				current_time;

	gettimeofday(&time_of_day, 0);
	current_time = time_of_day.tv_usec - args->start_time.tv_usec;
	// printf("%d\n", current_time);
	return (current_time);
}