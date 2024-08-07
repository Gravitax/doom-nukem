/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/21 18:39:05 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*maps_paths(unsigned int index)
{
	static char	*paths[SCENE_MAX] = {	"resources/maps/famas.obj",
										"resources/maps/ak47.obj",
										"resources/maps/sawed-off.obj",
										"resources/maps/glock-18.obj",
										"resources/maps/aug.obj",
										"resources/maps/ump45.obj",
										"resources/maps/mag-7.obj",
										"resources/maps/galil.obj",
										"resources/maps/negev.obj",
										"resources/maps/tec-9.obj",
										"resources/maps/physic.obj",
										"resources/maps/cube.obj",
										"resources/maps/axis.obj",
										"resources/maps/pente_nord.obj",
										"resources/maps/pente_ouest.obj",
										"resources/maps/pente_sud.obj",
										"resources/maps/pente_est.obj",
										"resources/maps/map-test.obj",
										"resources/maps/ugly.obj",
										"resources/maps/moon.obj",
										"resources/maps/star.obj",
										"resources/maps/mage.obj",
										"resources/maps/loot.obj",
										"resources/maps/goule.obj",
										"resources/maps/house.obj",
										"resources/maps/key.obj",
										"resources/maps/start_room.obj",
										"resources/maps/dust.obj"};

	return (paths[index]);
}

char	*sprites_paths(unsigned int index)
{
	static char		*paths[SP_MAX] = {
					"resources/sprites/buttons/campaign_clic.xpm",
					"resources/sprites/buttons/campaign_hover.xpm",
					"resources/sprites/buttons/campaign_off.xpm",
					"resources/sprites/buttons/custom_clic.xpm",
					"resources/sprites/buttons/custom_hover.xpm",
					"resources/sprites/buttons/custom_off.xpm",
					"resources/sprites/buttons/map_editor_clic.xpm",
					"resources/sprites/buttons/map_editor_hover.xpm",
					"resources/sprites/buttons/map_editor_off.xpm",
					"resources/sprites/buttons/quit_clic.xpm",
					"resources/sprites/buttons/quit_hover.xpm",
					"resources/sprites/buttons/quit_off.xpm",
					"resources/sprites/logo.xpm",
					"resources/sprites/buttons/SP_CP_BUTTON_1C.xpm",
					"resources/sprites/buttons/SP_CP_BUTTON_1H.xpm",
					"resources/sprites/buttons/SP_CP_BUTTON_1O.xpm",
					"resources/sprites/buttons/SP_CP_BUTTON_2C.xpm",
					"resources/sprites/buttons/SP_CP_BUTTON_2H.xpm",
					"resources/sprites/buttons/SP_CP_BUTTON_2O.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_2C.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_2H.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_2O.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_CREATE_1C.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_CREATE_1H.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_CREATE_1O.xpm",
					"resources/sprites/buttons/SP_NM_BUTTON_MAPED_2C.xpm",
					"resources/sprites/buttons/SP_NM_BUTTON_MAPED_2H.xpm",
					"resources/sprites/buttons/SP_NM_BUTTON_MAPED_2O.xpm",
					"resources/sprites/ts_background.xpm",
					"resources/sprites/cmp_ts_background.xpm",
					"resources/sprites/main_txt_loader_campaign.xpm",
					"resources/sprites/map_editor_background.xpm",
					"resources/sprites/me_new_map_background.xpm",
					"resources/sprites/map_editor_menu_title.xpm",
					"resources/sprites/map_editor_new_map_title.xpm",
					"resources/sprites/custom_background.xpm",
					"resources/sprites/hitmarker.xpm",
					"resources/sprites/game_over.xpm",
					"resources/sprites/buttons/yes_off.xpm",
					"resources/sprites/buttons/yes_hover.xpm",
					"resources/sprites/buttons/yes_on.xpm",
					"resources/sprites/buttons/no_off.xpm",
					"resources/sprites/buttons/no_hover.xpm",
					"resources/sprites/buttons/no_on.xpm",
					"resources/sprites/coins.xpm",
					"resources/sprites/new_wave.xpm",
					"resources/sprites/key.xpm",
					"resources/sprites/campaign/1.xpm",
					"resources/sprites/campaign/2.xpm",
					"resources/sprites/campaign/3.xpm",
					"resources/sprites/campaign/4.xpm",
					"resources/sprites/campaign/5.xpm",
					"resources/sprites/campaign/6.xpm",
					"resources/sprites/campaign/7.xpm",
					"resources/sprites/campaign/8.xpm"};

	return (paths[index]);
}

char	*blocs_txt_paths(unsigned int index)
{
	static char		*paths[BTXT_MAX] = {"",
		"resources/textures/blocs/brique.xpm",
		"resources/textures/blocs/brique_dark.xpm",
		"resources/textures/blocs/clean_stone.xpm",
		"resources/textures/blocs/dirt.xpm",
		"resources/textures/blocs/dirt_grass.xpm",
		"resources/textures/blocs/dirt_snow.xpm",
		"resources/textures/blocs/glace.xpm",
		"resources/textures/blocs/gold.xpm",
		"resources/textures/blocs/iron.xpm",
		"resources/textures/blocs/light.xpm",
		"resources/textures/blocs/obsidienne.xpm",
		"resources/textures/blocs/sand.xpm",
		"resources/textures/blocs/stone.xpm",
		"resources/textures/blocs/wood_a.xpm",
		"resources/textures/blocs/wood_a_cut.xpm",
		"resources/textures/blocs/wood_b.xpm",
		"resources/textures/blocs/wood_b_cut.xpm",
		"resources/textures/blocs/wood_c.xpm",
		"resources/textures/blocs/wood_c_cut.xpm",
		"resources/textures/blocs/wood_d.xpm",
		"resources/textures/blocs/wood_d_cut.xpm",
		"resources/textures/blocs/jukebox.xpm",
		"resources/textures/blocs/mystery_box.xpm",
		"resources/textures/blocs/door.xpm",
		"resources/textures/blocs/lava.xpm",
		"resources/textures/blocs/spawner.xpm",
		"resources/textures/blocs/mob_spawner.xpm"};

	return (paths[index]);
}

char	*samples_paths(unsigned int index)
{
	static char		*paths[SA_MAX] = {"resources/samples/ambiances/title_screen_intro.wav",
					"resources/samples/ambiances/title_screen_loop.wav",
					"resources/samples/musics/game1.wav",
					"resources/samples/musics/game2.wav",
					"resources/samples/musics/game3.wav",
					"resources/samples/musics/game4.wav",
					"resources/samples/musics/gameover.wav",
					"resources/samples/musics/maped.wav",
					"resources/samples/weapons/ak47-reload.wav",
					"resources/samples/weapons/ak47-shot.wav",
					"resources/samples/weapons/aug-reload.wav",
					"resources/samples/weapons/aug-shot.wav",
					"resources/samples/weapons/famas-reload.wav",
					"resources/samples/weapons/famas-shot.wav",
					"resources/samples/weapons/galil-reload.wav",
					"resources/samples/weapons/galil-shot.wav",
					"resources/samples/weapons/glock-reload.wav",
					"resources/samples/weapons/glock-shot.wav",
					"resources/samples/weapons/mag7-reload.wav",
					"resources/samples/weapons/mag7-shot.wav",
					"resources/samples/weapons/negev-reload.wav",
					"resources/samples/weapons/negev-shot.wav",
					"resources/samples/weapons/sawed-off-fill.wav",
					"resources/samples/weapons/sawed-off-pump.wav",
					"resources/samples/weapons/sawed-off-shot.wav",
					"resources/samples/weapons/tec9-reload.wav",
					"resources/samples/weapons/tec9-shot.wav",
					"resources/samples/weapons/ump45-reload.wav",
					"resources/samples/weapons/ump45-shot.wav",
					"resources/samples/voices/doublekill.wav",
					"resources/samples/voices/triplekill.wav",
					"resources/samples/voices/rampage.wav",
					"resources/samples/voices/godlike.wav",
					"resources/samples/voices/wickedsick.wav",
					"resources/samples/monsters/death_monster.wav",
					"resources/samples/monsters/levitation.wav",
					"resources/samples/world/button.wav",
					"resources/samples/world/put.wav",
					"resources/samples/world/take.wav",
					"resources/samples/world/step.wav",
					"resources/samples/world/lava.wav",
					"resources/samples/world/door.wav",
					"resources/samples/world/change.wav",
					"resources/samples/loots/nuke.wav",
					"resources/samples/loots/ammos.wav",
					"resources/samples/loots/cash.wav",
					"resources/samples/loots/god_end.wav",
					"resources/samples/loots/god_start.wav",
					"resources/samples/voices/player_damage.wav"};

	return (paths[index]);
}

char	*icones_paths(unsigned int index)
{
	static char		*paths[BTXT_MAX] = {"brick_ico.xpm", "dark_brick_ico.xpm",
										"clean_stone_ico.xpm", "dirt_ico.xpm",
										"dirt_grass_ico.xpm",
										"dirt_snow_ico.xpm",
										"glace_ico.xpm",
										"gold_ico.xpm",
										"iron_ico.xpm",
										"light_ico.xpm",
										"obsidienne_ico.xpm",
										"sand_ico.xpm",
										"stone_ico.xpm",
										"wood_a_ico.xpm",
										"wood_a_cut_ico.xpm",
										"wood_b_ico.xpm",
										"wood_b_cut_ico.xpm",
										"wood_c_ico.xpm",
										"wood_c_cut_ico.xpm",
										"wood_d_ico.xpm",
										"wood_d_cut_ico.xpm",
										"jukebox_ico.xpm",
										"mystery_box_ico.xpm",
										"door_ico.xpm",
										"lava_ico.xpm",
										"spawner_ico.xpm",
										"mob_spawner_ico.xpm"};

	return (paths[index]);
}

char	*fonts_paths(unsigned int index)
{
	static char		*paths[FONT_MAX] = {"resources/fonts/arial.ttf",
										"resources/fonts/ammos.ttf",
										"resources/fonts/Courier.dfont",
										"resources/fonts/coolvetica.ttf"};

	return (paths[index]);
}
