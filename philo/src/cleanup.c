/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:11:20 by sperez-s          #+#    #+#             */
/*   Updated: 2023/04/12 13:18:00 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_and_free(t_node **philos)
{
	int	first_node;

	first_node = -1;
	while ((*philos)->id != 1 || first_node == -1)
		first_node = pthread_join((*philos)->philo_data->thread, NULL);
	cleanse_list(philos);
}

void	clean_params(t_params **params)
{
	pthread_mutex_destroy(&((*params)->death_lock));
	pthread_mutex_destroy(&((*params)->print_lock));
	free(*params);
}
