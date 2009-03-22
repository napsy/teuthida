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
#include "document.h"

G_DEFINE_TYPE (Document, document, G_TYPE_OBJECT);

#define DOCUMENT_GET_PRIVATE(o)\
    (G_TYPE_INSTANCE_GET_PRIVATE ((o), DOCUMENT_TYPE, DocumentPrivate))

struct _DocumentPrivate {
    gint width, height;
    gchar *title;
};

void
document_set_property(GObject        *object,
                      guint           property_id,
                      const GValue   *value,
                      GParamSpec     *pspec)
{
    Document *doc = DOCUMENT(object);
    DocumentPrivate *priv;
    priv = DOCUMENT_GET_PRIVATE (doc);
    switch (property_id) {
        case DOCUMENT_WIDTH:
            priv->width = g_value_get_uint(value);
            break;
        case DOCUMENT_HEIGHT:
            priv->height = g_value_get_uint(value);
            break;
        case DOCUMENT_TITLE:
            g_free(priv->title);
            priv->title = g_value_dup_string(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

void
document_get_property(GObject        *object,
                      guint           property_id,
                      GValue         *value,
                      GParamSpec     *pspec)
{
    Document *doc = DOCUMENT(object);
    DocumentPrivate *priv;
    priv = DOCUMENT_GET_PRIVATE (doc);
    switch (property_id) {
        case DOCUMENT_WIDTH:
            g_value_set_uint(value, priv->width);
            break;
        case DOCUMENT_HEIGHT:
            g_value_set_uint(value, priv->height);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

static void
document_dispose (Document *self)
{
}

static void
document_finalize (Document *self)
{
}

static void
document_init (Document *self)
{
    DocumentPrivate *priv;
    priv = DOCUMENT_GET_PRIVATE (self);
}

static void
document_class_init (DocumentClass *self_class)
{
    GObjectClass *object_class = G_OBJECT_CLASS (self_class);
    GParamSpec *param_spec;

    g_type_class_add_private (self_class, sizeof (DocumentPrivate));
    object_class->dispose = (void (*) (GObject *object)) document_dispose;
    object_class->finalize = (void (*) (GObject *object)) document_finalize;
    object_class->set_property = document_set_property;
    object_class->get_property = document_get_property;

    /* Define document properties. */
    param_spec = g_param_spec_uint("width", "width", "Document width",
            1, 3000, 640, G_PARAM_READABLE | G_PARAM_WRITABLE);
    g_object_class_install_property(object_class, DOCUMENT_WIDTH, param_spec);
    param_spec = g_param_spec_uint("height", "height", "Document height",
            1, 3000, 480, G_PARAM_READABLE | G_PARAM_WRITABLE);
    g_object_class_install_property(object_class, DOCUMENT_HEIGHT, param_spec);
    param_spec = g_param_spec_string("title", "title", "Document title",
            "Untitled", G_PARAM_READABLE | G_PARAM_WRITABLE);
    g_object_class_install_property(object_class, DOCUMENT_TITLE, param_spec);
}
Document *
document_new(gint w,
             gint h,
             const gchar *title)
{
    Document *obj = g_object_new(DOCUMENT_TYPE, NULL);

    g_object_set(G_OBJECT(obj), "width", w, "height", h, NULL);
    return obj;
}

