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

#ifndef __T_CANVAS_H__
#define __T_CANVAS_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define T_TYPE_CANVAS t_canvas_get_type()

#define T_CANVAS(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), T_TYPE_CANVAS, TCanvas))

#define T_CANVAS_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), T_TYPE_CANVAS, TCanvasClass))

#define T_IS_CANVAS(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), T_TYPE_CANVAS))

#define T_IS_CANVAS_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), T_TYPE_CANVAS))

#define T_CANVAS_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), T_TYPE_CANVAS, TCanvasClass))

typedef struct {
  GtkDrawingAreaClass parent;
} TCanvas;

typedef struct {
  GtkDrawingAreaClass parent_class;
} TCanvasClass;

GType t_canvas_get_type (void);

TCanvas* t_canvas_new (void);

G_END_DECLS

#endif /* __T_CANVAS_H__ */

/* t-canvas.c */

