/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccur <ccur@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:03:18 by bcopoglu          #+#    #+#             */
/*   Updated: 2024/01/28 01:50:52 by ccur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <sys/errno.h>
#include <signal.h>

void	ft_close_pipe_fds(t_init *process)
{
	size_t	i;

	i = 0;
	while (i < (process->nr_of_cmds - 1))
	{
		if (close(process->pipes[i][0]) == -1)
			ft_throw_error(process, errno);
		if (close(process->pipes[i][1]) == -1)
			ft_throw_error(process, errno);
		i++;
	}
}

static bool	ft_infile(t_init *process, t_rdr *rdr)
{
	int32_t	temp;

	process->fdin = open(rdr->data, O_RDONLY);
	if (process->fdin == -1 || dup2(process->fdin, STDIN_FILENO) == -1 || \
		close(process->fdin) == -1)
	{
		temp = errno;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		process->errorcode = 1;
		errno = temp;
		return (perror(rdr->data), false);
	}
	return (true);
}

static void	ft_outfile(t_init *process, t_rdr *rdr)
{
	int32_t	temp;

	if (rdr->type == RDR_APPEND)
		process->fdout = open(rdr->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		process->fdout = open(rdr->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (process->fdout == -1 || dup2(process->fdout, STDOUT_FILENO) == -1 || \
		close(process->fdout) == -1)
	{
		temp = errno;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		process->errorcode = 1;
		errno = temp;
		perror(rdr->data);
	}
}

static bool	ft_check_for_heredoc(t_scmd_list *scmd, t_init *process)
{
	t_rdr	*rdr;

	while (scmd)
	{
		if (scmd->type == RDR)
		{
			rdr = scmd->data;
			if (rdr->type == HERE_DOC)
			{
				if (dup2(process->oldin, STDIN_FILENO) == -1 || \
					signal(SIGQUIT, SIG_IGN) == SIG_ERR)
					ft_throw_error(process, errno);
				if (!ft_heredoc(process, rdr->data))
				{
					signal(SIGQUIT, SIG_DFL);
					return (false);
				}
				signal(SIGQUIT, SIG_DFL);
				process->heredoc = true;
			}
		}
		scmd = scmd->next;
	}
	return (true);
}

bool	ft_check_for_files(t_scmd_list *scmd, t_init *process)
{
	t_rdr	*rdr;

	if (!ft_check_for_heredoc(scmd, process))
	{
		process->must_exit = true;
		return (false);
	}
	while (scmd)
	{
		if (scmd->type == RDR)
		{
			rdr = scmd->data;
			if (rdr->type == RDR_INPUT)
			{
				if (!ft_infile(process, rdr))
					return (false);
			}
			if (rdr->type == RDR_OUTPUT || rdr->type == RDR_APPEND)
				ft_outfile(process, rdr);
		}
		scmd = scmd->next;
	}
	return (true);
}
