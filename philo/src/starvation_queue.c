/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starvation_queue.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:28:22 by sperez-s          #+#    #+#             */
/*   Updated: 2023/09/19 15:23:09 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_starve_node	*create_starve_node(unsigned int death_ms, t_philo_data *data)
{
	t_starve_node	*new;

	new = NULL;
	new = malloc(sizeof(t_starve_node));
	if (new == NULL)
		return (NULL);
	new->death_ms = death_ms;
	new->philo = data;
	new->next = NULL;
	return (new);
}

int	add_starve_node(unsigned int death_ms, t_philo_data *data)
{
	t_starve_node	*curr;
	t_starve_node	*new;

	new = NULL;
	curr = NULL;
	new = create_starve_node(death_ms, data);
	if (new == NULL)
		return (0);
	pthread_mutex_lock(&data->params->starve_queue_lock);
	curr = data->params->starve_queue;
	while (curr != NULL && curr->next != NULL)
		curr = curr->next;
	if (curr == NULL)
		data->params->starve_queue = new;
	else
		curr->next = new;
	pthread_mutex_unlock(&data->params->starve_queue_lock);
	return (-1);
}

t_starve_node	*get_next_starve_node(t_params *params)
{
	t_starve_node	*node;

	node = NULL;
	pthread_mutex_lock(&(params->starve_queue_lock));
	pthread_mutex_lock(&(params->satisfaction_lock));
	pthread_mutex_lock(&(params->death_lock));
	while (params->starve_queue == NULL && params->death == 0
		&& (params->n_meals == 0 || (params->n_meals != 0
				&& params->n_satisfied < params->n_philo)))
	{
		pthread_mutex_unlock(&(params->death_lock));
		pthread_mutex_unlock(&(params->satisfaction_lock));
		pthread_mutex_unlock(&(params->starve_queue_lock));
		usleep(1000);
		pthread_mutex_lock(&(params->starve_queue_lock));
		pthread_mutex_lock(&(params->satisfaction_lock));
		pthread_mutex_lock(&(params->death_lock));
	}
	node = params->starve_queue;
	if (params->starve_queue != NULL)
		params->starve_queue = params->starve_queue->next;
	pthread_mutex_unlock(&(params->starve_queue_lock));
	pthread_mutex_unlock(&(params->satisfaction_lock));
	pthread_mutex_unlock(&(params->death_lock));
	return (node);
}

void	erase_queue(t_params params)
{
	t_starve_node	*node;

	node = NULL;
	pthread_mutex_lock(&params.starve_queue_lock);
	while (params.starve_queue != NULL)
	{
		node = params.starve_queue;
		params.starve_queue = params.starve_queue->next;
		free(node);
	}
	pthread_mutex_unlock(&params.starve_queue_lock);
}
