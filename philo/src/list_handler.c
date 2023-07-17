/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:02:53 by sperez-s          #+#    #+#             */
/*   Updated: 2023/07/17 19:24:42 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_node	*create_node(unsigned int id,
	t_node *prev, t_node *next, t_params *params)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
	{
		printf("[ERROR]: Node with id %u memory allocation failed.\n", id);
		return (NULL);
	}
	node->id = id;
	node->philo_data = create_philosopher(id, params, prev);
	if (node->philo_data == NULL)
	{
		free(node);
		return (NULL);
	}
	node->prev = prev;
	node->next = next;
	if (node->prev != NULL)
		node->prev->next = node;
	return (node);
}

t_node	*create_circle(t_params *params)
{
	unsigned int	i;
	t_node			*list;
	t_node			*first;

	if (params->n_philo <= 0)
		return (NULL);
	list = create_node(1, NULL, NULL, params);
	if (list == NULL)
		return (NULL);
	first = list;
	i = 2;
	while (i <= params->n_philo)
	{
		if (create_node(i++, list, NULL, params) == NULL)
		{
			printf("Cleansing \n");
			cleanse_list(&list);
			return (NULL);
		}
		list = list->next;
	}
	list->next = first;
	first->prev = list;
	first->philo_data->l_fork = first->prev->philo_data->r_fork;
	return (first);
}

void	cleanse_list(t_node **list)
{
	t_node			*aux;

	aux = NULL;
	while (*list != NULL && (*list)->next != NULL && (*list)->next->id != 1)
		*list = (*list)->next;
	while (*list != NULL)
	{
		if ((*list)->prev != *list)
			aux = (*list)->prev;
		if ((*list)->next != NULL)
			(*list)->next->prev = NULL;
		if ((*list)->prev != NULL)
			(*list)->prev->next = NULL;
		pthread_mutex_destroy(((*list)->philo_data->r_fork));
		pthread_mutex_destroy(((*list)->philo_data->n_meals_mutex));
		free((*list)->philo_data->r_fork);
		free((*list)->philo_data->n_meals_mutex);
		free((*list)->philo_data);
		free(*list);
		*list = aux;
	}
	list = NULL;
}
