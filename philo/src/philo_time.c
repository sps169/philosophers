/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:25:01 by sperez-s          #+#    #+#             */
/*   Updated: 2023/07/17 19:54:51 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_meal_time(t_philo_data *philo_data)
{
	pthread_mutex_lock(&(philo_data->params->meal_lock));
	gettimeofday(&philo_data->last_meal, NULL);
	pthread_mutex_unlock(&(philo_data->params->meal_lock));
}

void	real_sleep(int m_sec)
{
	struct timeval	init_time;
	struct timeval	curr_time;

	if (m_sec > 0)
	{
		gettimeofday(&init_time, NULL);
		usleep(m_sec * 500);
		gettimeofday(&curr_time, NULL);
		while (time_diff(&init_time, &curr_time) < m_sec)
		{
			usleep(100);
			gettimeofday(&curr_time, NULL);
		}
	}
}

int	check_starvation(t_philo_data *data)
{
	struct timeval	curr_time;
	int				ret_value;

	ret_value = 0;
	gettimeofday(&curr_time, NULL);
	pthread_mutex_lock(data->n_meals_mutex);
	if (data->params->n_meals != 0 && data->n_meals == data->params->n_meals)
		ret_value = 0;
	else if (time_diff(&(data->last_meal), &curr_time)
		> (int)(data->params->t_die))
		ret_value = 1;
	else
		ret_value = 0;
	pthread_mutex_unlock(data->n_meals_mutex);
	return (ret_value);
}

int	sleep_or_die(int sleep, t_philo_data *data)
{
	struct timeval	curr_time;
	int				time_left;

	gettimeofday(&curr_time, NULL);
	time_left = data->params->t_die - time_diff(&data->last_meal, &curr_time);
	if (time_left < sleep)
	{
		real_sleep(time_left);
		die(data, 1);
		return (1);
	}
	else
		real_sleep(sleep);
	return (0);
}
