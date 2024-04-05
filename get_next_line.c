/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:42:52 by jseidere          #+#    #+#             */
/*   Updated: 2023/11/30 16:10:09 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"

char	*return_function(int index, char **stash)
{
	char		*result;
	size_t		len;

	if (!*stash)
		return (NULL);
	if (index <= 0)
	{
		if (**stash == 0 || index < 0)
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		result = *stash;
		*stash = NULL;
		return (result);
	}
	len = ft_strlen(*stash) - index;
	result = *stash;
	*stash = ft_substr(*stash, index, len);
	result[index] = '\0';
	return (result);
}

char	*get_line(char **stash, char *buffer, int fd)
{
	char	*new_stash;
	char	*result;
	char	*next_line;
	ssize_t	bytesread;

	next_line = ft_strchr(*stash, '\n');
	while (next_line == NULL)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread <= 0)
			return (return_function(bytesread, stash));
		buffer[bytesread] = '\0';
		new_stash = ft_strjoin(*stash, buffer);
		free(*stash);
		*stash = new_stash;
		next_line = ft_strchr(*stash, '\n');
	}
	result = return_function(next_line - *stash + 1, stash);
	return (result);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(buffer));
	if (!buffer)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	result = get_line(&stash, buffer, fd);
	free(buffer);
	return (result);
}
#include <stdio.h>
int main()
{
	int i = 1;

	int fd = open("text.txt", O_RDONLY);
	
	if (fd < 0)
	{
		perror("Fehler beim Öffnen der Datei");
		return 1;
	}

	char *line;
	
	while (i <= 12)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("%d = %s\n", i, line);
			free(line);
		}
		else
		{
			printf("%d = Zeile nicht verfügbar\n", i);
		}
		printf("________________________\n");
	i++;
	}
	close(fd);
	return 0;
}
/* int main ()
{
	int fd;
	//char *test = get_buffer(fd);
	
	fd = open ("text.txt", O_RDONLY);
	
	//test = get_next_next_line(fd);
	printf("1 = %s\n", get_next_next_line(fd));
	printf("________________________\n");
	printf("2 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	printf("3 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	printf("4 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	printf("5 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	printf("6 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	printf("7 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	printf("8 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	printf("9 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	printf("10 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	printf("11 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	printf("12 = %s\n", get_next_next_line(fd));
	 printf("________________________\n");
	//printf("%s\n", get_next_next_line(fd));

	close (fd);

	//return (0);
} */
