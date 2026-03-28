/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 07:11:20 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/28 07:11:20 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>

static int	remove_items(t_board *board, char *answer)
{
	board->heaps[board->nb_heap - 1] -= ft_atoi(answer);
	if (board->heaps[board->nb_heap - 1] == 0)
		board->nb_heap--;
	fill_board(board);
	print_board(board);
	return (render_board_window(board));
}

static void	launch_game(t_board *board, int fd)
{
	bool	play_turn;
	char	*answer;

	play_turn = false;
	answer = NULL;
	while (1)
	{
		play_turn = !play_turn;
		if (play_turn)
		{
			write(1, "AI took 1\n", 10);
			if (remove_items(board, "1"))
				break ;
		}
		else
		{
			write(1, "Choose between 1 and 3 items\n",
				ft_strlen("Choose between 1 and 3 items\n"));
			answer = readline_windowed(fd, board);
			if (!answer)
				break ;
			if (ft_atoi(answer) < 1 || ft_atoi(answer) > 3
				|| ft_atoi(answer) > board->heaps[board->nb_heap - 1])
			{
				write(1, answer, ft_strlen(answer));
				write(1, " - Invalid choice\n", 18);
				play_turn = !play_turn;
			}
			else if (remove_items(board, answer))
			{
				free(answer);
				break ;
			}
			free(answer);
		}
		if (board->nb_heap == 0)
		{
			if (play_turn)
				write(1, "AI is the winner! Congratulations!\n", 35);
			else
				write(1, "You are the winner! Congratulations!\n", 37);
			break ;
		}
	}
}

int	main(void)
{
	t_board	board;
	int		tty;

	if (set_board(&board) == -1)
	{
		write(1, "ERROR\n", 6);
		return (1);
	}
	tty = open("/dev/tty", O_RDONLY);
	if (tty == -1)
		return (1);
	init_board_window();
	print_board(&board);
	if (!render_board_window(&board))
		launch_game(&board, tty);
	CloseWindow();
	free_board(&board);
	close(tty);
	return (0);
}
