/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:54:33 by jsobreir          #+#    #+#             */
/*   Updated: 2024/09/19 19:15:21 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Function to convert a string of numbers to an int
/// @param nptr String of numbers
/// @return Int corresponding to the number in nptr
int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}

/// @brief Function to check if the args of the program are in right format
/// @param args Pointer to the args struct filled with the program arguments
void check_args(int argc, t_philo *philo, t_args *args)
{
	if (args->tdie < 1 || args->teat < 1000 || args->tsleep < 1000
	|| args->num_philo < 1)
		clean_exit(philo, "Error: Invalid time_to_die");
	else if (args->max_eat < 0 && argc == 5)
		clean_exit(philo, "Error: number_of_times_each_philosopher_must_eat must be positive.");
	else if (args->num_philo > 200)
		clean_exit(philo, "Error: Program only accepts up to 200 philosophers.");
}

/// @brief Function to parse the arguments of the program and fill the args struct
/// @param args Pointer to the args struct
/// @param argc Number of arguments of the program
/// @param argv Pointer to an array of program arguments
void	parse_args(t_philo *philo, t_args *args, int argc, char **argv)
{
	char	**temp;
	char	*iterate;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid input.\n");
		exit(1);
	}
	temp = argv + 1;
	while (*temp)
	{
		iterate = *temp;
		while (*iterate)
		{
			if (*iterate == '+' || *iterate == '-')
				iterate++;
			if (*iterate < '0' || *iterate > '9')
				clean_exit(philo, "Error: Invalid input.");
			iterate++;			
		}
		temp++;
	}
	args->num_philo = ft_atoi(argv[1]);
	args->tdie = ft_atoi(argv[2]);
	args->teat = ft_atoi(argv[3]) * 1000;
	args->tsleep = ft_atoi(argv[4]) * 1000;
	args->max_eat = 0; // Careful when implemented. Innitialized this due to conditional jump error.
	if (argv[5])
		args->max_eat = ft_atoi(argv[5]);
	check_args(argc, philo, args);
	return ;
}