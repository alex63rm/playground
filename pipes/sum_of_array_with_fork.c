/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:33:43 by alejarod          #+#    #+#             */
/*   Updated: 2023/05/08 21:50:16 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


int main(void)
{
	// we want to divide the array in 2, sum them with 2 processes at the same
	// time and then add them together through a pipe

	int	arr[] = {1, 2, 3, 4, 1, 2};			// array that we want to add

	// len of the array
	int len = sizeof(arr) / sizeof(int);

	int	fd[2];								// array for the pipe
	// pedantic: it appears that pipe returns an array of 2 file descriptors
	// that will be saved in the argument array.
	if (pipe(fd) == -1)
		return (1);

	int	id = fork();	// create another process: duplicates the current program/process

	if (id == -1)
		return (2);

	// the process needs to know where to start and where to end
	int	start;
	int	end;

	// if id == 0 it means we are in the child process
	// child process will do the first half
	// REMEMBER: Both processes will run simultaneously!
	if (id == 0)
	{
		start = 0;
		end = len / 2;
	}
	else   // this is the parent process, will do the second half
	{
		start = len / 2;
		end = len;
	}

	int sum = 0;
	int i = start;
	while (i < end)
	{
		sum = sum + arr[i];
		printf("process is: %d\n", id);
		i++;
	}
	// the result may not be in order, because they are executing paralelly
	// see that all the printfs are getting printed by duplicate, because the
	// program is getting executed twice
	printf("calculated partial sum: %d\n", sum);
	printf("fd read is %d\n", fd[0]);
	printf("fd write is %d\n", fd[1]);

	// now we are going to join the two results with a pipe
	// remember that they execute in paralell
	//THEY ARE INTERCHANGEABLE, meaning id !=0 runs the parent first
	if (id == 0)
	{
		close(fd[0]); // we are not reading anything in the child, just writing
		// remember the format of write: (int to write (default is 1 stdout, 2 is stderr, other number for fd))
		int error = write(fd[1], &sum, sizeof(sum));
		//just to check
		if (error == -1)
			return (3);
		close(fd[1]); // close after reading
	}
	else
	{
		int	sumFromChild;
		close(fd[1]); // we are not going to write, just read
		if (read(fd[0], &sumFromChild, sizeof(sumFromChild)) == -1)
			return (4);
		close(fd[0]);

		int totalSum = sum + sumFromChild;
		printf("Total sum is %d\n", totalSum);
		wait(NULL);	// wait for the child process to finish, i.e. don't
		// read until the child has written the data

	}


	return (0);
}
