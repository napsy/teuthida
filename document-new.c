#include "document-new.h"

void
document_new_ok_clicked(GtkButton *button, gpointer data)
{
    gtk_widget_hide(document_new->window);
    gtk_widget_destroy(document_new->window);
}

void
document_new_cancel_clicked(GtkButton *button, gpointer data)
{
    gtk_widget_hide(document_new->window);
    gtk_widget_destroy(document_new->window);
}
void
document_new_show()
{
    if (!document_new) 
        document_new = g_malloc(sizeof(*document_new));

    document_new->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    document_new->box = gtk_vbox_new(FALSE, 2);

    document_new->label_format = gtk_label_new("Format:");
    document_new->label_width = gtk_label_new("Width:");
    document_new->label_height = gtk_label_new("Height:");
    document_new->spin_width = gtk_spin_button_new_with_range(1, 5000, 1);
    document_new->spin_height = gtk_spin_button_new_with_range(1, 5000, 1);
    document_new->combo_format = gtk_combo_box_new_text();

    gtk_misc_set_alignment(GTK_MISC(document_new->label_format), 0.0, 0.0);
    gtk_misc_set_alignment(GTK_MISC(document_new->label_width), 0.0, 0.0);
    gtk_misc_set_alignment(GTK_MISC(document_new->label_height), 0.0, 0.0);

    gtk_combo_box_append_text(GTK_COMBO_BOX(document_new->combo_format),
            "A4 paper");
    gtk_combo_box_append_text(GTK_COMBO_BOX(document_new->combo_format),
            "A5 paper");
    gtk_combo_box_append_text(GTK_COMBO_BOX(document_new->combo_format),
            "Letter");
    gtk_combo_box_append_text(GTK_COMBO_BOX(document_new->combo_format),
            "Custom");


    gtk_widget_set_sensitive(document_new->spin_width, FALSE);
    gtk_widget_set_sensitive(document_new->spin_height, FALSE);

    gtk_box_pack_start(GTK_BOX(document_new->box), document_new->label_format,
            FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(document_new->box), document_new->combo_format,
            FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(document_new->box), document_new->label_width,
            FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(document_new->box), document_new->spin_width,
            FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(document_new->box), document_new->label_height,
            FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(document_new->box), document_new->spin_height,
            FALSE, FALSE, 2);

    document_new->button_ok = gtk_button_new_from_stock(GTK_STOCK_OK);
    g_signal_connect(G_OBJECT(document_new->button_ok), "clicked",
            G_CALLBACK(document_new_ok_clicked), NULL);
    document_new->button_cancel = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    g_signal_connect(G_OBJECT(document_new->button_cancel), "clicked",
            G_CALLBACK(document_new_cancel_clicked), NULL);

    document_new->button_box = gtk_hbox_new(FALSE, 2);
    gtk_box_pack_end(GTK_BOX(document_new->button_box), document_new->button_ok,
            FALSE, FALSE, 2);
    gtk_box_pack_end(GTK_BOX(document_new->button_box), document_new->button_cancel,
            FALSE, FALSE, 2);



    gtk_box_pack_end(GTK_BOX(document_new->box), document_new->button_box, FALSE, FALSE, 2);
    gtk_window_set_title(GTK_WINDOW(document_new->window), "New Document");

    g_signal_connect(G_OBJECT(document_new->window), "delete-event",
            G_CALLBACK(document_new_cancel_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(document_new->window), document_new->box);
    gtk_container_set_border_width(GTK_CONTAINER(document_new->window), 3);
    gtk_window_set_default_size(GTK_WINDOW(document_new->window), 400, 200);
    gtk_window_set_position(GTK_WINDOW(document_new->window), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(document_new->window);
}

