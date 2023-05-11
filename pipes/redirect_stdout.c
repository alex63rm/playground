/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stdout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:58:41 by alejarod          #+#    #+#             */
/*   Updated: 2023/05/11 20:58:21 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	int pid;
	int err;

	pid = fork();
	if (pid == -1)
		return (1);

	if (pid == 0)
	{
		// child process
		// open a file or create it if it does not exist to save the output of execlp, give it the correct permissionis in octal value
		int fd = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
		if (fd == -1)
			return (3);
				/*
		we duplicate 3 in 1
		0 stdin
		1 stdout ---> replaced by pingResults.txt
		2 stderr
		3 pingResults.txt
		*/
		dup2(fd, STDOUT_FILENO);	// replaces number 1 stdout with fd
		close(fd);							// close 3

		err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
		{
			printf("Could not find program to execute\n");
			return (2);
		}

	}
	// here the parent still executes code
	else
	{
		wait(NULL);	/* wait for the child to finish (remember that they execute
		in parallel and could overlap the child */
		printf("some other lines go here\n");
	}


	printf("success. Process ended\n");
	return (0);
}