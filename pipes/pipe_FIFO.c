/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_FIFO.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:15:22 by alejarod          #+#    #+#             */
/*   Updated: 2023/05/09 20:56:09 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

/* pipes can only be used by processes that are in the same jerarchy
for this, there is the FIFO, it is a file type from where we can read
or write from any other process, even if it is not related
FIFO is a special time of file. It can be created here or in linux it
has its own CLI command: mkfifo <filename>
*/
int	main(void)
{
	if (mkfifo("myfifo1", 0777) == -1)	// creates a file chmod 777 in octal base
	{
		if (errno != EEXIST)
		{
			printf("could not create file\n");
			return (1);
		}
	}
	printf("opening...\n");

	/*
	Opening the read or write end of a FIFO file pauses/blocks the current program until the other end is also
	opened by another process or thread.
	The program gets stuck here, so we need to run another process in anotehr terminal (cat fifo) for this program to continue
	*/
	int fd = open("myfifo1", O_WRONLY);		// returns a file descriptor to the file. Note that if we opened in O_RDWR it will terminate,
	// because we are reading and writing at the same time
	printf("fd is: | %d |\n", fd);
	printf("opened...\n");

	int x = 97;
	if (write(fd, &x, sizeof(x)) == -1)
		return (2);
	printf("written...\n");

	close(fd);
	printf("closed...\n");



	return (0);
}