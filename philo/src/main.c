/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:43:10 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/23 17:15:18 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks(void)
{
	system("leaks philo");
}

static t_philo_data	*init_philosopher(int id, t_params *params, t_node *forks)
{
	t_philo_data	*data;

	data = malloc(sizeof(t_philo_data));
	if (data == NULL)
		return (NULL);
	data->forks = forks;
	data->params = params;
	data->id = id;
	pthread_create(&(data->thread), NULL, &philo_behaviour, (void *)(data));
	return (data);
}

static void	blocked_death_check_loop(t_philo_data **philos, t_params *params)
{
	unsigned int	j;
	struct timeval	curr_time;

	while (check_death(params) == 0)
	{
		j = 0;
		while (philos[j] != NULL && check_death(params) == 0)
		{
			gettimeofday(&curr_time, NULL);
			if (philos[j]->is_block && time_diff(&philos[j]->time_block, &curr_time) > philos[j]->time_left)
				die(philos[j], 1);
		}
	}
}

static int	start_philo(t_params *params)
{
	t_node			*forks;
	t_philo_data	*philos[500];
	unsigned int	i;

	forks = create_fork_circle(params->n_philo);
	if (forks == NULL)
	{
		printf("List creation failed\n");
		return (-1);
	}
	i = 1;
	while (i <= params->n_philo)
	{
		philos[i - 1] = init_philosopher(i, params, forks);
		if (philos[i - 1] == NULL)
		{
			params->kick_off = -1;
			wait_and_free(&forks, philos, i - 2);
			return (-1);
		}
		i++;
	}
	gettimeofday(&(params->t_start), NULL);
	params->kick_off = 1;
	blocked_death_check_loop(philos, params);
	wait_and_free(&forks, philos, i - 2);
	return (0);
}

static t_params *init_params(int argc, char *argv[])
{
	t_params *params;

	if (argc >= 5 && argc <= 6)
	{
		params = malloc(sizeof(t_params));
		if (params == NULL)
			return (NULL);
		params->n_philo = 16;
		params->t_die = 200;
		params->t_sleep = 100;
		params->t_eat = 100;
		params->n_meals = 100;
		params->death = 0;
		params->kick_off = 0;
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
