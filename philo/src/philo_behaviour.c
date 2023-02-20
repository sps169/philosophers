/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:12:39 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/20 13:31:21 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_update(t_philo_data *data, char print_type)
{
	struct timeval	 curr_time;
	int				timediff;

	gettimeofday(&curr_time, NULL);
	timediff = time_diff(&data->params.t_start, &curr_time);
	if (print_type == 'e')
		printf("%d ms: %u is eating\n", timediff, data->id);
	else if (print_type == 's')
		printf("%d ms: %u is sleeping\n", timediff, data->id);
	else if (print_type == 't')
		printf("%d ms: %u is thinking\n", timediff, data->id);
}

void	*philo_behaviour(void *data)
{
	t_philo_data	*philo_data;
	t_node			*l_fork;
	t_node			*r_fork;
	unsigned int	n_meals;

	n_meals = 0;
	philo_data = (t_philo_data *)data;
	while (n_meals < philo_data->params.n_meals)
	{
		while(philo_data->forks->id != 1)
			philo_data->forks = philo_data->forks->next;
		l_fork = philo_data->forks;
		while(philo_data->forks->id != 2)
			philo_data->forks = philo_data->forks->next;
		r_fork = philo_data->forks;
		pthread_mutex_lock(&(l_fork->fork));
		pthread_mutex_lock(&(r_fork->fork));
		gettimeofday(&(philo_data->last_meal), NULL);
		print_update(philo_data, 'e');
		usleep(philo_data->params.t_eat * 1000);
		print_update(philo_data, 's');
		n_meals++;
		pthread_mutex_unlock(&(l_fork->fork));
		pthread_mutex_unlock(&(r_fork->fork));
		usleep(philo_data->params.t_sleep * 1000);
		print_update(philo_data, 't');
	}
	return (NULL);
}
