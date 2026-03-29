/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 13:12:43 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/29 17:49:09 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

int ai_choose(char *number)
{
    write(1, "AI took ", 8);
    write(1, number, 1);
    write(1, "\n", 1);
    return (ft_atoi(number));
}

int ai_play(t_board *board)
{
    static char	*nums[] = {"1", "2", "3"};
    size_t			take;
    size_t		heap;

    heap = board->heaps[board->nb_heap - 1];
    if (board->nb_heap == 1)
        take = ((heap - 1) % 4);
    else
    {
        int cp_wins = (board->heaps[0] % 4 != 1);
        size_t i = 1;
        while (i < board->nb_heap - 1)
        {
            if (cp_wins)
                cp_wins = (board->heaps[i] % 4 != 1);
            else
                cp_wins = (board->heaps[i] % 4 != 0);
            i++;
        }
        if (cp_wins)
            take = ((heap - 1) % 4);
        else
            take = (heap % 4);
    }
    if (take == 0)
        take = 1;
    if (take > heap)
        take = heap;
    return (ai_choose(nums[take - 1]));
}