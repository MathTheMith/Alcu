/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/28 16:16:49 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include "raylib.h"
#include <sys/select.h>

#define WIN_W	1000
#define WIN_H	1000
#define FONT_SZ	36
#define ROW_H	80

Color	row_color(size_t i)
{
	Color	palette[6];

	palette[0] = (Color){220, 80,  80,  255};
	palette[1] = (Color){80,  140, 220, 255};
	palette[2] = (Color){80,  180, 100, 255};
	palette[3] = (Color){200, 150, 50,  255};
	palette[4] = (Color){160, 80,  200, 255};
	palette[5] = (Color){50,  180, 180, 255};
	return (palette[i % 6]);
}

void	init_board_window(void)
{
	SetTraceLogLevel(LOG_NONE);
	InitWindow(WIN_W, WIN_H, "Alcu");
	SetTargetFPS(60);
}

static char	*skip_spaces(char *s)
{
	while (*s == ' ')
		s++;
	return (s);
}

int	render_board_window(t_board *board)
{
	size_t	i;
	int		y;
	Color	c;

	BeginDrawing();
	ClearBackground((Color){30, 30, 40, 255});
	DrawText("~ ALCU ~", WIN_W / 2 - MeasureText("~ ALCU ~", 48) / 2, 30, 48, WHITE);
	DrawLine(60, 100, WIN_W - 60, 100, (Color){80, 80, 100, 255});
	i = 0;
	y = 130;
	while (i < board->nb_heap)
	{
		c = row_color(i);
		DrawText(TextFormat("%zu", i + 1), 30, y + 10, FONT_SZ, (Color){c.r, c.g, c.b, 120});
		DrawText(skip_spaces(board->board[i]), WIN_W / 4, y, FONT_SZ, c);
		y += ROW_H;
		i++;
	}
	DrawLine(60, y + 10, WIN_W - 60, y + 10, (Color){80, 80, 100, 255});
	EndDrawing();
	return (WindowShouldClose()
		|| IsKeyPressed(KEY_ESCAPE)
		|| IsKeyPressed(KEY_ENTER));
}

char	*readline_windowed(int fd, t_board *board)
{
	fd_set			rfds;
	struct timeval	tv;

	while (!WindowShouldClose()
		&& !IsKeyPressed(KEY_ESCAPE)
		&& !IsKeyPressed(KEY_ENTER))
	{
		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);
		tv.tv_sec = 0;
		tv.tv_usec = 16000;
		if (select(fd + 1, &rfds, NULL, NULL, &tv) > 0)
			return (readline_(fd));
		render_board_window(board);
	}
	return (NULL);
}
