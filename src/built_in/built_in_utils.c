/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibrahim <fibrahim@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:58:31 by fibrahim          #+#    #+#             */
/*   Updated: 2023/11/17 21:05:14 by fibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_delete_env(char *str, t_data	*g_data)
{
	t_env	*env;
	t_env	*prev;

	env = g_data->environmental;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->front, str) == 0)
		{
			if (prev == NULL)
				g_data->environmental = env->next;
			else
				prev->next = env->next;
			free_env_node(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
	free_matrix(g_data->env);
	g_data->env = ft_env_to_matrix(g_data);
}

t_env	*ft_new_env(char *str, t_data	*g_data)
{
	t_env	*env;
	t_env	*new;

	env = g_data->environmental;
	new = (t_env *)malloc(sizeof(t_env));
	new->front = ft_substr(str, 0, ft_strchr(str, '=') - str);
	new->back = ft_substr(str, ft_strchr(str, '=') - str + 1, ft_strlen(str));
	new->next = NULL;
	if (env == NULL)
		g_data->environmental = new;
	else
	{
		while (env->next)
			env = env->next;
		env->next = new;
	}
	return (new);
}

int	ft_is_valid_env(char *str, t_data	*g_data)
{
	t_env	*env;

	env = g_data->environmental;
	if (!str)
		return (0);
	while (env)
	{
		if (ft_strcmp(env->front, str) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_change_env(char *str, char *new_value, t_data	*g_data)
{
	t_env	*env;

	env = g_data->environmental;
	if (!str)
		return ;
	while (env)
	{
		if (ft_strcmp(env->front, str) == 0)
		{
			free(env->back);
			env->back = ft_strdup(new_value);
			return ;
		}
		env = env->next;
	}
}
