/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:14:06 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/08/07 15:50:30 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	c = 0;
	pid_t					client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (SIGUSR1 == sig)
		c = (c << 1) | 0b00000001;
	else if (SIGUSR2 == sig)
		c = c << 1;
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sig;
	pid_t				pid;

	sig.sa_sigaction = ft_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_NODEFER;
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	if (sigaction(SIGUSR1, &sig, NULL) == -1
		|| sigaction(SIGUSR2, &sig, NULL) == -1)
	{
		write(2, "sigaction error\n", 16);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
