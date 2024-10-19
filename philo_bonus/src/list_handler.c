/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:02:53 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/19 15:54:18 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_node	*create_node(unsigned int id, t_node *prev, t_params *params)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
	{
		printf("[ERROR]: Node with id %u memory allocation failed.\n", id);
		return (NULL);
	}
	node->id = id;
	node->philo_data = build_philosopher(id, params);
	if (node->philo_data == NULL)
	{
		free(node);
		return (NULL);
	}
	if (prev)
		prev->next = node;
	return (node);
}

t_node	*create_circle(t_params *params)
{
	unsigned int	i;
	t_node			*list;
	t_node			*first;

	if (params->n_philo <= 0)
		return (NULL);
	list = create_node(1, NULL, params);
	if (list == NULL)
		return (NULL);
	first = list;
	i = 2;
	while (i <= params->n_philo)
	{
		if (create_node(i++, list, params) == NULL)
		{
			cleanse_list(&list);
			return (NULL);
		}
		list = list->next;
	}
	list->next = first;
	return (first);
}

void	cleanse_list(t_node **list)
{
	t_node			*aux;

	while (*list != NULL && (*list)->next != NULL && (*list)->next->id != 1)
		*list = (*list)->next;
	while (*list != NULL)
	{
		aux = (*list)->next;
		clean_philo_data((*list)->philo_data);
		free(*list);
		*list = aux;
	}
	list = NULL;
}
