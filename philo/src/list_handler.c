/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:02:53 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/20 13:20:42 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_node	*create_node(unsigned int id, t_node *prev, t_node *next)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
	{
		printf("[ERROR]: Node with id %u memory allocation failed.\n", id);
		return (NULL);
	}
	node->id = id;
	if (pthread_mutex_init(&(node->fork), NULL) != 0)
	{
		printf("[ERROR]: Node with id %u mutex initialization failed\n", id);
		return (NULL);
	}
	node->prev = prev;
	node->next = next;
	if (node->prev != NULL)
		node->prev->next = node;
	return (node);
}

t_node	*create_fork_circle(int n_philo)
{
	int		i;
	t_node	*list;
	t_node	*first;

	if (n_philo <= 0)
		return (NULL);
	list = create_node(1, NULL, NULL);
	first = list;
	i = 2;
	while (i <= n_philo)
	{
		if (create_node(i++, list, NULL) == NULL)
		{
			cleanse_list(&list);
			return (NULL);
		}
		list = list->next;
	}
	list->next = first;
	first->prev = list;
	return (first);
}

void	cleanse_list(t_node **list)
{
	t_node			*aux;

	aux = NULL;
	while(*list != NULL && (*list)->next != NULL && (*list)->next->id != 1)
		*list = (*list)->next;
	while (*list != NULL)
	{
		aux = (*list)->prev;
		if ((*list)->next != NULL)
			(*list)->next->prev = NULL;
		if ((*list)->prev != NULL)
			(*list)->prev->next = NULL;
		pthread_mutex_destroy(&((*list)->fork));
		free(*list);
		*list = aux;
	}
	list = NULL;
}

void	print_list(t_node *list)
{
	int	printed;

	printed = 0;
	while (list != NULL && printed == 0)
	{
		if (list->prev != NULL)
			printf("%u", list->prev->id);
		else
			printf("NULL");
		printf("<-[%u]->",list->id);
		if (list->next != NULL)
			printf("%u\n", list->next->id);
		else
			printf("NULL\n");
		if (list->next && list->next->id != 1)
			list = list->next;
		else
			printed = 1;
	}
}
