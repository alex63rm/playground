/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:05:01 by alejarod          #+#    #+#             */
/*   Updated: 2023/05/11 21:15:22 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int	main(void)
{
	int pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		while (1)
		{
			// infinite loop
			printf("Some text here\n");
			usleep(50000);
		}
	}
	else
	{
		sleep(1);
		kill(pid, SIGKILL);		// kill does not kill, it will check the argument and run it in the pid
		wait(NULL);
	}
	return (0);
}