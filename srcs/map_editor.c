/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:12:32 by maboye            #+#    #+#             */
/*   Updated: 2020/02/26 18:15:48 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static int      events_map_editor(t_doom *data)
{
	while (SDL_PollEvent(&data->event))
	{
        if ((data->event.key.keysym.sym == SDLK_ESCAPE
	    && data->event.type == SDL_KEYDOWN)
	    || data->event.type == SDL_QUIT)
	        clean_exit(data, "cube3d: EXIT_SUCCES", 1);
		if (data->event.type == SDL_KEYDOWN
		&& data->event.key.keysym.sym == SDLK_p)
			return (0);
	}
    return (1);
}

void		    map_editor(t_doom *data)
{
	if (data->event.key.keysym.sym == SDLK_p)
	{
		SDL_RenderClear(data->renderer);
		SDL_RenderPresent(data->renderer);
		while (1)
		{
            if (events_map_editor(data) == 0)
                break ;
			puts("press p to break");
		}
	}
}
