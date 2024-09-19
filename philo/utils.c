/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:12:28 by jsobreir          #+#    #+#             */
/*   Updated: 2024/09/19 19:55:01 by jsobreir         ###   ########.fr       */
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
	if (!philo)
		exit(0);
	if (philo->args->forks_lock)
	{
		while (i++ < philo->args->num_philo)
			pthread_mutex_destroy(&philo->args->forks_lock[i]);
	}
	i = 0;
	if (print_msg != 0)
	{
		printf("%s\n", print_msg);
		exit(1);
	}
	exit(0);
}

/// @brief Function to get the current time elapsed since start of program in ms.
/// @param args Pointer to args struct where the start_time is stored.
/// @return Time elapsed since start of the program.
long long	get_time(void)
{
	struct timeval	time_of_day;
	long long		current_time;

	gettimeofday(&time_of_day, 0);
	current_time = (time_of_day.tv_sec * 1000) + (time_of_day.tv_usec / 1000);
	return (current_time);
}

#include <string.h>
void handler(t_philo *philo, char *event)
{
	long long	elapsed_time;

 	pthread_mutex_lock(&philo->args->mutex);
	elapsed_time = get_time() - philo->args->start;
	if (philo->died == 1)
	{
		printf("%lld %d %s", elapsed_time, philo->id, event);
		philo->args->nuke = 1;
		pthread_mutex_unlock(&philo->args->mutex);
		return ;
	}
	printf("%lld %d %s", elapsed_time, philo->id, event);
	pthread_mutex_unlock(&philo->args->mutex);
}

void	init_start_time(t_philo *philo)
{
	long long	start;
	struct timeval	start_time;
	
	start = 0;
	gettimeofday(&start_time, 0);
	start += start_time.tv_sec * 1000;
	start += start_time.tv_usec / 1000;
	philo->args->start = start;
}