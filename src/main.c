/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 07:11:20 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/29 09:28:31 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

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
	print_board(&board);
	launch_game(&board, tty);
	free_board(&board);
	close(tty);
	return (0);
}
