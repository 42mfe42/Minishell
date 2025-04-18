/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_ensure_buffer_capacity.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:18:08 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 20:18:23 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/process_env_utils.h"

int	ensure_buffer_capacity(t_env_state *state, int extra_length)
{
	int		current_length;
	int		new_length;
	char	*new_result;

	current_length = state->result_size;
	if (state->res_index + extra_length >= current_length)
	{
		new_length = current_length * 2 + extra_length;
		state->result_size = new_length + 1;
		new_result = malloc(new_length + 1);
		if (!new_result)
		{
			free(state->result);
			perror("Memory allocation failed");
			errno = ENOMEM;
			return (-1);
		}
		ft_strlcpy(new_result, state->result, current_length + 1);
		free(state->result);
		state->result = new_result;
	}
	return (0);
}

int	try_ensure_buffer_capacity(t_env_state *state, int extra_length, char c)
{
	if (ensure_buffer_capacity(state, extra_length) == 0)
		state->result[state->res_index++] = c;
	else
		return (-1);
	return (0);
}
