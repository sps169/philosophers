/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:43:10 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/17 19:57:41 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks(void)
{
	system("leaks philo");
}

static int	init_philosopher(int id, t_params params, t_node *forks)
{
	t_philo_data data;
	
	data.forks = forks;
	data.params = params;
	data.id = id;
	pthread_create(&(data.thread), NULL, &philo_behaviour, &data);

}

static int	start_philo(t_params params)
{
	t_node			*forks;
	pthread_t		thread_id;
	unsigned int	i;

	forks = create_fork_circle(params.n_philo);
	if (forks == NULL)
	{
		printf("List creation failed\n");
		return (-1);
	}
	print_list(forks);
	i = 1;
	while (i <= params.n_philo && init_philosopher(i, params, forks) != -1)
		i++;
	cleanse_list(&forks);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_params	params;

	(void)argc;
	(void)argv;
	params.n_philo = 3;
	params.t_die = 200;
	params.t_sleep = 50;
	params.t_eat = 50;
	params.n_meals = -1;
	params.t_start = gettimeofday(NULL, NULL);
	start_philo(params);
	return (0);
}
