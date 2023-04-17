/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:29:28 by sperez-s          #+#    #+#             */
/*   Updated: 2023/04/18 00:30:20 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo_data *data, int result)
{
	pthread_mutex_lock(&data->params->death_lock);
	if (data->params->death == 0)
	{
		data->params->death = result;
		if (result == 1)
			print_death(data);
	}
	pthread_mutex_unlock(&data->params->death_lock);
}

int	wait_start(t_params *params)
{
	while (params->kick_off != 1)
	{
		if (params->kick_off == -1)
			return (-1);
		else
			usleep(10);
	}
	return (params->kick_off);
}

void	take_forks(t_philo_data *philo_data)
{
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
	philo_data->n_meals++;
	if (!is_dead)
		print_update(philo_data, 's');
	pthread_mutex_unlock(philo_data->l_fork);
	pthread_mutex_unlock(philo_data->r_fork);
	return (is_dead);
}
