/* ASE - Allegro Sprite Editor
 * Copyright (C) 2001-2008  David A. Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "config.h"

#include "commands/commands.h"
#include "core/app.h"
#include "modules/gui.h"
#include "modules/sprites.h"
#include "raster/layer.h"
#include "raster/sprite.h"
#include "raster/undo.h"
#include "raster/undoable.h"
#include "widgets/colbar.h"

static bool cmd_clear_enabled(const char *argument)
{
  return
    current_sprite != NULL &&
    current_sprite->layer != NULL &&
    layer_is_image(current_sprite->layer) &&
    layer_is_readable(current_sprite->layer) &&
    layer_is_writable(current_sprite->layer);
}

static void cmd_clear_execute(const char *argument)
{
  Sprite* sprite = current_sprite;
  {
    Undoable undoable(sprite, "Clear");
    undoable.clear_mask(app_get_color_to_clear_layer(sprite->layer));
    undoable.commit();
  }
  update_screen_for_sprite(sprite);
}

Command cmd_clear = {
  CMD_CLEAR,
  cmd_clear_enabled,
  NULL,
  cmd_clear_execute,
  NULL
};
