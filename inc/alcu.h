/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 07:03:37 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/31 07:53:23 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALCU_H 
#define ALCU_H

#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>

typedef struct board{
    size_t nb_heap;
    size_t total_heaps;
    size_t *heaps;
    char **board;
    size_t biggest_nb;
} t_board;

size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char c);
size_t	ft_atoi(const char *str);
int		is_number(char *str);
void    *realloc_(void *ptr, size_t old_size, size_t new_size);
int		set_board(t_board *board, int fd);
int     ai_play(t_board *board);
void	launch_game(t_board *board, int fd);
char	*readline_(int fd);
void	fill_board(t_board *board);
void    free_board(t_board *board);
void    print_board(t_board *board);
void    init_board_window(void);
int     render_board_window(t_board *board);
int     wait_for_button(int fd, t_board *board);
void    set_ai_took(int n);

#endif