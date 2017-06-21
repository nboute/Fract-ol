/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setcolors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 16:01:55 by nboute            #+#    #+#             */
/*   Updated: 2017/06/21 18:33:02 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		draw_palet(t_img *menu, int offset, int colstart, int colend)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = 60;
	k = ft_lmap(colstart, 100, 60, 999);
	l = ft_lmap(colend, 100, 60, 999);
	while (i < 1000)
	{
		j = 0;
		while (j < offset)
		{
			if ((i >= k - 2 && i <= k + 2) || (i >= l - 2 && i <= l + 2))
				*(int*)(menu->data + j * 4 + i * menu->size) = (int)0x00FFFFFF;
			else
			{
				*(int*)(menu->data + j * 4 + i * menu->size) = (menu->colors)
					[ft_lmap(i - 60, 940, 0, menu->nbcols - 1)];
			}
			j++;
		}
		i++;
	}
}

int			*set_color_values_p3(int vals[4], int *colors, int val)
{
	int		j;
	double	perc;

	j = 0;
	while (j < vals[3])
	{
		perc = ft_dmap(j, vals[3], 0, 100);
		if (perc > 100)
			perc = 100;
		colors[j] = ft_gradation(colors[-1], val, lround(perc));
		j++;
	}
	return (colors);
}

int			*set_color_values_p2(int vals[4], int *nbcols, int **colors)
{
	int		i;
	int		tmp[2];
	double	perc;

	perc = ft_dmap(vals[0] % vals[2], vals[2], 0, 100);
	i = 0;
	while (i < *nbcols)
	{
		tmp[0] = ((vals[0] + i) - (vals[0] + i) % vals[2]) % (vals[2] * 10 + 1);
		tmp[1] = (tmp[0] + vals[2]) % (vals[2] * 10);
		if ((vals[0] + i) % vals[2] == 0)
			perc = 0;
		if (perc > 100)
			perc = 100;
		(*colors)[i] = get_color_grad(tmp[0], tmp[1], vals[2], lround(perc));
		perc = perc + ft_dmap(1, vals[2], 0, 100);
		i++;
	}
	*nbcols += vals[3];
	tmp[0] = get_color_grad(vals[0] - (vals[0] % vals[2]),
			(vals[0] + vals[2]) % ((vals[2] * 9) + 1),
			vals[2], ft_lmap(vals[0] % vals[2], vals[2], 0, 100));
	set_color_values_p3(vals, (*colors) + i, tmp[0]);
	return (*colors);
}

int			*set_color_values(int vals[4], int *nbcols, int **colors)
{
	*nbcols = labs(vals[1] - vals[0]);
	if (vals[1] < vals[0])
		*nbcols = vals[2] * 10 - *nbcols;
	vals[3] = 0;
	if (*nbcols <= vals[2])
		vals[3] = *nbcols;
	else if (*nbcols >= vals[2] * 9 && *nbcols < vals[2] * 10)
		vals[3] = vals[2] * 10 - *nbcols;
	else if (*nbcols != vals[2] * 10)
		vals[3] = vals[2];
	if (*colors)
		free(*colors);
	if (!(*colors = (int*)malloc(sizeof(int) * (*nbcols + vals[3]))))
		return (0);
	return (set_color_values_p2(vals, nbcols, colors));
}
