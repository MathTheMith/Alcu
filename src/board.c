/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 07:11:20 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/28 15:05:53 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include <stdlib.h>

char	*readline_(int fd)
{
	char	buf;
	char	*line = NULL;
	size_t	r;

	while (1)
	{
		r = read(fd, &buf, 1);
		if (r <= 0)
			break ;
		if (buf == '\n')
			break ;
		line = ft_strjoin(line, buf);
		if (!line)
			return (NULL);
	}
	if (!line && r <= 0)
		return (NULL);
	return (line);
}

static int	check_line(char *line)
{
	if (!is_number(line))
		return (-1);
	return (1);
}

static int	get_board(t_board *board, int fd)
{
	char	*line;
	size_t	*tmp;

	board->bigest_nb = 0;
	line = readline_(fd);
	while (line)
	{
		if (check_line(line) == -1)
		{
			free(line);
			return (-1);
		}
		tmp = realloc_(board->heaps, board->nb_heap * sizeof(size_t), (board->nb_heap + 1) * sizeof(size_t));
		if (!tmp)
		{
			free(line);
			return (-1);
		}
		board->heaps = tmp;
		board->heaps[board->nb_heap] = ft_atoi(line);
		if (board->heaps[board->nb_heap] > board->bigest_nb)
			board->bigest_nb = board->heaps[board->nb_heap];
		board->nb_heap++;
		free(line);
		line = readline_(fd);
	}
	return (0);
}

static int	init_board(t_board *board)
{
	size_t	i;

	i = 0;
	board->board = malloc(board->nb_heap * sizeof(char *));
	if (!board->board)
		return (-1);
	while (i < board->nb_heap)
	{
		board->board[i] = malloc(board->bigest_nb * sizeof(char) * 2);
		if (!board->board[i])
			return (-1);
		i++;
	}
	return (0);
}

void	fill_board(t_board *board)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < board->nb_heap)
	{
		j = 0;
		while (j < (board->bigest_nb - board->heaps[i]))
		{
			board->board[i][j] = ' ';
			j++;
		}
		k = 0;
		while (k < board->heaps[i])
		{
			board->board[i][j] = '|';
			j++;
			board->board[i][j] = ' ';
			j++;
			k++;
		}
		i++;
	}
}

void	print_board(t_board *board)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < board->nb_heap)
	{
		len = (board->bigest_nb - board->heaps[i]) + board->heaps[i] * 2;
		write(1, board->board[i], len);
		write(1, "\n", 1);
		i++;
	}
}

int	set_board(t_board *board)
{
	board->nb_heap = 0;
	board->total_heaps = 0;
	board->heaps = NULL;
	board->board = NULL;
	board->bigest_nb = 0;
	if (get_board(board, 0) == -1)
		return (-1);
	board->total_heaps = board->nb_heap;
	if (init_board(board) == -1)
		return (-1);
	fill_board(board);
	return (0);
}

void	free_board(t_board *board)
{
	size_t	i;

	i = 0;
	while (i < board->total_heaps)
	{
		free(board->board[i]);
		i++;
	}
	free(board->board);
	free(board->heaps);
}
