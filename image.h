/* image.h                                                 -*- C++ -*-
 *   by Trinity Quirk <tquirk@ymb.net>
 *   last updated 18 May 2018, 09:33:58 tquirk
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
 * Things to do
 *
 */

#ifndef __INC_CUDDLY_IMAGE_H__
#define __INC_CUDDLY_IMAGE_H__

#include <math.h>
#include <string.h>

#include <GL/gl.h>

#include <algorithm>

#include <glm/vec4.hpp>

namespace ui
{
    typedef struct cell_tag
    {
        unsigned char r, g, b, a;

        static float clamp(float n)
            {
                return std::min(std::max(n, 0.0f), 1.0f);
            }

        struct cell_tag& operator=(const glm::vec4& v)
            {
                this->r = truncf(clamp(v.r) * 255);
                this->g = truncf(clamp(v.g) * 255);
                this->b = truncf(clamp(v.b) * 255);
                this->a = truncf(clamp(v.a) * 255);
                return *this;
            }
    } __attribute__ ((__packed__))
    cell;

    struct image
    {
        union {
            unsigned char *data;
            cell *cells;
        };

        GLuint width, height, per_pixel;

        image()
            {
                this->data = NULL;
                this->reset();
            };
        image(const image& i)
            {
                this->data = NULL;
                *this = i;
            };
        ~image()
            {
                if (this->data != NULL)
                    delete[] this->data;
            };
        image& operator=(const image& i)
            {
                GLuint new_size = i.width * i.height * i.per_pixel;

                if (this->data != NULL)
                    delete[] this->data;
                this->width = i.width;
                this->height = i.height;
                this->per_pixel = i.per_pixel;
                if (new_size > 0)
                {
                    this->data = new unsigned char[new_size];
                    memcpy(this->data, i.data, new_size);
                }
                return *this;
            };
        void reset(void)
            {
                this->width = 0;
                this->height = 0;
                this->per_pixel = 0;
                if (this->data != NULL)
                    delete[] this->data;
                this->data = NULL;
            };
    };

}

#endif /* __INC_CUDDLY_IMAGE_H__ */
