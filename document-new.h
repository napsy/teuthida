#ifndef __DOCUMENT_NEW_H__
#define __DOCUMENT_NEW_H__

#include <gtk/gtk.h>

struct document_new_s {
    GtkWidget *window;
    GtkWidget *button_ok, *button_cancel;
    GtkWidget *box, *button_box;
    GtkWidget *spin_width, *spin_height;
    GtkWidget *combo_format;
    GtkWidget *label_width, *label_height, *label_format;
};

struct document_new_s *document_new = NULL;
void
document_new_show();

#endif /* __DOCUMENT_NEW_H__ */

