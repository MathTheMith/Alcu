/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/29 18:08:23 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include <stdlib.h>
#include <stdbool.h>

static void	remove_items(t_board *board, int answer)
{
	board->heaps[board->nb_heap - 1] -= answer;
	if (board->heaps[board->nb_heap - 1] == 0)
		board->nb_heap--;
	fill_board(board);
	print_board(board);
}

static bool	player_turn(t_board *board, int fd, bool *play_turn)
{
	char	*answer;

	write(1, "Choose between 1 and 3 items\n",
		ft_strlen("Choose between 1 and 3 items\n"));
	answer = readline_(fd);
	if (!answer)
		return (false);
	if (ft_atoi(answer) < 1 || ft_atoi(answer) > 3
		|| ft_atoi(answer) > board->heaps[board->nb_heap - 1] || ft_strlen(answer) != 1)
	{
		write(1, answer, ft_strlen(answer));
		write(1, " - Invalid choice\n", 18);
		*play_turn = !(*play_turn);
	}
	else
	{
		board->player_nb = ft_atoi(answer);
		remove_items(board, ft_atoi(answer));
	}
	free(answer);
	return (true);
}

void	launch_game(t_board *board, int fd)
{
	bool	play_turn;
	
	board->player_nb = -1;
	play_turn = false;
	while (1)
	{
		play_turn = !play_turn;
		if (play_turn)
		{
			int ai_nb = ai_play(board);
			remove_items(board, ai_nb);
		}
		else if (!player_turn(board, fd, &play_turn))
			break ;
		if (board->nb_heap == 0)
		{
			if (!play_turn)
				write(1, "AI is the winner! Congratulations!\n", 35);
			else
				write(1, "You are the winner! Congratulations!\n", 37);
			break ;
		}
	}
}
