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

#include "document-new.h"
#include "document.h"
#include "t-canvas.h"

void
t_document_combo_format_changed(GtkComboBox *combo, gpointer data)
{
    int choice = gtk_combo_box_get_active(combo);
    
    if (choice == 3) {/* Custom */
        gtk_widget_set_sensitive(t_document_new->spin_width, TRUE);
        gtk_widget_set_sensitive(t_document_new->spin_height, TRUE);
    } else {
        gtk_widget_set_sensitive(t_document_new->spin_width, FALSE);
        gtk_widget_set_sensitive(t_document_new->spin_height, FALSE);
    }
}

void
t_document_new_ok_clicked(GtkButton *button, gpointer data)
{

    gint w, h;
    int choice = gtk_combo_box_get_active(GTK_COMBO_BOX(t_document_new->combo_format));
    Document *document;
    
    switch (choice) {
        case 0: /* A4 paper */
            w = 400;
            h = 600;
            break;
        case 1: /* A5 paper */
            w = 300;
            h = 500;
            break;
        case 2: /* Letter */
            w = 350;
            h = 450;
            break;
        case 3: /* Custom */
            w = (gint)gtk_spin_button_get_value(GTK_SPIN_BUTTON(t_document_new->spin_width));
            h = (gint)gtk_spin_button_get_value(GTK_SPIN_BUTTON(t_document_new->spin_height));
            break;
    }
            
    document = document_new(w, h, "Untitled");
    t_canvas_change_document(t_document_new->canvas, document);
    gtk_widget_hide(t_document_new->window);
    gtk_widget_destroy(t_document_new->window);
}

void
t_document_new_cancel_clicked(GtkButton *button, gpointer data)
{
    gtk_widget_hide(t_document_new->window);
    gtk_widget_destroy(t_document_new->window);
}
void
document_new_show(TCanvas *canvas)
{
    if (!t_document_new) 
        t_document_new = g_malloc(sizeof(*t_document_new));

    t_document_new->canvas = canvas;
    t_document_new->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    t_document_new->box = gtk_vbox_new(FALSE, 2);

    t_document_new->label_format = gtk_label_new("Format:");
    t_document_new->label_width = gtk_label_new("Width:");
    t_document_new->label_height = gtk_label_new("Height:");
    t_document_new->label_orient = gtk_label_new("Orientation:");
    t_document_new->spin_width = gtk_spin_button_new_with_range(1, 5000, 1);
    t_document_new->spin_height = gtk_spin_button_new_with_range(1, 5000, 1);
    t_document_new->combo_format = gtk_combo_box_new_text();
    t_document_new->radio_horizontal = gtk_radio_button_new_with_label(NULL, "Horizontal");
    t_document_new->radio_vertical = 
        gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(t_document_new->radio_horizontal)), "Vertical");

    t_document_new->box_orient = gtk_hbox_new(FALSE, 2);
    gtk_box_pack_start(GTK_BOX(t_document_new->box_orient),
            t_document_new->radio_horizontal, FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(t_document_new->box_orient),
            t_document_new->radio_vertical, FALSE, FALSE, 2);
    g_signal_connect(G_OBJECT(t_document_new->combo_format), "changed",
            G_CALLBACK(t_document_combo_format_changed), NULL);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(t_document_new->spin_width), 640);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(t_document_new->spin_height), 480);
    gtk_misc_set_alignment(GTK_MISC(t_document_new->label_format), 0.0, 0.0);
    gtk_misc_set_alignment(GTK_MISC(t_document_new->label_width), 0.0, 0.0);
    gtk_misc_set_alignment(GTK_MISC(t_document_new->label_height), 0.0, 0.0);
    gtk_misc_set_alignment(GTK_MISC(t_document_new->label_orient), 0.0, 0.0);

    gtk_combo_box_append_text(GTK_COMBO_BOX(t_document_new->combo_format),
            "A4 paper");
    gtk_combo_box_append_text(GTK_COMBO_BOX(t_document_new->combo_format),
            "A5 paper");
    gtk_combo_box_append_text(GTK_COMBO_BOX(t_document_new->combo_format),
            "Letter");
    gtk_combo_box_append_text(GTK_COMBO_BOX(t_document_new->combo_format),
            "Custom");

    gtk_combo_box_set_active(GTK_COMBO_BOX(t_document_new->combo_format), 0);

    gtk_widget_set_sensitive(t_document_new->spin_width, FALSE);
    gtk_widget_set_sensitive(t_document_new->spin_height, FALSE);

    gtk_box_pack_start(GTK_BOX(t_document_new->box), t_document_new->label_format,
            FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(t_document_new->box), t_document_new->combo_format,
            FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(t_document_new->box), t_document_new->label_width,
            FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(t_document_new->box), t_document_new->spin_width,
            FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(t_document_new->box), t_document_new->label_height,
            FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(t_document_new->box), t_document_new->spin_height,
            FALSE, FALSE, 2);

    t_document_new->button_ok = gtk_button_new_from_stock(GTK_STOCK_OK);
    g_signal_connect(G_OBJECT(t_document_new->button_ok), "clicked",
            G_CALLBACK(t_document_new_ok_clicked), NULL);
    t_document_new->button_cancel = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    g_signal_connect(G_OBJECT(t_document_new->button_cancel), "clicked",
            G_CALLBACK(t_document_new_cancel_clicked), NULL);

    t_document_new->button_box = gtk_hbox_new(FALSE, 2);
    gtk_box_pack_end(GTK_BOX(t_document_new->button_box), t_document_new->button_ok,
            FALSE, FALSE, 2);
    gtk_box_pack_end(GTK_BOX(t_document_new->button_box), t_document_new->button_cancel,
            FALSE, FALSE, 2);



    gtk_box_pack_start(GTK_BOX(t_document_new->box), t_document_new->label_orient, FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(t_document_new->box), t_document_new->box_orient, FALSE, FALSE, 2);
    gtk_box_pack_end(GTK_BOX(t_document_new->box), t_document_new->button_box, FALSE, FALSE, 2);
    gtk_window_set_title(GTK_WINDOW(t_document_new->window), "New Document");

    g_signal_connect(G_OBJECT(t_document_new->window), "delete-event",
            G_CALLBACK(t_document_new_cancel_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(t_document_new->window), t_document_new->box);
    gtk_container_set_border_width(GTK_CONTAINER(t_document_new->window), 3);
    gtk_window_set_default_size(GTK_WINDOW(t_document_new->window), 400, 200);
    gtk_window_set_position(GTK_WINDOW(t_document_new->window), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(t_document_new->window);
}

