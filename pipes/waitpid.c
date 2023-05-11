/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:22:00 by alejarod          #+#    #+#             */
/*   Updated: 2023/05/11 21:39:44 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main(void)
{
	int process = getpid();
	printf("parent pid is: (%d)\n", process);
	int pid = fork();
	if (pid == -1)
		return (1);

	// enter child
	if (pid == 0)
	{
		sleep(4);
		printf("Finished execution (%d)\n", getpid());
		return (0);		// this return closes the process
	}

	int pid2 = fork();
	if (pid2 == -1)
		return (2);

	// enter second child
	if (pid2 == 0)
	{
		sleep(1);
		printf("Finished execution (%d)\n", getpid());
		return (0);
	}

	// if we want to wait for a specific process

	int pid1_res = waitpid(pid, NULL, 0);
	printf("Waited for %d\n", pid1_res);
	int	pid2_res = wait(NULL);
	printf("Waited for %d\n", pid2_res);
	return (0);
}