/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:12:39 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/23 16:40:02 by sperez-s         ###   ########.fr       */
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
	if (check_death(data->params) == 0)
	{
		pthread_mutex_lock(&data->params->death_lock);
		data->params->death = result;
		pthread_mutex_unlock(&data->params->death_lock);
		if (result == 1)
			print_update(data, 'd');
	}
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

void	*philo_behaviour(void *data)
{
	t_philo_data	*philo_data;
	t_node			*l_fork;
	t_node			*r_fork;
	unsigned int	n_meals;

	n_meals = 0;
	philo_data = (t_philo_data *)data;
	while (philo_data->params->kick_off != 1)
	{
		if (philo_data->params->kick_off == -1)
			return (NULL);
		else
			usleep(10);
	}
	gettimeofday(&philo_data->last_meal, NULL);
	if (philo_data->id % 2 != 0)
		usleep(500);
	while (check_death(philo_data->params) == 0 && n_meals < philo_data->params->n_meals)
	{
		while(philo_data->forks->id != philo_data->id)
			philo_data->forks = philo_data->forks->next;
		l_fork = philo_data->forks;
		if (philo_data->id != philo_data->params->n_philo)
		{
			while (philo_data->forks->id != philo_data->id + 1)
				philo_data->forks = philo_data->forks->next;
		}
		else
		{
			while (philo_data->forks->id != 1)
				philo_data->forks = philo_data->forks->next;
		}
		r_fork = philo_data->forks;
		gettimeofday(&philo_data->time_block, NULL);
		philo_data->time_left = philo_data->params->t_die
								- time_diff(&philo_data->last_meal,
											 &philo_data->time_block);
		philo_data->is_block = 1;
		pthread_mutex_lock(&(l_fork->fork));
		print_update(philo_data, 'l');
		pthread_mutex_lock(&(r_fork->fork));
		philo_data->is_block = 0;
		print_update(philo_data, 'r');
		gettimeofday(&(philo_data->last_meal), NULL);
		print_update(philo_data, 'e');
		sleep_or_die(philo_data->params->t_eat, philo_data);
		pthread_mutex_unlock(&(l_fork->fork));
		pthread_mutex_unlock(&(r_fork->fork));
		n_meals++;
		print_update(philo_data, 's');
		if (sleep_or_die(philo_data->params->t_sleep, philo_data) == 1)
			return (NULL);
		print_update(philo_data, 't');
	}
	if (check_death(philo_data->params) == 0)
		die(philo_data, -1);
	return (NULL);
}
