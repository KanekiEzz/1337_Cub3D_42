/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:48:07 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/17 12:59:13 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_up(void)
{
	ft_malloc(-1);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	printf(COLOR_YELLOW "[INIT PARSING] " COLOR_RESET "\n");
	if (map_parsing(ac, av, &cub))
		return (clean_up(), 1);
	printf(COLOR_GREEN "[DONE PARSING] " COLOR_RESET "\n");
	printf(COLOR_YELLOW "[CREATING WINDOW]  " COLOR_RESET "\n");
	if (init_window(&cub))
		return (clean_up(), 1);
	clean_up();
	return (0);
}
