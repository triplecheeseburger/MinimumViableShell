/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvs_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:14:49 by hakim             #+#    #+#             */
<<<<<<<< HEAD:minishell/src/parse_user_input/mvs_split_utils.c
/*   Updated: 2022/03/01 14:23:18 by jaemoojung       ###   ########.fr       */
========
/*   Updated: 2022/03/06 21:33:45 by hakim            ###   ########.fr       */
>>>>>>>> main:minishell/src/utils/mvs_split_utils.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	m_is_space(char c)
{
	if (c == SPACE)
		return (true);
	return (false);
}

bool	m_is_quote(char c)
{
	if (c == SQUOTE || c == DQUOTE)
		return (true);
	return (false);
}

void	ft_free_split(char **splitted, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(splitted[i]);
		splitted[i] = 0;
		++i;
	}
	free(splitted);
	splitted = 0;
}
