/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:43:10 by sperez-s          #+#    #+#             */
/*   Updated: 2023/07/17 21:08:58 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	execute_starve_check(t_node *philos)
{
	int	first;

	first = 1;
	while (((philos->id != 1) || first == 1)
		&& philos->philo_data->params->death == 0)
	{
		pthread_mutex_unlock(&philos->philo_data->params->death_lock);
		pthread_mutex_lock(&(philos->philo_data->params->meal_lock));
		if (first == 1)
			first = 0;
		if (check_starvation(philos->philo_data) == 1)
			die(philos->philo_data, 1);
		pthread_mutex_unlock(&(philos->philo_data->params->meal_lock));
		philos = philos->next;
		pthread_mutex_lock(&philos->philo_data->params->death_lock);
	}
}

static void	starve_check_loop(t_node *philos)
{	
	if (philos->philo_data->params->n_philo > 1)
	{
		while (philos->id != 1)
			philos = philos->prev;
		real_sleep(philos->philo_data->params->t_die / 2);
		pthread_mutex_lock(&philos->philo_data->params->death_lock);
		while (philos->philo_data->params->death == 0)
		{
			pthread_mutex_unlock(&philos->philo_data->params->death_lock);
			pthread_mutex_lock(&philos->philo_data->params->death_lock);
			execute_starve_check(philos);
			pthread_mutex_unlock(&(philos->philo_data->params->death_lock));
			real_sleep(philos->philo_data->params->t_die);
			pthread_mutex_lock(&philos->philo_data->params->death_lock);
			printf("CHECKED\n");
		}
		pthread_mutex_unlock(&philos->philo_data->params->death_lock);
	}
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
