/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibrahim <fibrahim@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:58:31 by fibrahim          #+#    #+#             */
/*   Updated: 2023/11/17 21:06:38 by fibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_expand	*ft_add_tail_expander(t_expand *head, char *str)
{
	t_expand	*temp;
	t_expand	*new;

	temp = NULL;
	new = NULL;
	temp = head;
	new = (t_expand *)malloc(sizeof(t_expand));
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (NULL);
	new->next = NULL;
	if (!(head))
		head = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (head);
}

char	*ft_search_env(char *splitted_input, t_data *g_data)
{
	char	*str;
	t_env	*tmp;

	str = NULL;
	tmp = NULL;
	tmp = g_data->environmental;
	if (!splitted_input || *splitted_input == '\0')
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(splitted_input, tmp->front,
				ft_strlen(splitted_input)) == 0)
		{
			str = ft_strdup(tmp->back);
			return (str);
		}
		tmp = tmp->next;
	}
	return (str);
}

int	i_x(char c, char x)
{
	return ((c == '$' && (ft_isalnum(x) || x == '?')));
}

int	is_in_single_quote(char *str, int indx)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (i < indx)
	{
		if (str[i] == '\'')
			flag++;
		i++;
	}
	if (flag && flag % 2 == 0)
		return (0);
	else if (ft_strchr(str + indx + 1, '\'') != 0)
		return (1);
	return (0);
}
