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
#include "t-canvas.h"
#include "document.h"


G_DEFINE_TYPE (TCanvas, t_canvas, GTK_TYPE_DRAWING_AREA)

#define GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((o), T_TYPE_CANVAS, TCanvasPrivate))

typedef struct _TCanvasPrivate TCanvasPrivate;

struct _TCanvasPrivate {
    gint events;
    gint border;
    gdouble click_src_x, click_src_y,
            click_cur_x, click_cur_y;
    gint width, height;
    gboolean show_grid;
    Document *document;

    /* Image masks. */
    cairo_surface_t *grid_mask, *paper_mask;
};

static gboolean
t_canvas_button_press(GtkWidget *widget, GdkEventButton *e)
{
    TCanvasPrivate *priv = GET_PRIVATE(widget);
    priv->events |= GDK_BUTTON_PRESS_MASK;
    priv->click_src_x = e->x;
    priv->click_src_y = e->y;
    return TRUE;
}


static gboolean
t_canvas_button_release(GtkWidget *widget, GdkEventButton *e)
{
    TCanvasPrivate *priv = GET_PRIVATE(widget);
    priv->events ^= GDK_BUTTON_PRESS_MASK;
    priv->click_src_x = priv->click_src_y = 0;
    gtk_widget_queue_draw(widget);
    return TRUE;
}

static gboolean
t_canvas_mouse_move(GtkWidget *widget, GdkEventMotion *e)
{
    TCanvasPrivate *priv = GET_PRIVATE(widget);

    if ((priv->events & GDK_BUTTON_PRESS_MASK) == GDK_BUTTON_PRESS_MASK) {
        priv->click_cur_x = e->x;
        priv->click_cur_y = e->y;
        gtk_widget_queue_draw(widget);
    }
    return TRUE;
}

void
t_canvas_draw_grid(GtkWidget *widget, cairo_t *cr, gint w, gint h)
{
    double dashes[] = {0.2, 0.7, 1.0, 0.5};
    TCanvasPrivate *priv = GET_PRIVATE(widget);
    int x, y;
    cairo_surface_t *surface;
    cairo_t *mask_cr;
    
    if (!priv->grid_mask) {
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
        mask_cr = cairo_create(surface);
#if 0
        cairo_iirectangle(mask_cr, 0, 0, w, h);
        cairo_fill(mask_cr);
#endif
        cairo_set_source_rgb(mask_cr, 0.65, 0.65, 0.65);
        cairo_set_line_width(mask_cr, 1.0);
        cairo_set_dash(mask_cr, dashes, 4, 0);
        for (x = priv->border; x < w; x+=10) {
            cairo_move_to(mask_cr, x, priv->border);
            cairo_line_to(mask_cr, x, h-7);
        }
        for (y = priv->border; y < h; y+=10) {
            cairo_move_to(mask_cr, priv->border, y);
            cairo_line_to(mask_cr, w-7, y);
        }
        cairo_stroke(mask_cr);
        cairo_surface_flush(surface);
        //cairo_surface_finish(surface);
        priv->grid_mask = surface;
        //cairo_destroy(mask_cr);
    }
    //cairo_set_source_rgb(cr, 0, 0, 0);
    //cairo_paint_with_alpha(cr, 0.0);
    //cairo_mask_surface(cr, priv->grid_mask, 0, 0);
    cairo_set_source_surface(cr, priv->grid_mask, 0, 0);
    cairo_paint(cr);
}

void
t_canvas_draw_paper(GtkWidget *widget, cairo_t *cr, int w, int h)
{
    TCanvasPrivate *priv = GET_PRIVATE(widget);
    cairo_surface_t *surface;
    cairo_t *mask_cr;
    
    if (!priv->paper_mask) {
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
        mask_cr = cairo_create(surface);

        /* Canvas shadow. */
        cairo_set_source_rgb(mask_cr, 0.5, 0.5, 0.5);
        cairo_rectangle(mask_cr, priv->border+7, priv->border+7, 
                w + priv->border+7, h + priv->border+7);
        cairo_fill(mask_cr);
        /* Canvas workspace. */
        cairo_set_source_rgb(mask_cr, 0, 0, 0);
        cairo_rectangle(mask_cr, priv->border, priv->border, 
                w - priv->border-7, h - priv->border-7);

        cairo_stroke(mask_cr);
        cairo_set_source_rgb(mask_cr, 1, 1, 1);
        cairo_rectangle(mask_cr, priv->border, priv->border, 
                w - priv->border-7, h - priv->border-7);

        cairo_fill(mask_cr);

        cairo_surface_flush(surface);
        priv->paper_mask = surface;
        cairo_destroy(mask_cr);

    }
    //cairo_set_source_rgb(cr, 1, 1, 1);
    //cairo_paint_with_alpha(cr, 0.0);
    //cairo_mask_surface(cr, priv->paper_mask, 0, 0);
    cairo_set_source_surface(cr, priv->paper_mask, 0, 0);
    cairo_paint(cr);
}

static gboolean
t_canvas_expose(GtkWidget *widget, GdkEventExpose *e)
{
    cairo_t *cr;
    TCanvasPrivate *priv = GET_PRIVATE(widget);
    int w, h;
    cr = gdk_cairo_create(widget->window);

    /* Always use information from the current document. */
    g_object_get(G_OBJECT(priv->document),
            "width", &w, "height", &h, NULL);

    /* Draw the paper. */
    t_canvas_draw_paper(widget, cr, w, h);

    /* Draw grid. */
    if (priv->show_grid)
        t_canvas_draw_grid(widget, cr, w, h);

    if ((priv->events & GDK_BUTTON_PRESS_MASK) == GDK_BUTTON_PRESS_MASK) {
        cairo_set_source_rgba(cr, 0.33, 0.2, 0.7, 0.5);
        cairo_rectangle(cr, priv->click_src_x, priv->click_src_y,
                priv->click_cur_x - priv->click_src_x,
                priv->click_cur_y - priv->click_src_y);
        cairo_stroke(cr);

        cairo_set_source_rgba(cr, 0.43, 0.3, 0.7, 0.5);
        cairo_rectangle(cr, priv->click_src_x, priv->click_src_y,
                priv->click_cur_x - priv->click_src_x,
                priv->click_cur_y - priv->click_src_y);
        cairo_fill(cr);
    }


    cairo_destroy(cr);
    return TRUE;
}

static void
t_canvas_get_property (GObject *object, guint property_id,
                              GValue *value, GParamSpec *pspec)
{
    switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

static void
t_canvas_set_property (GObject *object, guint property_id,
                              const GValue *value, GParamSpec *pspec)
{
    switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

static void
t_canvas_finalize (GObject *object)
{
    GtkWidget *canvas = GTK_WIDGET(object);

    TCanvasPrivate *priv = GET_PRIVATE(canvas);
    if (priv->grid_mask)
        cairo_surface_destroy(priv->grid_mask);
    if (priv->paper_mask)
        cairo_surface_destroy(priv->paper_mask);

    g_object_unref(priv->document);
    G_OBJECT_CLASS (t_canvas_parent_class)->finalize (object);
}

static void
t_canvas_class_init (TCanvasClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

    g_type_class_add_private (klass, sizeof (TCanvasPrivate));
    object_class->get_property = t_canvas_get_property;
    object_class->set_property = t_canvas_set_property;
    object_class->finalize = t_canvas_finalize;


    widget_class->expose_event = t_canvas_expose;
    widget_class->button_press_event = t_canvas_button_press;
    widget_class->button_release_event = t_canvas_button_release;
    widget_class->motion_notify_event = t_canvas_mouse_move;
}

static void
t_canvas_init (TCanvas *self)
{
}

TCanvas*
t_canvas_new(Document *document)
{
    TCanvas *canvas = g_object_new (T_TYPE_CANVAS, NULL);
    GdkColor bg_color;

    TCanvasPrivate *priv = GET_PRIVATE(canvas);
    gtk_widget_set_events(GTK_WIDGET(canvas), GDK_ALL_EVENTS_MASK);
    priv->events = 0;
    priv->border = 20;
    priv->show_grid = FALSE;
    priv->document = document;
    priv->paper_mask = NULL;

    gtk_widget_set_size_request(GTK_WIDGET(canvas), 640+priv->border,
            480+priv->border);
    gtk_widget_set_sensitive(GTK_WIDGET(canvas), TRUE);
    gdk_color_parse("#C1C1C1", &bg_color);
    gtk_widget_modify_bg(GTK_WIDGET(canvas), GTK_STATE_NORMAL, &bg_color);
    return canvas;
}

void
t_canvas_change_document(TCanvas *canvas, Document *document)
{
    gint w,h;
    TCanvasPrivate *priv = GET_PRIVATE(canvas);
    if (priv->document)
        g_object_unref(priv->document);
    if (priv->grid_mask) { /* Destroy the grid mask for the old document. */
        cairo_surface_destroy(priv->grid_mask);
        priv->grid_mask = NULL;
    }
    /* We have to re-paint the paper. */
    cairo_surface_destroy(priv->paper_mask);
    priv->paper_mask = NULL;

    g_object_get(G_OBJECT(document), "width", &w, "height", &h, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(canvas), w+priv->border, h+priv->border);
    priv->document = document;
    gtk_widget_queue_draw(GTK_WIDGET(canvas));
}

void
t_canvas_set_grid(TCanvas *canvas, gboolean show_grid)
{
    TCanvasPrivate *priv = GET_PRIVATE(canvas);
    priv->show_grid = show_grid;
    gtk_widget_queue_draw(GTK_WIDGET(canvas));
}

