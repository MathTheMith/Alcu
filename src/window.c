/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/28 17:41:56 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include "raylib.h"
#include <sys/select.h>
#include <stdlib.h>

#define WIN_W	1000
#define WIN_H	1000
#define FONT_SZ	36
#define ROW_H	80
#define BTN_W	120
#define BTN_H	60
#define BTN_GAP	40
#define BTN_Y	900

static int	g_ai_took = 0;

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

void	set_ai_took(int n)
{
	g_ai_took = n;
}

static char	*skip_spaces(char *s)
{
	while (*s == ' ')
		s++;
	return (s);
}

static void	draw_board(t_board *board)
{
	size_t		i;
	int			y;
	Color		c;
	const char	*msg;

	ClearBackground((Color){30, 30, 40, 255});
	DrawText("~ ALCU ~", WIN_W / 2 - MeasureText("~ ALCU ~", 48) / 2,
		30, 48, WHITE);
	DrawLine(60, 100, WIN_W - 60, 100, (Color){80, 80, 100, 255});
	i = 0;
	y = 130;
	while (i < board->nb_heap)
	{
		c = row_color(i);
		DrawText(TextFormat("%zu", i + 1), 30, y + 10, FONT_SZ,
			(Color){c.r, c.g, c.b, 120});
		DrawText(skip_spaces(board->board[i]), WIN_W / 4, y, FONT_SZ, c);
		y += ROW_H;
		i++;
	}
	DrawLine(60, y + 10, WIN_W - 60, y + 10, (Color){80, 80, 100, 255});
	if (g_ai_took > 0)
	{
		msg = TextFormat("L'IA a pris %d", g_ai_took);
		DrawText(msg, WIN_W / 2 - MeasureText(msg, FONT_SZ) / 2,
			BTN_Y - 60, FONT_SZ, (Color){180, 180, 200, 255});
	}
}

static void	draw_buttons(size_t max_valid)
{
	int		i;
	int		bx;
	Color	col;
	Color	text_col;
	char	label[2];

	i = 1;
	while (i <= 3)
	{
		bx = (WIN_W - (3 * BTN_W + 2 * BTN_GAP)) / 2
			+ (i - 1) * (BTN_W + BTN_GAP);
		if ((size_t)i <= max_valid)
		{
			col = (Color){80, 160, 80, 255};
			text_col = WHITE;
		}
		else
		{
			col = (Color){55, 55, 65, 255};
			text_col = (Color){90, 90, 100, 255};
		}
		DrawRectangle(bx, BTN_Y, BTN_W, BTN_H, col);
		label[0] = '0' + i;
		label[1] = '\0';
		DrawText(label, bx + BTN_W / 2 - MeasureText(label, FONT_SZ) / 2,
			BTN_Y + BTN_H / 2 - FONT_SZ / 2, FONT_SZ, text_col);
		i++;
	}
}

int	render_board_window(t_board *board)
{
	BeginDrawing();
	draw_board(board);
	EndDrawing();
	return (WindowShouldClose()
		|| IsKeyPressed(KEY_ESCAPE)
		|| IsKeyPressed(KEY_ENTER));
}

int	wait_for_button(int fd, t_board *board)
{
	fd_set			rfds;
	struct timeval	tv;
	char			*line;
	Vector2			mouse;
	int				i;
	int				bx;

	while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
	{
		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);
		tv.tv_sec = 0;
		tv.tv_usec = 16000;
		if (select(fd + 1, &rfds, NULL, NULL, &tv) > 0)
		{
			line = readline_(fd);
			if (!line)
				return (0);
			i = (int)ft_atoi(line);
			free(line);
			return (i);
		}
		BeginDrawing();
		draw_board(board);
		draw_buttons(board->heaps[board->nb_heap - 1]);
		EndDrawing();
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
