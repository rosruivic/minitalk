/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_fd_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:11:29 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/06/09 17:30:11 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putuint_fd_len(unsigned int n, int fd, int *len)
{
	if (n < 0)
		n = n + 4294967296;
	if (n > 9)
		ft_putuint_fd_len(n / 10, fd, len);
	ft_putchar_fd_len(48 + (n % 10), fd, len);
}
