SRCS_NAME =	main.c\
			free.c\
			free2.c\
			openal.c\
			resources_paths.c\
			setup.c\
			singletons.c\
			text.c\
			text2.c\
			scroll_file.c\
			\
			sound_system/sound_system.c\
			sound_system/sound_system_functions.c\
			sound_system/sound_system_manager.c\
			sound_system/sound_system_params.c\
			sound_system/sound_system_play.c\
			sound_system/sound_system_tools.c\
			\
			campaign/render.c\
			campaign/events.c\
			campaign/key.c\
			campaign/setup_cmp.c\
			campaign/menu.c\
			campaign/game.c\
			campaign/intro.c\
			campaign/routines.c\
			campaign/sectors.c\
			\
			contexts/switch_context.c\
			contexts/routines.c\
			contexts/routines_bis.c\
			\
			custom_mode/render.c\
			custom_mode/copy_to_scene.c\
			custom_mode/doors.c\
			custom_mode/events.c\
			custom_mode/events_blocks.c\
			custom_mode/events_blocks_funcs.c\
			custom_mode/game_over.c\
			custom_mode/loots.c\
			custom_mode/loots_functions.c\
			custom_mode/menu.c\
			custom_mode/moon.c\
			custom_mode/play.c\
			custom_mode/player.c\
			custom_mode/routines.c\
			custom_mode/setup.c\
			custom_mode/sky.c\
			custom_mode/tools.c\
			custom_mode/waves.c\
			\
			enemies/astar.c\
			enemies/astar_quick_sort.c\
			enemies/astar_tools.c\
			enemies/create_mob.c\
			enemies/enemies.c\
			enemies/enemies_animations.c\
			enemies/enemies_damages.c\
			enemies/enemies_death.c\
			enemies/enemies_do_movement.c\
			enemies/enemies_kills_annoucements.c\
			enemies/enemies_movements.c\
			enemies/enemies_rotations.c\
			enemies/nodes.c\
			enemies/nodes_neighbours.c\
			enemies/tools.c\
			\
			map_editor/build_map.c\
			map_editor/block.c\
			map_editor/category_pallet.c\
			map_editor/convert_matrice.c\
			map_editor/flat_map.c\
			map_editor/crosshair.c\
			map_editor/create_map.c\
			map_editor/creative.c\
			map_editor/handle_creative_events.c\
			map_editor/export.c\
			map_editor/setup_me.c\
			map_editor/render.c\
			map_editor/events.c\
			map_editor/import.c\
			map_editor/load_shapes.c\
			map_editor/menu.c\
			map_editor/map_to_scene.c\
			map_editor/new_map.c\
			map_editor/pallet.c\
			map_editor/file.c\
			map_editor/listpath.c\
			map_editor/switch_bt.c\
			map_editor/render_pallet.c\
			map_editor/replace_by_face.c\
			map_editor/routines.c\
			map_editor/input_field.c\
			map_editor/input_field_tools.c\
			map_editor/culling.c\
			map_editor/cull_slopes.c\
			map_editor/tools.c\
			\
			obj_parser/load_maps.c\
			obj_parser/dependencies.c\
			obj_parser/mapper.c\
			obj_parser/mapper_fts.c\
			obj_parser/mapper_fts_bis.c\
			obj_parser/mapper_values.c\
			obj_parser/load_face.c\
			obj_parser/lines_fts.c\
			obj_parser/lines_fts_bis.c\
			obj_parser/check_formats.c\
			obj_parser/parse_map.c\
			obj_parser/parse_map_tools.c\
			obj_parser/parse_mtl.c\
			obj_parser/mtl_lines_fts.c\
			obj_parser/states.c\
			obj_parser/tools.c\
			\
			physic_engine/init_engine.c\
			physic_engine/init_bounding_boxs.c\
			physic_engine/engine.c\
			physic_engine/report_collisions.c\
			physic_engine/move_mesh.c\
			physic_engine/phy_gravity.c\
			physic_engine/phy_tool.c\
			physic_engine/phy_tool2.c\
			physic_engine/phy_tool3.c \
			physic_engine/phy_update.c\
			physic_engine/phy_move.c\
			physic_engine/rotate.c \
			\
			rasterizer/clipping.c\
			rasterizer/clipping_bis.c\
			rasterizer/clipping_tools.c\
			rasterizer/draw_triangle_line.c\
			rasterizer/fill_triangle_texture.c\
			rasterizer/fill_triangle_texture_bis.c\
			rasterizer/rasterizer.c\
			rasterizer/raster_tools.c\
			rasterizer/triangle_pipeline.c\
			rasterizer/raster_triangles.c\
			rasterizer/camera.c\
			rasterizer/aim.c\
			rasterizer/rotation_matrices.c\
			rasterizer/matrices.c\
			rasterizer/matrix_ops.c\
			rasterizer/matrix_tools.c\
			\
			mlx/init_mlx.c\
			mlx/sprites.c\
			mlx/pixloc.c\
			mlx/sprites_effects.c\
			mlx/render.c\
			mlx/term_loading_bar.c\
			mlx/events.c\
			mlx/basics.c\
			mlx/bresenham.c\
			mlx/shapes.c\
			mlx/hooks.c\
			\
			title_screen/animation.c\
			title_screen/setup_ts.c\
			title_screen/buttons.c\
			title_screen/events.c\
			title_screen/render.c\
			\
			vectors/vectors.c\
			vectors/vec2d_tools.c\
			vectors/vec3d_ops.c\
			vectors/vec3d_fops.c\
			vectors/vec3d_tools.c\
			vectors/vec3d_tools2.c\
			\
			weapons/weapons.c\
			weapons/ammos.c\
			weapons/hud.c\
			weapons/init_weapons.c\
			weapons/reload_animation.c\
			weapons/reticule.c\
			weapons/shoot.c\
			weapons/shoot_animation.c\
			weapons/sprint.c\
			weapons/stats.c\
			\
			archive/archive.c\
			archive/unarchive.c\
			archive/archive_tools.c\
			\
			hud/hud.c\
			hud/health.c\
			hud/waves.c\
			hud/countdown.c\
			hud/compass.c
