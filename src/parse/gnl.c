/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 14:44:30 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/10 15:33:31 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// temporary substitute
char	*get_next_line(int fd)
{
	char		*line;
	size_t		len;
	ssize_t		read;
	static FILE	*fp = NULL;

	if (fp == NULL)
	{
		fp = fdopen(fd, "r");
		if (fp == NULL)
			return (NULL);
	}
	line = NULL;
	len = 0;
	if ((read = getline(&line, &len, fp)) != -1)
		return (line);
	free(line);
	fclose(fp);
	fp = NULL;
	return (NULL);
}
