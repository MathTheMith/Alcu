/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 07:11:20 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/29 18:33:31 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include "raylib.h"
#include <stdlib.h>

int	main(void)
{
	t_board	board;
	int		tty;

	if (set_board(&board) == -1)
	{
		write(1, "ERROR\n", 6);
		return (1);
	}
	tty = open("/dev/tty", O_RDONLY | O_NONBLOCK);
	if (tty == -1)
	{
		free_board(&board);
		return (1);
	}
	init_board_window();
	print_board(&board);
	if (!render_board_window(&board))
		launch_game(&board, tty);
	CloseWindow();
	free_board(&board);
	close(tty);
	return (0);
}
