
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/29 09:43:18 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include "raylib.h"

void	draw_board(t_board *board);
void	draw_buttons(size_t max_valid);

#define WIN_W	1000
#define BTN_W	120
#define BTN_H	60
#define BTN_GAP	40
#define BTN_Y	900

static int	check_key(t_board *board)
{
	int	key;

	key = GetKeyPressed();
	if (key == KEY_ONE && (size_t)1 <= board->heaps[board->nb_heap - 1])
		return (1);
	if (key == KEY_TWO && (size_t)2 <= board->heaps[board->nb_heap - 1])
		return (2);
	if (key == KEY_THREE && (size_t)3 <= board->heaps[board->nb_heap - 1])
		return (3);
	return (0);
}

int	wait_for_button(int fd, t_board *board)
{
	static char	buf[8];
	static int	buf_len = 0;
	Vector2		mouse;
	int			i;
	int			bx;
	int			key;
	char		c;
	int			choice;

	while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
	{
		BeginDrawing();
		draw_board(board);
		draw_buttons(board->heaps[board->nb_heap - 1]);
		EndDrawing();
		if (read(fd, &c, 1) > 0)
		{
			if (c == '\n' && buf_len > 0)
			{
				buf[buf_len] = '\0';
				buf_len = 0;
				choice = (int)ft_atoi(buf);
				if (choice >= 1 && choice <= 3
					&& (size_t)choice <= board->heaps[board->nb_heap - 1])
					return (choice);
				else
				{
					write(1, buf, ft_strlen(buf));
					write(1, " - Invalid choice\n", 18);
					write(1, "Choose between 1 and 3 items\n",
						ft_strlen("Choose between 1 and 3 items\n"));
				}
			}
			else if (c != '\n' && buf_len < 7)
				buf[buf_len++] = c;
		}
		key = check_key(board);
		if (key)
			return (key);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			mouse = GetMousePosition();
			i = 1;
			while (i <= 3)
			{
				bx = (WIN_W - (3 * BTN_W + 2 * BTN_GAP)) / 2
					+ (i - 1) * (BTN_W + BTN_GAP);
				if (mouse.x >= bx && mouse.x <= bx + BTN_W
					&& mouse.y >= BTN_Y && mouse.y <= BTN_Y + BTN_H
					&& (size_t)i <= board->heaps[board->nb_heap - 1])
					return (i);
				i++;
			}
		}
	}
	return (0);
}
