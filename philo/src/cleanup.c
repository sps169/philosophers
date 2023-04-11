/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:11:20 by sperez-s          #+#    #+#             */
/*   Updated: 2023/04/11 19:00:39 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_and_free(t_node **philos)
{
	while ((*philos)->next->id != 1)
		pthread_join((*philos)->philo_data->thread, NULL);
	cleanse_list(philos);
}

void	clean_params(t_params **params)
{
	pthread_mutex_destroy(&((*params)->death_lock));
	pthread_mutex_destroy(&((*params)->print_lock));
	free(*params);
}
