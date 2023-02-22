/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:11:20 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/22 12:20:40 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo_data **philos, int last_philo)
{
	int	i;

	i = 0;
	while(i <= last_philo)
	{
		free(philos[i]);
		i++;
	}
}

void	wait_and_free(t_node **forks, t_philo_data **philos, int last_philo)
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

void	clean_params(t_params **params)
{
	pthread_mutex_destroy(&((*params)->death_lock));
	pthread_mutex_destroy(&((*params)->print_lock));
	free(*params);
}
