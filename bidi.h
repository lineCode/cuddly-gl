/* bidi.h                                                  -*- C++ -*-
 *   by Trinity Quirk <tquirk@ymb.net>
 *   last updated 23 Apr 2018, 11:40:56 tquirk
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
 * Prototypes, types, and defines for the Unicode BIDI algorithm.
 * See:  http://unicode.org/reports/tr9/
 *
 * Things to do
 *
 */

#ifndef __INC_CUDDLY_BIDI_H__
#define __INC_CUDDLY_BIDI_H__

#include <string>
#include <vector>
#include <unordered_set>

extern std::unordered_set<char32_t> AL, R;

std::vector<std::u32string> bidi_p1(const std::u32string&);
int bidi_p2_p3(const std::u32string&);

#endif /* __INC_CUDDLY_BIDI_H__ */
