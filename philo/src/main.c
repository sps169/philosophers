/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:43:10 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/21 18:16:18 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks(void)
{
	system("leaks philo");
}

static t_philo_data	*init_philosopher(int id, t_params params, t_node *forks)
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

static void	free_philos(t_philo_data **philos, int last_philo)
{
	int	i;

	i = 0;
	while(i <= last_philo)
	{
		free(philos[i]);
		printf("Philo at position %i freed.\n", i);
		i++;
	}
}

static void	wait_and_free(t_node **forks, t_philo_data **philos, int last_philo)
{
	int	j;
	
	j = 0;
	while (j <= last_philo)
	{
		if (philos[j] != NULL)
			pthread_join(philos[j]->thread, NULL);
		j++;
	}
	cleanse_list(forks);
	free_philos(philos, last_philo);
}

static int	start_philo(t_params params)
{
	t_node			*forks;
	t_philo_data	*philos[200];
	unsigned int	i;

	forks = create_fork_circle(params.n_philo);
	if (forks == NULL)
	{
		printf("List creation failed\n");
		return (-1);
	}
	i = 1;
	gettimeofday(&(params.t_start), NULL);
	while (i <= params.n_philo)
	{
		philos[i - 1] = init_philosopher(i, params, forks);
		if (philos[i - 1] == NULL)
		{
			wait_and_free(&forks, philos, i - 2);
			return (-1);
		}
		i++;
	}
	wait_and_free(&forks, philos, i - 2);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_params	params;

	// atexit(leaks);
	(void)argc;
	(void)argv;
	params.n_philo = 101;
	params.t_die = 200;
	params.t_sleep = 50;
	params.t_eat = 50;
	params.n_meals = 100;
	start_philo(params);
	return (0);
}
