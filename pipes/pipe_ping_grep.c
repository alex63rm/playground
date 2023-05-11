/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:51:44 by alejarod          #+#    #+#             */
/*   Updated: 2023/05/09 20:15:07 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

// we want to simulate ping -c 5 google.com | grep rtt
/* Logic: If we want our program to run 2 processes before reaching the
return (0) of the main, we need to run them in paralel inside (with forks)
and also replace STDOUT with our fd.  We will duplicate the output of ping from stdout to fd[1]-write
and it will be read by grep from fd[0] and then finally sent to stdout (2)
*/

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	// as usual create an array
	int fd[2];

	// create the pipe and check if it was not able to be created
	if (pipe(fd) == -1)
		return (1);

	printf("fd[0] is %d\n", fd[0]);
	printf("fd[1] is %d\n", fd[1]);

	// we need to create 2 processes
	int pid1 = fork();

	// if we are in the child
	if (pid1 < 0)
		return (2);
	if (pid1 == 0) // this child has its own STDIN and STDOUT
	{
		// child process 1 (execute the ping)
		// execlp easier than execv (execlp reads all the programs from the $PATH and can receive all the arguments one by one, whereas in execv
		// we need to specify the relative path and send an array of args as arguments)

		// if we want to redirect the output, we have to do it before executing the process
		// duplicate the output from SDTOUT_FILENO (which is 1 for stdout) to fd[1] (write end of the pipe)
		// Replace STDOUT_FILENO (1) with fd[1] which is 3. We are sending the output to fd = 3 instead of the screen (fd = 1)
		printf("stdout before dup2: %d", STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		// now we overwrote STDOUT with 3, so we dont see it in the screen (which is 1)
		printf("stdout after dup2: %d", STDOUT_FILENO);
		close(fd[1]); // Close the swe have already duplicate it, we don't need it
		close(fd[0]); // we dont use the read end of this array
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	else
	{
		// note that the child process got replaced by the "ping" program
		printf("no need for else\n");
	}
	// this is the parent again

	// grep
	int pid2 = fork();
	if (pid2 < 0)
		return (3);

	if (pid2 == 0)
	{
		// child process grep
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]); // grep does not need to write, just read
		close(fd[0]); // already duplicate to stdin
		execlp("grep", "grep", "rtt", NULL);
	}

	// we also need to close the 0 and 1 read and write of the main (parent) process
	// otherwise, the child still tries to keep reading because there is a read end open
	// good practice, always close what we don't use
	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("stdout in parent: %d\n", STDOUT_FILENO);

	return (0);
}