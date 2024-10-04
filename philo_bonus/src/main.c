/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:27:34 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/04 20:40:33 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_child(int i, sem_t *sem)
{
	int	pid;
	int	wstatus;

	pid = fork();
	if (pid == 0)
	{
		
	}
	else
	{
		waitpid(pid, &wstatus, 0);
	}
}

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	sem_t	*semaphore;
	int		n_philo = 5;

	sem_unlink("Forks");
	semaphore = sem_open("Forks", O_CREAT, O_RDWR, n_philo);
	if (semaphore == SEM_FAILED)
		write(1, "Ding dong\n", 10);
	int	i;
	i = 0;
	while (i < n_philo)
	{
		create_child(i + 1, semaphore);
		i++;
	}
	sem_close(semaphore);
	return (0);
}