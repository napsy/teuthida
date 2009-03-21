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

#include <gtk/gtk.h>
#include "teuthida-main.h"
#include "t-canvas.h"

void
teuthida_init()
{
    GtkWidget *canvas;

    teuthida_main = g_malloc(sizeof(*teuthida_main));

    teuthida_main->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    canvas = GTK_WIDGET(t_canvas_new());

    gtk_window_set_title(GTK_WINDOW(teuthida_main->window), "Teuthida");
    gtk_window_set_default_size(GTK_WINDOW(teuthida_main->window), 500, 600);
    gtk_container_add(GTK_CONTAINER(teuthida_main->window), canvas);
    gtk_widget_show_all(teuthida_main->window);
}

