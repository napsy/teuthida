/*
 * Teuthida
 * Copyright (C) 2009  Luka Napotnik <luka.napotnik@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __DOCUMENT_NEW_H__
#define __DOCUMENT_NEW_H__

#include <gtk/gtk.h>
#include "t-canvas.h"

struct document_new_s {
    GtkWidget *window;
    GtkWidget *button_ok, *button_cancel;
    GtkWidget *box, *button_box, *box_orient;
    GtkWidget *spin_width, *spin_height;
    GtkWidget *combo_format;
    GtkWidget *label_width, *label_height, *label_format, *label_orient;
    GtkWidget *radio_horizontal, *radio_vertical;
    TCanvas *canvas;
    gint width;
    gint height;
};

struct document_new_s *t_document_new;
void
document_new_show();

#endif /* __DOCUMENT_NEW_H__ */

