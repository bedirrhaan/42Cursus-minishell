/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibrahim <fibrahim@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:58:31 by fibrahim          #+#    #+#             */
/*   Updated: 2023/11/17 21:05:46 by fibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	ft_exit_ut(t_block *cmd)
{
	int	j;

	j = 0;
	if (!(cmd->args[1][0] == '+' && cmd->args[1][0] == '-')
			&& ft_isdigit(cmd->args[1][0]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_blocks(cmd);
		exit(255);
	}
	else
	{
		j = ft_atoi(cmd->args[1]);
		free_blocks(cmd);
		exit(j);
	}
}

int	ft_exit_b(t_block *cmd, t_data	*g_data)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	free_string(g_data->default_prompt);
	free_env(g_data->environmental);
	free_matrix(g_data->env);
	free_exp(g_data->exp);
	free_pipes(g_data->fd_pipe, g_data->block_cnt);
	free(g_data);
	if (i == 1)
	{
		free_blocks(cmd);
		exit(0);
	}
	else if (i == 2)
		ft_exit_ut(cmd);
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		free_blocks(cmd);
		exit(1);
	}
	return (0);
}
