/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:43:10 by sperez-s          #+#    #+#             */
/*   Updated: 2023/06/28 21:47:38 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	starve_check_loop(t_node *philos)
{
	if (philos->philo_data->params->n_philo > 1)
	{
		usleep(philos->philo_data->params->t_die * 500);
		pthread_mutex_lock(&philos->philo_data->params->death_lock);
		while (philos->philo_data->params->death == 0)
		{
			pthread_mutex_unlock(&philos->philo_data->params->death_lock);
			pthread_mutex_lock(&(philos->philo_data->params->meal_lock));
			if (check_starvation(philos->philo_data) == 1)
				die(philos->philo_data, 1);
			pthread_mutex_unlock(&(philos->philo_data->params->meal_lock));
			philos = philos->next;
			usleep(philos->philo_data->params->t_die * 500);
			pthread_mutex_lock(&philos->philo_data->params->death_lock);
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
