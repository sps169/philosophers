/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:12:39 by sperez-s          #+#    #+#             */
/*   Updated: 2023/04/11 20:34:51 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_update(t_philo_data *data, char print_type)
{
	struct timeval	 curr_time;
	int				timediff;

	pthread_mutex_lock(&data->params->print_lock);
	if (check_death(data->params) == 0 || print_type == 'd')
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
	pthread_mutex_unlock(&data->params->print_lock);
}

static void	real_sleep(int m_sec)
{
	struct timeval	init_time;
	struct timeval	curr_time;
	
	gettimeofday(&init_time, NULL);
	gettimeofday(&curr_time, NULL);
	while (time_diff(&init_time, &curr_time) < m_sec)
	{
		usleep(10);
		gettimeofday(&curr_time, NULL);
	}
}

int	check_death(t_params *params)
{
	int death;

	pthread_mutex_lock(&params->death_lock);
	death = params->death;
	pthread_mutex_unlock(&params->death_lock);
	return (death);
}

void	die(t_philo_data *data, int result)
{
	pthread_mutex_lock(&data->params->death_lock);
	if (check_death(data->params) == 0)
	{
		data->params->death = result;
		if (result == 1)
			print_update(data, 'd');
	}
	pthread_mutex_unlock(&data->params->death_lock);
}

static int	sleep_or_die(int sleep, t_philo_data *data)
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

static int	wait_start(t_params *params)
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

static void	update_meal_time(t_philo_data *philo_data)
{
	gettimeofday(&philo_data->last_meal, NULL);
}

static void	take_forks(t_philo_data *philo_data)
{
	pthread_mutex_lock((philo_data->r_fork));
	print_update(philo_data, 'r');
	pthread_mutex_lock((philo_data->l_fork));
	print_update(philo_data, 'l');
}

static int	eat(t_philo_data *philo_data)
{
	int	is_dead;

	is_dead = 0;
	gettimeofday(&(philo_data->last_meal), NULL);
	print_update(philo_data, 'e');
	is_dead = sleep_or_die(philo_data->params->t_eat, philo_data);
	philo_data->n_meals++;
	pthread_mutex_unlock((philo_data->r_fork));
	pthread_mutex_unlock((philo_data->l_fork));
	return (is_dead);
}

void	*philo_behaviour(void *data)
{
	t_philo_data	*philo_data;

	philo_data = (t_philo_data *)data;
	wait_start(philo_data->params);
	update_meal_time(philo_data);
	if (philo_data->id % 2 != 0)
		usleep(1000);
	while (check_death(philo_data->params) == 0
			&& (philo_data->params->n_meals == 0
				|| (philo_data->n_meals < philo_data->params->n_meals)))
	{
		take_forks(philo_data);
		if (eat(philo_data) != 0)
			return (NULL);
		print_update(philo_data, 's');
		if (sleep_or_die(philo_data->params->t_sleep, philo_data) == 1)
			return (NULL);
		print_update(philo_data, 't');
	}
	if (check_death(philo_data->params) == 0)
		die(philo_data, -1);
	return (NULL);
}
