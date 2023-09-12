/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:43:10 by sperez-s          #+#    #+#             */
/*   Updated: 2023/09/12 12:06:19 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	execute_starve_check(t_node *philos)
{
	t_starve_node	*starve_node;
	struct timeval	curr_time;
	unsigned int	curr_ms;

	curr_ms = 0;
	starve_node = NULL;
	starve_node = get_next_starve_node(philos->philo_data->params);
	gettimeofday(&curr_time, NULL);
	curr_ms = time_diff(&(philos->philo_data->params->t_start), &curr_time);
	while (curr_ms < starve_node->death_ms)
	{
		usleep(starve_node->death_ms - curr_ms);
		gettimeofday(&curr_time, NULL);
		curr_ms = time_diff(&(philos->philo_data->params->t_start), &curr_time);
	}
	if (check_starvation(starve_node->philo) == 1)
		die(starve_node->philo);
}

static void	starve_check_loop(t_node *philos)
{
	pthread_mutex_lock(&philos->philo_data->params->death_lock);
	pthread_mutex_lock(&philos->philo_data->params->satisfaction_lock);
	while (philos->philo_data->params->death == 0
			&& (philos->philo_data->params->n_meals == 0 ||
			(philos->philo_data->params->n_meals != 0 &&
			philos->philo_data->params->n_satisfied <
			philos->philo_data->params->n_philo)))
	{
		pthread_mutex_unlock(&philos->philo_data->params->satisfaction_lock);
		pthread_mutex_unlock(&philos->philo_data->params->death_lock);
		execute_starve_check(philos);
		pthread_mutex_lock(&philos->philo_data->params->death_lock);
		pthread_mutex_lock(&philos->philo_data->params->satisfaction_lock);
	}
	pthread_mutex_unlock(&philos->philo_data->params->satisfaction_lock);
	pthread_mutex_unlock(&philos->philo_data->params->death_lock);

}

static int	start_philo(t_params *params)
{
	t_node	*philos;

	pthread_mutex_lock(&(params->kick_off_lock));
	philos = create_circle(params);
	if (philos == NULL)
	{
		printf("List creation failed\n");
		params->kick_off = -1;
		pthread_mutex_unlock(&(params->kick_off_lock));
		return (-1);
	}
	gettimeofday(&(params->t_start), NULL);
	params->kick_off = 1;
	pthread_mutex_unlock(&(params->kick_off_lock));
	if (params->n_philo > 1)
		starve_check_loop(philos);
	wait_and_free(&philos);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_params	*params;

	params = init_params(argc, argv);
	if (params != NULL)
	{
		start_philo(params);
		clean_params(&params);
	}
	else
		printf("Wrong params\n");
	return (0);
}
