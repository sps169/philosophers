/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:12:39 by sperez-s          #+#    #+#             */
/*   Updated: 2023/07/17 19:59:14 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_wolf(void *data)
{
	t_philo_data	*philo_data;

	philo_data = (t_philo_data *)data;
	if (wait_start(philo_data->params) <= 0)
		return (NULL);
	update_meal_time(philo_data);
	pthread_mutex_lock(philo_data->r_fork);
	print_update(philo_data, 'r');
	real_sleep(philo_data->params->t_die);
	print_death(philo_data);
	pthread_mutex_unlock(philo_data->r_fork);
	return (NULL);
}

static void	*philo_loop(t_philo_data *philo_data)
{
	while (philo_data->params->death != 1 && (philo_data->params->n_meals == 0
			|| (philo_data->n_meals < philo_data->params->n_meals)))
	{
		pthread_mutex_unlock(philo_data->n_meals_mutex);
		pthread_mutex_unlock(&philo_data->params->death_lock);
		take_forks(philo_data);
		if (eat(philo_data) != 0)
			return (NULL);
		if (sleep_or_die(philo_data->params->t_sleep, philo_data) == 1)
			return (NULL);
		print_update(philo_data, 't');
		pthread_mutex_lock(&philo_data->params->death_lock);
		pthread_mutex_lock(philo_data->n_meals_mutex);
	}
	return (philo_data);
}

void	*philo_behaviour(void *data)
{
	t_philo_data	*philo_data;

	philo_data = (t_philo_data *)data;
	if (wait_start(philo_data->params) <= 0)
		return (NULL);
	update_meal_time(philo_data);
	if (philo_data->id % 2 != 0)
		usleep(1000);
	pthread_mutex_lock(&philo_data->params->death_lock);
	pthread_mutex_lock(philo_data->n_meals_mutex);
	if (philo_loop(philo_data) == NULL)
		return (NULL);
	pthread_mutex_unlock(&philo_data->params->death_lock);
	if (philo_data->n_meals >= philo_data->params->n_meals)
		die(philo_data, -1);
	pthread_mutex_unlock(philo_data->n_meals_mutex);
	return (NULL);
}
