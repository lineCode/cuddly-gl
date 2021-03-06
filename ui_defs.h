/* ui_defs.h                                               -*- C++ -*-
 *   by Trinity Quirk <tquirk@ymb.net>
 *   last updated 04 Sep 2018, 06:59:13 tquirk
 *
 * CuddlyGL OpenGL widget toolkit
 * Copyright (C) 2017  Trinity Annabelle Quirk
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *
 * This file contains namespace definitions for the CuddlyGL UI
 * classes.
 *
 * Things to do
 *
 */

#ifndef __INC_CUDDLY_UI_DEFS_H__
#define __INC_CUDDLY_UI_DEFS_H__

#include <GL/gl.h>

#include <glm/vec2.hpp>

namespace ui
{
    /* Mouse motion callback routines */
    typedef struct mouse_callback_call
    {
        glm::ivec2 location;
    }
    mouse_call_data;

    /* Button press/release callback routines */
    typedef struct btn_callback_call
    {
        glm::ivec2 location;
        GLuint button;
        GLuint state;
        GLuint mods;
    }
    btn_call_data;

    /* Key press/release callback routines */
    typedef struct key_callback_call
    {
        glm::ivec2 location;
        uint32_t character;
        GLuint key;
        GLuint state;
        GLuint mods;
    }
    key_call_data;

    /* Resize callback routines */
    typedef struct resize_callback_call
    {
        glm::ivec2 new_size;
    }
    resize_call_data;

#define GET_VA template<typename... Args> \
               int get(GLuint e, GLuint t, void *v, Args... args) const \
               { \
                   return this->get(e, t, v) + this->get(args...); \
               };

#define SET_VA template<typename A, typename... Args>                \
               void set(GLuint e, GLuint t, A v, Args... args)       \
               {                                                     \
                   this->set(e, t, v);                               \
                   this->set(args...);                               \
               };

    namespace element
    {
        const GLuint size = 1, attribute = 2;
        const GLuint border = 3, margin = 4, color = 5, position = 6;
        const GLuint radius = 7;
        const GLuint font = 8, string = 9, image = 10;
        const GLuint state = 11;
        const GLuint cursor = 13;
        const GLuint transform = 15, pixel_size = 16, child_spacing = 17;
        const GLuint resize = 18;
        const GLuint order = 19;
        const GLuint popup = 20;
    }

    namespace size
    {
        const GLuint width = 1, height = 2, all = 3;
        const GLuint rows = 4, columns = 5, grid = 6;
        const GLuint max_width = 7, max_height = 8, max = 9;
    }

    namespace attribute
    {
        const GLuint position = 1, color = 2, texture = 3;
        const GLuint text_bgnd = 4;
    }

    namespace side
    {
        const GLuint top = 1, left = 2, right = 4, bottom = 8, all = 15;
        const GLuint outer = 1, inner = 8;
    }

    namespace corner
    {
        const GLuint top_left = 1, top_right = 2;
        const GLuint bottom_left = 4, bottom_right = 8;
        const GLuint top = 3, left = 5, right = 10, bottom = 12, all = 15;
    }

    namespace color
    {
        const GLuint foreground = 1, background = 2;
    }

    namespace position
    {
        const GLuint x = 1, y = 2, all = 3;
    }

    namespace callback
    {
        const GLuint enter = 1, leave = 2, btn_down = 3, btn_up = 4;
        const GLuint motion = 5, key_down = 6, key_up = 7, resize = 8;
    }

    namespace mouse
    {
        const int button0 = 0, button1 = 1, button2 = 2, button3 = 3;
        const int button4 = 4, button5 = 5, button6 = 6, button7 = 7;
        const int down = 254, up = 255;
    }

    namespace key
    {
        const int no_key = 0;
        const int l_arrow = 1, r_arrow = 2, u_arrow = 3, d_arrow = 4;
        const int pg_up = 5, pg_down = 6, home = 7, end = 8;
        const int bkspc = 9, del = 10, esc = 11;
        const int down = 254, up = 255;
    }

    namespace key_mod
    {
        const int shift = 1, ctrl = 2, alt = 4, meta = 8;
        const int super = 16, hyper = 32;
    }

    namespace cursor
    {
        const int position = 1, blink = 2;
    }

    namespace transform
    {
        const GLuint translate = 1;
    }

    namespace resize
    {
        const GLuint none = 0, shrink = 1, grow = 2, all = 3;
    }

    namespace order
    {
        const GLuint row = 1, column = 2;
    }

    namespace ownership
    {
        const GLuint shared = 1, owned = 2;
    }

    namespace popup
    {
        const GLuint visible = 1, button = 2, menu = 3;
    }

    namespace state
    {
        const GLuint visible = 1, active = 2, armed = 3;
    }
}

#endif /* __INC_CUDDLY_UI_DEFS_H__ */
