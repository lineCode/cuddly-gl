/* label.h                                                 -*- C++ -*-
 *   by Trinity Quirk <tquirk@ymb.net>
 *   last updated 18 Nov 2018, 09:34:58 tquirk
 *
 * CuddlyGL OpenGL widget toolkit
 * Copyright (C) 2018  Trinity Annabelle Quirk
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
 * This file contains the basic label object declaration.  We derive
 * from the panel, which will take care of the box part.  In this
 * class, we'll add font handling via freetype, and we'll get our text
 * on the screen via a 2D GL texture.
 *
 * Things to do
 *
 */

#ifndef __INC_CUDDLY_LABEL_H__
#define __INC_CUDDLY_LABEL_H__

#include <string.h>

#include <string>

#include "widget.h"
#include "font.h"

namespace ui
{
    class label : public widget
    {
      protected:
        bool shared_font;
        std::u32string str;
        image img;
        ui::base_font *font;
        GLuint tex;

        int get_font(GLuint, void *) const;
        virtual void set_font(GLuint, ui::base_font *);
        int get_string(GLuint, void *) const;
        virtual void set_string(GLuint, const std::string&);
        int get_image(GLuint, void *) const;
        virtual void set_image(GLuint, const ui::image&);
        virtual void set_border(GLuint, GLuint) override;
        virtual void set_margin(GLuint, GLuint) override;

        virtual void generate_string_image(void);
        virtual void calculate_widget_size(void);
        virtual vertex_buffer *generate_points(void) override;
        virtual void populate_buffers(void) override;

      public:
        label(composite *, GLuint = 0, GLuint = 0);
        virtual ~label();

        virtual int get(GLuint, GLuint, void *) const override;
        using ui::widget::set;
        virtual void set(GLuint, GLuint, ui::base_font *);
        virtual void set(GLuint a, GLuint b, ui::font *c)
            { this->set(a, b, (ui::base_font *)c); }
        virtual void set(GLuint a, GLuint b, ui::font_set *c)
            { this->set(a, b, (ui::base_font *)c); }
        virtual void set(GLuint, GLuint, const std::string&);
        virtual void set(GLuint, GLuint, const ui::image&);

        GET_VA;
        SET_VA;

        virtual void draw(GLuint, const glm::mat4&) override;
    };
}

#endif /* __INC_CUDDLY_LABEL_H__ */
