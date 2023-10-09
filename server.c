/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 01:14:32 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/07/09 17:19:04 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

/**
 * @brief By a sig.sa_sigaction struct, we assign to it a pointer
 * 	to ft_handler.
 *  	- sigemptyset(&sig.sa_mask)	creates a void group of signals, to
 * 			be safe that there isn't aditional blocked signals while the
 * 			signal controller are executing; it avoids unexpected
 * 			interruptions and allows a correct handle of the specific
 * 			signal that are being configured with sigaction.
 * 		- SA_SIGINFO is a const that is saying that we want to use the
 * 			most recent and complex function of signal handler;
 * 			in other words, the 3 arguments sigaction function
 * 						"void (*sa_sigaction)(int, siginfo_t *, void *)"
 * 			instead of the older 2 arguments
 * 						"void (*sa_handler)(int)"
 * 		- SA_NODEFER, instead: if this bit is set, further occurrences of
 * 			the delivered signal are not masked during the execution of the
 * 			handler.
 * @return int
 */
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
