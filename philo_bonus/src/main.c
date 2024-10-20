/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:27:34 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/20 14:17:49 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	create_semaphores (t_params *params)
{
	sem_t	*semaphore;

	if (sem_unlink("/forks"))
	{
		printf("Unlink forks semaphore failed with code %i\n", errno);
		if (errno == EACCES)
			return(0);
	}
	printf("Unlinked forks semaphore successfully\n");
	if (sem_unlink("/pickup"))
	{
		printf("Unlink pickup semaphore failed with code %i\n", errno);
		if (errno == EACCES)
			return(0);
	}
	printf("Unlink pickup semaphore successfully\n");
	if (sem_unlink("/print"))
	{
		printf("Unlink print semaphore failed with code %i\n", errno);
		if (errno == EACCES)
			return(0);
	}
	printf("Unlink print semaphore successfully\n");
	semaphore = sem_open("/forks", O_CREAT, O_RDWR, params->n_philo);
	if (semaphore == SEM_FAILED)
		return (0);
	printf("Forks semaphore created with value %i\n", params->n_philo);
	params->forks = semaphore;
	semaphore = sem_open("/pickup", O_CREAT, O_RDWR, 1);
	if (semaphore == SEM_FAILED)
		return (0);
	printf("Pickup semaphore created with value %i\n", 1);
	params->pickup = semaphore;
	semaphore = sem_open("/print", O_CREAT, O_RDWR, 1);
	if (semaphore == SEM_FAILED)
		return (0);
	printf("Print semaphore created with value %i\n", 1);
	params->print = semaphore;
	return (1);
}

static int fork_philos (t_node *philos)
{
	int	first;
	t_node *curr_node;

	curr_node = philos;
	first = 1;
	while (curr_node->id != 1 || first)
	{
		if (curr_node->id == 1)
			first = 0;
		if (!init_philo_process(curr_node->philo_data))
			return (0);
		curr_node = curr_node->next;
	}
	return (1);
}

static int retreat() {
	return (-1);
}

static int	start_philo(t_params *params)
{
	t_node	*philos;

	if (!create_semaphores(params))
	{
		printf("Semaphore initialization failed\n");
		printf("Error: %i", errno);
		return (0);
	}
	philos = create_circle(params);
	if (philos == NULL)
	{
		printf("List creation failed\n");
		return (0);
	}
	sem_wait(params->pickup);
	gettimeofday(&(params->t_start), NULL);
	if (!fork_philos(philos))
	{
		retreat(); // todo
		return (-1);
	}
	sem_post(params->pickup);
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