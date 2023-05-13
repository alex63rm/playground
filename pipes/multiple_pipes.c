/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:30:34 by alejarod          #+#    #+#             */
/*   Updated: 2023/05/12 22:30:15 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int	main(void)
{
	// we are going to communicate 3 pipes in a circle (see multiple_pipes.png)
	// we create 3 fd of size 2 (0,1), totaling 6 (see arrays.c for example of matrix)
	int	fd[3][2];
	/*
		j j
	i [0, 1] --> pipe 0
	i [0, 1] --> pipe 1
	i [0, 1] --> pipe 2

	or [[0,1], [0,1], [0,1]]
	or [
		[0,1],
		[0,1],
		[0,1]
		]
	*/
	int i = 0;

	// generate 3 pipes;
	for (i = 0; i < 3; i++)
		if (pipe(fd[i]) < 0)
			return (1);

	int pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		/* child process 1
		in this first child:
		parent gets paused, it is not going to write
		child is going read ---> need fd[0][0] open
		child is going to write ---> need fd[1][1] open
		close the other ends fd[0][1] and fd[1][0] */
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);	// this proccess is not going to use the 2nd pipe, we can close it
		close(fd[2][1]);
		int x;
		if (read(fd[0][0], &x, sizeof(int)) < 0)
			return (3);
		x += 5;				// this is the instruction executed by the child
		if (write(fd[1][1], &x, sizeof(int)) < 0)
			return (4);
		// close the file descriptors after doing the work
		close(fd[0][0]);
		close(fd[1][1]);
		// VERY IMPORTANT TO END THE PROCESS WHEN THE WORK IS DONE
		// IF WE DON'T END IT AND MAKE ANOTHER FORK, THIS PROCESS ALSO GETS FORKED
		return (0);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return (5);
	if (pid2 == 0)
	{
		// child2
		// we need to read from fd[1][0]
		// we need to write to fd[2][1]
		// close what we don't need
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		int x;
		if (read(fd[1][0], &x, sizeof(int)) < 0)
			return (6);
		x += 5;
		if (write(fd[2][1], &x, sizeof(int)) < 0)
			return (7);
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);

	}
	// parent process
	// we need to read from fd[2][0] and write fd[0][1]
	// close unused fds
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	int x;
	printf("input a number: ");
	scanf("%d", &x);
	// the PARENT process first writes x and then reads.
	// When the process starts, there is nothing to read, so it starts writing

	if (write(fd[0][1], &x, sizeof(int)) < 0)
		return (8);
	if (read(fd[2][0], &x, sizeof(int)) < 0)
		return (9);
	printf("Result is %d\n", x);
	close(fd[0][1]);
	close(fd[2][0]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}