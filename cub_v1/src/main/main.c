/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:27:06 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/18 18:41:22 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	log_state("INIT PARSING", 3);
	if (map_parsing(ac, av, &cub))
		return (ft_malloc(-1), 1);
	check_rendring_depend(&cub);
	log_state("PARSING DONE", 1);
	if (init_window(&cub))
		return (ft_malloc(-1), 1);
	ft_malloc(-1);
	return (0);
}
