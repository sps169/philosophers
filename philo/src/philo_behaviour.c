/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:12:39 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/17 21:37:35 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_behaviour(void *data)
{
	t_philo_data	*philo_data;
	t_node			*l_fork;
	t_node			*r_fork;
	unsigned int	n_meals;

	n_meals = 0;
	philo_data = (t_philo_data *)data;
	if (philo_data->id == 1)
	{
		while (n_meals < philo_data->params.n_meals)
		{
			while(philo_data->forks->id != 1)
				philo_data->forks = philo_data->forks->next;
			l_fork = philo_data->forks;
			while(philo_data->forks->id != 2)
				philo_data->forks = philo_data->forks->next;
			r_fork = philo_data->forks;
			pthread_mutex_lock(&(l_fork->fork));
			pthread_mutex_lock(&(r_fork->fork));
			printf("%i %u is eating\n",gettimeofday(NULL, NULL) - philo_data->params.t_start, philo_data->id);
			usleep(philo_data->params.t_eat);
			n_meals++;
			pthread_mutex_unlock(&(l_fork->fork));
			pthread_mutex_unlock(&(r_fork->fork));
			printf("%i %u is sleeping\n",gettimeofday(NULL, NULL) - philo_data->params.t_start, philo_data->id);
			usleep(philo_data->params.t_sleep);
			printf("%i %u is thinking\n",gettimeofday(NULL, NULL) - philo_data->params.t_start, philo_data->id);
		}
	}
	else
		printf("BONK\n");
	return (NULL);
}
