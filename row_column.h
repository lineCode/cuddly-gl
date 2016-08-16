/* row_column.h                                       -*- C++ -*-
 *   by Trinity Quirk <tquirk@ymb.net>
 *   last updated 15 Aug 2016, 23:24:12 tquirk
 *
 * Revision IX game client
 * Copyright (C) 2016  Trinity Annabelle Quirk
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
 * This file contains the declaration for the row-column object.  It
 * extends the manager to add grid layout of its children.
 *
 * Things to do
 *
 */

#ifndef __INC_R9_ROW_COLUMN_H__
#define __INC_R9_ROW_COLUMN_H__

#include "manager.h"

namespace ui
{
    class row_column : public manager
    {
      public:
        row_column(composite *, GLuint, GLuint);
        virtual ~row_column();
    };
}

#endif /* __INC_R9_ROW_COLUMN_H__ */