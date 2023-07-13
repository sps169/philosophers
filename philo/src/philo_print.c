/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:23:38 by sperez-s          #+#    #+#             */
/*   Updated: 2023/07/13 21:06:20 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_update(t_philo_data *data, char print_type)
{
	struct timeval	curr_time;
	int				timediff;

	pthread_mutex_lock(&(data->params->death_lock));
	pthread_mutex_lock(&(data->params->print_lock));
	if (data->params->death != 1)
	{
		gettimeofday(&curr_time, NULL);
		timediff = time_diff(&data->params->t_start, &curr_time);
		if (print_type == 'e')
			printf("%d ms: %u is eating\n", timediff, data->id);
		else if (print_type == 's')
			printf("%d ms: %u is sleeping\n", timediff, data->id);
		else if (print_type == 't')
			printf("%d ms: %u is thinking\n", timediff, data->id);
		else if (print_type == 'l')
			printf("%d ms: %u has taken a fork (left)\n", timediff, data->id);
		else if (print_type == 'r')
			printf("%d ms: %u has taken a fork (right)\n", timediff, data->id);
		else if (print_type == 'd')
			printf("%d ms: %u died\n", timediff, data->id);
	}
	pthread_mutex_unlock(&(data->params->print_lock));
	pthread_mutex_unlock(&(data->params->death_lock));
}

void	print_death(t_philo_data *data)
{
	struct timeval	curr_time;
	int				timediff;

	pthread_mutex_lock(&(data->params->print_lock));
	gettimeofday(&curr_time, NULL);
	timediff = time_diff(&data->params->t_start, &curr_time);
	printf("%d ms: %u died\n", timediff, data->id);
	pthread_mutex_unlock(&(data->params->print_lock));
}
