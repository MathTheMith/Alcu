/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 07:11:20 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/29 19:54:02 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include "raylib.h"

static int	get_input_fd(int argc, char **argv)
{
	if (argc > 2)
		return (-1);
	if (argc == 2)
		return (open(argv[1], O_RDONLY));
	return (0);
}

int	main(int argc, char **argv)
{
	t_board	board;
	int		tty;
	int		fd;

	fd = get_input_fd(argc, argv);
	if (fd == -1)
	{
		write(2, "ERROR\n", 6);
		return (1);
	}
	if (set_board(&board, fd) == -1)
	{
		if (fd != 0)
			close(fd);
		write(2, "ERROR\n", 6);
		return (1);
	}
	if (fd != 0)
		close(fd);
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
