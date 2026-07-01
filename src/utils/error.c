/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:18:48 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/01 16:27:56 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <unistd.h>

void	print_error(const char *msg)
{
	if (msg == NULL)
		return ;
	(void)write(STDERR_FILENO, msg, ft_strlen(msg));
	(void)write(STDERR_FILENO, "\n", 1);
}
