/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:29:28 by sperez-s          #+#    #+#             */
/*   Updated: 2023/09/12 12:06:01 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo_data *data)
{
	pthread_mutex_lock(&data->params->death_lock);
	if (data->params->death == 0)
	{
		data->params->death = 1;
		print_death(data);
	}
	pthread_mutex_unlock(&data->params->death_lock);
}

int	wait_start(t_params *params)
{
	if (params == NULL)
		return (-1);
	pthread_mutex_lock(&(params->kick_off_lock));
	pthread_mutex_unlock(&(params->kick_off_lock));
	return (params->kick_off);
}

void	take_forks(t_philo_data *philo_data)
{
	unsigned int	death_ms;

	death_ms = philo_data->params->t_die;
	pthread_mutex_lock(philo_data->last_meal_mutex);
	death_ms += time_diff(&(philo_data->params->t_start), &(philo_data->last_meal));
	pthread_mutex_unlock(philo_data->last_meal_mutex);
	add_starve_node(death_ms, philo_data);
	pthread_mutex_lock(philo_data->l_fork);
	print_update(philo_data, 'l');
	pthread_mutex_lock(philo_data->r_fork);
	print_update(philo_data, 'r');
}

int	eat(t_philo_data *philo_data)
{
	int	is_dead;

	is_dead = 0;
	gettimeofday(&(philo_data->last_meal), NULL);
	print_update(philo_data, 'e');
	is_dead = sleep_or_die(philo_data->params->t_eat, philo_data);
	pthread_mutex_lock(philo_data->n_meals_mutex);
	philo_data->n_meals++;
	if (philo_data->n_meals == philo_data->params->n_meals
		&& philo_data->n_meals != 0)
	{
		pthread_mutex_lock(&(philo_data->params->satisfaction_lock));
		philo_data->params->n_satisfied++;
		pthread_mutex_unlock(&(philo_data->params->satisfaction_lock));
	}
	pthread_mutex_unlock(philo_data->n_meals_mutex);
	print_update(philo_data, 's');
	pthread_mutex_unlock(philo_data->l_fork);
	pthread_mutex_unlock(philo_data->r_fork);
	return (is_dead);
}
