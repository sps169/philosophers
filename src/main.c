/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:43:10 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/16 18:08:21 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks(void)
{
	system("leaks philo");
}

static void	*thread_fun()
{
	printf("Hola hilo!\n");
	return (NULL);
}

static void	start_philo(int n_philo, int t_die, int t_sleep, int t_eat, int n_meals)
{
	t_node		*forks;
	pthread_t	thread_id;

	atexit(leaks);
	(void)t_die;
	(void)t_sleep;
	(void)t_eat;
	(void)n_meals;
	forks = create_fork_circle(n_philo);
	if (forks != NULL)
	{
		print_list(forks);
		cleanse_list(&forks);
		pthread_create(&thread_id, NULL, thread_fun, NULL);
	}
	else
		printf("List creation failed\n");
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int	n_philo;
	int	t_die;
	int	t_sleep;
	int	t_eat;
	int	n_meals;

	n_philo = 3;
	t_die = 200;
	t_sleep = 50;
	t_eat = 50;
	n_meals = -1;
	start_philo(n_philo, t_die, t_sleep, t_eat, n_meals);
	return (0);
}
