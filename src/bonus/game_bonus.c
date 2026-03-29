/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/29 00:00:00 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include "raylib.h"
#include <stdbool.h>

static int	remove_items(t_board *board, int choice)
{
	board->heaps[board->nb_heap - 1] -= (size_t)choice;
	if (board->heaps[board->nb_heap - 1] == 0)
		board->nb_heap--;
	fill_board(board);
	print_board(board);
	return (render_board_window(board));
}

static int	player_turn(t_board *board, int fd, bool *play_turn)
{
	int		choice;
	char	c;

	write(1, "Choose between 1 and 3 items\n",
		ft_strlen("Choose between 1 and 3 items\n"));
	choice = wait_for_button(fd, board);
	if (!choice)
		return (-1);
	c = choice + '0';
	write(1, &c, 1);
	write(1, "\n", 1);
	if (choice < 1 || choice > 3
		|| (size_t)choice > board->heaps[board->nb_heap - 1])
	{
		write(1, " - Invalid choice\n", 18);
		*play_turn = !(*play_turn);
		return (0);
	}
	board->player_nb = choice;
	return (remove_items(board, choice));
}

void	launch_game(t_board *board, int fd)
{
	bool	play_turn;
	int		ret;

	board->player_nb = -1;
	play_turn = false;
	while (1)
	{
		play_turn = !play_turn;
		if (play_turn)
		{
			int nb_ai = ai_play(board);
			set_ai_took(nb_ai);
			if (remove_items(board, nb_ai))
				break ;
		}
		else
		{
			ret = player_turn(board, fd, &play_turn);
			if (ret == -1)
				break ;
			if (ret > 0)
				break ;
		}
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
