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

#ifndef __DOCUMENT_H__
#define __DOCUMENT_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _DocumentPrivate DocumentPrivate;

typedef struct {
    GObject parent;

    DocumentPrivate *priv;
} Document;

typedef struct {
    GObjectClass parent;
} DocumentClass;

#define DOCUMENT_TYPE (document_get_type ())
#define DOCUMENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), DOCUMENT_TYPE, Document))
#define DOCUMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), DOCUMENT_TYPE, DocumentClass))
#define IS_DOCUMENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DOCUMENT_TYPE))
#define IS_DOCUMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), DOCUMENT_TYPE))
#define DOCUMENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), DOCUMENT_TYPE, DocumentClass))

/* Document properties. */
enum {
    DOCUMENT_WIDTH = 1,
    DOCUMENT_HEIGHT,
    DOCUMENT_TITLE,
};

G_END_DECLS


Document *
document_new(gint w,
             gint h,
             const gchar *title);


#endif /* __DOCUMENT_H__ */

