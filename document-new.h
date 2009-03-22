#ifndef __DOCUMENT_NEW_H__
#define __DOCUMENT_NEW_H__

#include <gtk/gtk.h>
#include "t-canvas.h"

struct document_new_s {
    GtkWidget *window;
    GtkWidget *button_ok, *button_cancel;
    GtkWidget *box, *button_box;
    GtkWidget *spin_width, *spin_height;
    GtkWidget *combo_format;
    GtkWidget *label_width, *label_height, *label_format;
    TCanvas *canvas;
    gint width;
    gint height;
};

struct document_new_s *t_document_new;
void
document_new_show();

#endif /* __DOCUMENT_NEW_H__ */

