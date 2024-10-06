/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:27:34 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/06 18:12:18 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_semaphores (t_params *params)
{
	sem_t	*semaphore;

	if (sem_unlink("forks"))
		return(0);
	if (sem_unlink("pickup"));
		return(0);
	semaphore = sem_open("forks", O_CREAT, O_RDWR, params->n_philo);
	if (semaphore == SEM_FAILED)
		return (0);
	params->forks = semaphore;
	semaphore = sem_open("pickup", O_CREAT, O_RDWR, 1);
	if (semaphore == SEM_FAILED)
		return (0);
	params->pickup = semaphore;
	return (1);
}

static int	start_philo(t_params *params)
{
	t_node	*philos;

	if (!create_semaphores(params))
	{
		printf("Semaphore initialization failed\n");
		return (0);
	}
	philos = create_circle(params);
	if (philos == NULL)
	{
		printf("List creation failed\n");
		return (0);
	}
	gettimeofday(&(params->t_start), NULL);
	wait_and_free(&philos);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_params	*params;
	sem_t	*semaphore;

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