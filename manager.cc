/* manager.cc
 *   by Trinity Quirk <tquirk@ymb.net>
 *   last updated 11 Sep 2016, 08:08:32 tquirk
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
 * This file contains the method definitions for the manager object,
 * which combines the panel with the composite.
 *
 * Things to do
 *
 */

#include <algorithm>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ui_defs.h"
#include "manager.h"

int ui::manager::get_child_spacing(GLuint t, void *v)
{
    int ret = 0;

    switch (t)
    {
      case ui::size::all:    *(glm::ivec2 *)v = this->child_spacing;  break;
      case ui::size::width:  *(int *)v = this->child_spacing.x;       break;
      case ui::size::height: *(int *)v = this->child_spacing.y;       break;
      default:               ret = 1;                                 break;
    }
    return ret;
}

void ui::manager::set_child_spacing(GLuint t, void *v)
{
    switch (t)
    {
      case ui::size::all:     this->child_spacing = *(glm::ivec2 *)v;  break;
      case ui::size::width:   this->child_spacing.x = *(int *)v;       break;
      case ui::size::height:  this->child_spacing.y = *(int *)v;       break;
    }
}

int ui::manager::get_resize(GLuint t, void *v)
{
    *(GLuint *)v = this->resize;
    return 0;
}

void ui::manager::set_resize(GLuint t, void *v)
{
    GLuint new_v = *((GLuint *)v);

    if (new_v <= ui::resize::all)
        this->resize = new_v;

    if (this->resize != ui::resize::none)
        this->set_desired_size();
}

int ui::manager::get_size(GLuint t, void *v)
{
    return this->composite::get_size(t, v);
}

void ui::manager::set_size(GLuint t, void *v)
{
    this->composite::set_size(t, v);
    this->panel::set_size(t, v);
}

void ui::manager::set_position(GLuint t, void *v)
{
    this->panel::set_position(t, v);
    if (this->composite::parent != NULL)
    {
        glm::vec3 pixel_sz(0.0f, 0.0f, 0.0f);
        glm::mat4 trans;

        this->composite::parent->get(ui::element::transform,
                                     ui::transform::translate,
                                     &trans);
        this->composite::parent->get(ui::element::pixel_size,
                                     ui::size::all,
                                     &pixel_sz);
        pixel_sz.x *= this->pos.x;
        pixel_sz.y = -(pixel_sz.y * this->pos.y);
        this->translate = glm::translate(trans, pixel_sz);
    }
}

int ui::manager::get_pixel_size(GLuint t, void *v)
{
    if (this->composite::parent != NULL)
        return this->composite::parent->get(ui::element::pixel_size, t, v);
    return 1;
}

glm::ivec2 ui::manager::calculate_max_point(void)
{
    glm::ivec2 max_pt(0, 0);

    for (auto i = this->children.begin(); i != this->children.end(); ++i)
    {
        glm::ivec2 c_sz, c_pos;

        (*i)->get_va(ui::element::size, ui::size::all, &c_sz,
                     ui::element::position, ui::position::all, &c_pos, 0);
        c_sz += c_pos;
        max_pt.x = std::max(max_pt.x, c_sz.x);
        max_pt.y = std::max(max_pt.y, c_sz.y);
    }
    return max_pt;
}

void ui::manager::set_desired_size(void)
{
    glm::ivec2 max_pt(0, 0);
    GLuint zero = 0;

    if (this->resize == ui::resize::none)
        return;

    max_pt = this->calculate_max_point();
    max_pt.x += this->margin[1] + this->margin[2]
        + this->border[1] + this->border[2]
        + this->child_spacing.x;
    max_pt.y += this->margin[0] + this->margin[3]
        + this->border[0] + this->border[3]
        + this->child_spacing.y;

    /* We could possibly shrink one dimension and grow another, so
     * we'll handle both cases directly (i.e. no 'else').
     */
    if (this->resize & ui::resize::shrink)
    {
        if (max_pt.x < this->size.x)
            this->size.x = this->dim.x = max_pt.x;
        if (max_pt.y < this->size.y)
            this->size.y = this->dim.y = max_pt.y;
    }
    if (this->resize & ui::resize::grow)
    {
        if (max_pt.x > this->size.x)
            this->size.x = this->dim.x = max_pt.x;
        if (max_pt.y > this->size.y)
            this->size.y = this->dim.y = max_pt.y;
    }
    this->composite::set_size(0, &zero);
    this->populate_buffers();
}

void ui::manager::leave_callback(event_target *p, void *call, void *client)
{
    ui::manager *m = dynamic_cast<ui::manager *>(p);

    if (m != NULL && m->old_child != NULL)
        m->old_child->call_callbacks(ui::callback::leave, NULL);
}

void ui::manager::motion_callback(event_target *p, void *call, void *client)
{
    ui::manager *m = dynamic_cast<ui::manager *>(p);

    if (m != NULL)
    {
        ui::mouse_call_data *mcd = (ui::mouse_call_data *)call;

        m->mouse_pos_callback(mcd->location.x, mcd->location.y);
    }
}

void ui::manager::button_callback(event_target *p, void *call, void *client)
{
    ui::manager *m = dynamic_cast<ui::manager *>(p);

    if (m != NULL)
    {
        ui::btn_call_data *bcd = (ui::btn_call_data *)call;

        m->mouse_btn_callback(bcd->button, bcd->state);
    }
}

void ui::manager::keypress_callback(event_target *p, void *call, void *client)
{
    ui::manager *m = dynamic_cast<ui::manager *>(p);

    if (m != NULL)
    {
        ui::key_call_data *kcd = (ui::key_call_data *)call;

        m->key_callback(kcd->key, kcd->character, kcd->state, kcd->mods);
    }
}

ui::manager::manager(ui::composite *c, GLuint w, GLuint h)
    : ui::panel::panel(c, w, h), ui::composite::composite(c, w, h),
      child_spacing(0, 0)
{
    this->resize = ui::resize::all;

    this->add_callback(ui::callback::leave,
                       ui::manager::leave_callback, NULL);
    this->add_callback(ui::callback::motion,
                       ui::manager::motion_callback, NULL);
    this->add_callback(ui::callback::btn_down,
                       ui::manager::button_callback, NULL);
    this->add_callback(ui::callback::btn_up,
                       ui::manager::button_callback, NULL);
    this->add_callback(ui::callback::key_down,
                       ui::manager::keypress_callback, NULL);
    this->add_callback(ui::callback::key_up,
                       ui::manager::keypress_callback, NULL);
}

ui::manager::~manager()
{
    while (this->children.size())
        this->children.front()->close();
}

int ui::manager::get(GLuint e, GLuint t, void *v)
{
    switch (e)
    {
      case ui::element::attribute:
      case ui::element::pixel_size:
        if (this->composite::parent != NULL)
            /* Eventually, the context will be somebody's parent */
            return this->composite::parent->get(e, t, v);
        break;

      case ui::element::transform:      return this->get_transform(t, v);
      case ui::element::child_spacing:  return this->get_child_spacing(t, v);
      case ui::element::resize:         return this->get_resize(t, v);
      default:                          return this->panel::get(e, t, v);
    }
    return 1;
}

void ui::manager::set(GLuint e, GLuint t, void *v)
{
    switch (e)
    {
      case ui::element::child_spacing:
        this->set_child_spacing(t, v);
        this->populate_buffers();
        break;

      case ui::element::resize:
        this->set_resize(t, v);
        break;

      case ui::element::size:
        this->panel::set(e, t, v);
        this->composite::set(e, t, v);
        break;

      default:
        this->panel::set(e, t, v);
        break;
    }
}

void ui::manager::draw(void)
{
    glm::mat4 t;
    GLuint tu;

    this->panel::draw();

    if (this->composite::parent == NULL)
        return;

    /* Our children need to be drawn in our coord space. */
    this->composite::parent->get(ui::element::attribute,
                                 ui::attribute::translate,
                                 &tu);
    glUniformMatrix4fv(tu, 1, GL_FALSE, glm::value_ptr(this->translate));
    for (auto i = this->children.begin(); i != this->children.end(); ++i)
        (*i)->draw();

    /* Reset the uniform to what it was when we got here, in case
     * we're not the only child of our parent.
     */
    this->composite::parent->get(ui::element::transform,
                                 ui::transform::translate,
                                 &t);
    glUniformMatrix4fv(tu, 1, GL_FALSE, glm::value_ptr(t));
}

void ui::manager::add_child(ui::panel *p)
{
    this->composite::add_child(p);
    this->set_desired_size();
}

void ui::manager::remove_child(ui::panel *p)
{
    this->composite::remove_child(p);
    this->set_desired_size();
}

void ui::manager::move_child(ui::panel *p)
{
    this->composite::move_child(p);
    this->set_desired_size();
}
