/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:43:10 by sperez-s          #+#    #+#             */
/*   Updated: 2023/04/13 14:13:31 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks(void)
{
	system("leaks philo");
}

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

t_philo_data	*create_philosopher(unsigned int id, t_params *params, t_node *prev)
{
	t_philo_data	*data;
	void			*(*func)(void *);

	data = malloc(sizeof(t_philo_data));
	if (data == NULL)
		return (NULL);
	if (prev != NULL)
		data->l_fork = prev->philo_data->r_fork;
	if (create_fork(id, &(data->r_fork)) == -1)
	{
		free(data);
		return (NULL);
	}
	data->params = params;
	data->id = id;
	data->n_meals = 0;
	if (params->n_philo > 1)
		func = &philo_behaviour;
	else
		func = &lone_wolf;
	if (pthread_create(&(data->thread), NULL, func, (void *)(data)) != 0)
	{
		pthread_mutex_destroy((data->r_fork));
		printf("[ERROR]: Thread with philo_id %u initialization failed\n", data->id);
		return (NULL);
	}
	return (data);
}

static void	starve_check_loop(t_node *philos)
{
	if (philos->philo_data->params->n_philo > 1)
	{
		usleep(philos->philo_data->params->t_die * 500);
		while (philos->philo_data->params->death == 0)
		{
			pthread_mutex_lock(&(philos->philo_data->params->meal_lock));
			if (check_starvation(philos->philo_data) == 1)
				die(philos->philo_data, 1);
			pthread_mutex_unlock(&(philos->philo_data->params->meal_lock));
			philos = philos->next;
			usleep(philos->philo_data->params->t_die * 500);
		}
	}
}

static int	start_philo(t_params *params)
{
	t_node	*philos;

	philos = create_circle(params);
	if (philos == NULL)
	{
		printf("List creation failed\n");
		params->kick_off = -1;
		return (-1);
	}
	gettimeofday(&(params->t_start), NULL);
	params->kick_off = 1;
	starve_check_loop(philos);
	wait_and_free(&philos);
	return (0);
}

static t_params *init_params(int argc, char *argv[])
{
	t_params *params;

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
		params->death = 0;
		params->kick_off = 0;
		if (params->n_philo <= 0
			|| params->n_philo == 4294967295
			|| params->t_die < 0
			|| params->t_die == 4294967295
			|| params->t_eat < 0
			|| params->t_eat == 4294967295
			|| params->t_sleep < 0
			|| params->t_sleep == 4294967295
			|| params->n_meals < 0
			|| params->n_meals == 4294967295)
		{
			free(params);
			return (NULL);
		}
		if (pthread_mutex_init(&(params->death_lock), NULL) != 0)
		{
			free(params);
			return (NULL);
		}
		if (pthread_mutex_init(&params->print_lock, NULL) != 0)
		{
			free(params);
			pthread_mutex_destroy(&params->death_lock);
			return (NULL);
		}
		if (pthread_mutex_init(&params->meal_lock, NULL) != 0)
		{
			free(params);
			pthread_mutex_destroy(&params->death_lock);
			pthread_mutex_destroy(&params->print_lock);
			return (NULL);
		}
	}
	return (params);
}

int	main(int argc, char *argv[])
{
	t_params	*params;

	// atexit(leaks);

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


