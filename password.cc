/* password.cc
 *   by Trinity Quirk <tquirk@ymb.net>
 *   last updated 20 May 2018, 15:01:38 tquirk
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
 * This file contains the password field method definitions for the
 * CuddlyGL UI widget set.
 *
 * Things to do
 *
 */

#include "password.h"

void ui::password::generate_string_image(void)
{
    if (this->font != NULL)
    {
        std::u32string save = this->str;
        std::u32string visible;

        visible.insert(0, this->str.size(), '*');
        this->str = visible;
        this->text_field::generate_string_image();
        this->str = save;
    }
}

void ui::password::get_string_size(const std::u32string& s,
                                   GLuint& w, GLuint& a, GLuint& d)
{
    if (this->font != NULL)
    {
        std::u32string visible;

        visible.insert(0, s.size(), '*');
        this->font->get_string_size(visible, w, a, d);
    }
}

int ui::password::get_raw_cursor_pos(void)
{
    int ret = 0;

    if (this->font != NULL)
    {
        std::u32string visible;
        GLuint w, a, d;

        visible.insert(0, this->cursor_pos, '*');
        this->font->get_string_size(visible, w, a, d);
        ret = w;
    }
    return ret;
}

ui::password::password(ui::composite *c, GLuint w, GLuint h)
    : ui::text_field::text_field(c, w, h), ui::active::active(w, h),
      ui::rect::rect(w, h)
{
}

ui::password::~password()
{
}
