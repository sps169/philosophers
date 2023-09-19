/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:17:49 by sperez-s          #+#    #+#             */
/*   Updated: 2023/09/19 17:29:52 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_params *params)
{
	int	status;

	status = 1;
	if (pthread_mutex_init(&(params->death_lock), NULL) != 0)
		status = 0;
	if (pthread_mutex_init(&params->print_lock, NULL) != 0)
		status = 0;
	if (pthread_mutex_init(&params->meal_lock, NULL) != 0)
		status = 0;
	if (pthread_mutex_init(&params->kick_off_lock, NULL) != 0)
		status = 0;
	if (pthread_mutex_init(&params->satisfaction_lock, NULL) != 0)
		status = 0;
	if (pthread_mutex_init(&params->starve_queue_lock, NULL) != 0)
		status = 0;
	if (status == 0)
		clean_params(&params);
	return (status);
}

static int	check_params(t_params *params)
{
	if (params->n_philo == 0 || params->n_philo == 4294967295
		|| params->t_die == 4294967295
		|| params->t_eat == 4294967295
		|| params->t_sleep == 4294967295
		|| params->n_meals == 4294967295)
	{
		free(params);
		return (0);
	}
	if (!init_mutex(params))
		return (0);
	return (1);
}

t_params	*init_params(int argc, char *argv[])
{
	t_params	*params;

	params = NULL;
	if (argc >= 5 && argc <= 6)
	{
		params = malloc(sizeof(t_params));
		if (params == NULL)
			return (NULL);
		params->n_philo = atou(argv[1]);
		params->t_die = atou(argv[2]);
		params->t_eat = atou(argv[3]);
		params->t_sleep = atou(argv[4]);
		if (argc > 5)
			params->n_meals = atou(argv[5]);
		else
			params->n_meals = 0;
		params->n_satisfied = 0;
		params->death = 0;
		params->kick_off = 0;
		if (!check_params(params))
			return (NULL);
	}
	return (params);
}
