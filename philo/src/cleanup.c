/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:11:20 by sperez-s          #+#    #+#             */
/*   Updated: 2023/09/13 12:34:42 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_and_free(t_node **philos)
{
	int		first_node;
	t_node	*curr_node;

	curr_node = *philos;
	first_node = -1;
	while (curr_node->id != 1 || first_node == -1)
	{
		first_node = pthread_join(curr_node->philo_data->thread, NULL);
		curr_node = curr_node->next;
	}
	erase_queue(*(*philos)->philo_data->params);
	cleanse_list(philos);
}

void	clean_params(t_params **params)
{
	pthread_mutex_destroy(&((*params)->death_lock));
	pthread_mutex_destroy(&((*params)->print_lock));
	pthread_mutex_destroy(&((*params)->meal_lock));
	pthread_mutex_destroy(&((*params)->kick_off_lock));
	pthread_mutex_destroy(&((*params)->satisfaction_lock));
	pthread_mutex_destroy(&((*params)->starve_queue_lock));
	free(*params);
}

void	clean_philo_data(t_philo_data **data)
{
	pthread_mutex_destroy(((*data)->r_fork));
	pthread_mutex_destroy(((*data)->n_meals_mutex));
	pthread_mutex_destroy(((*data)->last_meal_mutex));
	free(((*data)->r_fork));
	free(((*data)->n_meals_mutex));
	free(((*data)->last_meal_mutex));
	free(data);
}
