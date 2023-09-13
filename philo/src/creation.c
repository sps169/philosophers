/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:06:08 by sperez-s          #+#    #+#             */
/*   Updated: 2023/09/13 12:13:14 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_fork(unsigned int id, pthread_mutex_t **fork)
{
	*fork = malloc(sizeof(pthread_mutex_t));
	if (*fork == NULL)
		return (-1);
	if (pthread_mutex_init(*fork, NULL) != 0)
	{
		printf("[ERROR]: Node with id %u mutex initialization failed\n", id);
		return (-1);
	}
	return (0);
}

static int	init_thread(t_philo_data *data, void *(*f)(void *))
{
	if (pthread_create(&(data->thread), NULL, f, (void *)(data)) != 0)
	{
		printf("[ERROR]: Thread with philo_id %u initialization failed\n",
			data->id);
		return (0);
	}
	return (1);
}

static int	create_meals_mutex(unsigned int id, pthread_mutex_t **mutex)
{
	*mutex = malloc(sizeof(pthread_mutex_t));
	if (*mutex == NULL)
		return (-1);
	if (pthread_mutex_init(*mutex, NULL) != 0)
	{
		printf("[ERROR]: Node with id %u mutex initialization failed\n", id);
		return (-1);
	}
	return (0);
}

static int	philo_mutex_setup(unsigned int id, t_philo_data *data)
{
	int	status;

	status = 0;
	if (create_fork(id, &(data->r_fork)) == -1)
		status = -1;
	if (create_meals_mutex(id, &(data->n_meals_mutex)) == -1)
		status = -1;
	if (create_meals_mutex(id, &data->last_meal_mutex) == -1)
		status = -1;
	if (status < 0)
		clean_philo_data(&data);
	return (0);
}

t_philo_data	*create_philosopher(unsigned int id,
	t_params *params, t_node *prev)
{
	t_philo_data	*data;
	void			*(*func)(void *);

	data = malloc(sizeof(t_philo_data));
	if (data == NULL)
		return (NULL);
	if (prev != NULL)
		data->l_fork = prev->philo_data->r_fork;
	if (philo_mutex_setup(id, data) == -1)
		return (NULL);
	data->params = params;
	data->id = id;
	data->n_meals = 0;
	if (params->n_philo > 1)
		func = &philo_behaviour;
	else
		func = &lone_wolf;
	if (!init_thread(data, func))
	{
		clean_philo_data(&data);
		return (NULL);
	}
	return (data);
}
