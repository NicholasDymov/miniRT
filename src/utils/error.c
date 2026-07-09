/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:18:48 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/09 15:31:45 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_string.h"
#include <unistd.h>

static void	print_error(int fd, const char *prefix, const char *error,
		const char *context)
{
	if (prefix != NULL)
		(void)write(fd, prefix, ft_strlen(prefix));
	if (error != NULL)
		(void)write(fd, error, ft_strlen(error));
	if (context != NULL)
	{
		(void)write(fd, ": ", 2);
		(void)write(fd, context, ft_strlen(context));
	}
	(void)write(fd, "\n", 1);
}

t_error	err_msg(t_error error, const char *message)
{
	static const char *const	messages[ERR_MAX] = {
	[ERR_NO_FILE] = "You must provide a scene description in .rt file",
	[ERR_NO_CAM] = "No camera provided",
	[ERR_NO_LIGHT] = "No light provided",
	[ERR_NO_AMB] = "No ambient light provided",
	[ERR_EXTRA_CAM] = "More than one camera provided",
	[ERR_EXTRA_LIGHT] = "More than one light provided",
	[ERR_EXTRA_AMB] = "More than one ambient light provided",
	[ERR_TYPE] = "Invalid type indentifier",
	[ERR_COORD] = "Invalid coordinates",
	[ERR_RGB] = "RGB colors must be integers in the range [0, 255]",
	[ERR_FOV] = "FOV must be an integer in the range (0, 180)",
	[ERR_AMB] = "Ambient lighting ratio must be in the range [0.0, 1.0]",
	[ERR_LIGHT] = "Light brightness ratio must be in the range [0.0, 1.0]",
	[ERR_NORM] = "Normalized vector coordinates must be in range [0.0, 1.0]",
	[ERR_VEC] = "Vector must be normalized",
	[ERR_PARSE] = "Parse error near",
	};

	if (error < 0 || error >= ERR_MAX || messages[error] == NULL)
		print_error(STDERR_FILENO, NULL, message, NULL);
	else if (error != OK)
		print_error(STDERR_FILENO, "Error\n", messages[error], message);
	return (error);
}
