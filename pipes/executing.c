/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:58:41 by alejarod          #+#    #+#             */
/*   Updated: 2023/05/11 19:50:14 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	//execlp("ping", "ping", "-c", "3", "google.com", NULL);
	/* 1. this process is replacing the whole process, it is being replaced by
	execution line (printf will not be called)
	Note that if it cannot be executed for some reason, it will not replace the
	current process and the program will continue */

	int pid;
	int err;

	// 2. to avoid this, we are going to create a fork
	pid = fork();	// two processes will run in parallel
	if (pid == -1)
		return (1);
	/* 3. ORDER is important. Execution processes should be run in the child,
	so that the parent process is not replaced and the program can continue
	after executing the child */
	if (pid == 0)
	{
		// child process
		/* execlp receives a variable list of arguments (like printf), so we
		have to end the parameters in NULL to indicate there are no more */
		err = execlp("pingr", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
		{
			printf("Could not find program to execute\n");
			return (2);
		}

		// whatever we do here gets replaced by the execlp, it will never run
		printf("this never gets printed");
	}
	// here the parent still executes code
	else
	{
		wait(NULL);	/* wait for the child to finish (remember that they execute
		in parallel and could overlap the child */
		printf("some other lines go here\n");
	}

	//execlp("ping", "ping", "-c", "3", "google.com", NULL);
	/* 1. this process is replacing the whole process, it is being replaced by \
	execution line (printf will not be called) */
	printf("success. Process ended\n");
	return (0);	// this is a status code.
}