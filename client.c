/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:56:21 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/07/07 22:28:50 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_listen = 1;

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (SIGUSR1 == sig)
		g_listen = 0;
}

/**
 * @brief It sends a signal to the server and waits a response from it.
 * 	When the response arrives, it changes the status of the global var
 * 	from "listen" (1) to "continue doing your things (send next bit)" (0)
 * 
 * @param pid 
 * @param bit 
 * @param c 
 */
void	ft_kill_signal(int pid, int bit, char c)
{
	while (bit < 8)
	{
		g_listen = 1;
		if ((c << bit) & 0b10000000)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit++;
		while (g_listen)
			usleep(1);
	}
}

void	ft_signal_action(int pid, char *str)
{
	int	bit;
	int	c;

	bit = 0;
	while (*str)
	{
		c = *str;
		ft_kill_signal(pid, bit, c);
		bit = 0;
		str++;
	}
	bit = 0;
	c = '\n';
	ft_kill_signal(pid, bit, c);
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;
	int					pid;

	sig.sa_sigaction = ft_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
	{
		write(2, "Sigaction error\n", 16);
		exit(EXIT_FAILURE);
	}	
	if (argc != 3)
	{
		printf("Please write PID & String\n");
		exit(EXIT_FAILURE);
	}	
	pid = atoi(argv[1]);
	ft_signal_action(pid, argv[2]);
	return (0);
}
