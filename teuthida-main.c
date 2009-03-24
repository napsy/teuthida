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
#include "document-new.h"
#include "t-canvas.h"

const char MENU_XML[] = "<ui><menubar name=\"MenuBar\"><menu action=\"FileMenuAction\"><menuitem name=\"New\" action=\"FileNewAction\" /><separator /><menuitem name=\"Quit\" action=\"FileQuitAction\" /></menu><menu action=\"EditMenuAction\"><menuitem name=\"Cut\" action=\"EditCutAction\" /></menu><menu name=\"View\" action=\"ViewMenuAction\"><menuitem name=\"GridMenu\" action=\"ViewGridAction\" /></menu><menu action=\"HelpMenuAction\"><menuitem name=\"About\" action=\"HelpAboutAction\" /></menu></menubar></ui>";

void
teuthida_menu_file_new(GtkAction *action, gpointer data)
{
    TCanvas *canvas = (TCanvas *)data;
    document_new_show(canvas);
}

void
teuthida_menu_help_about(GtkAction *action, gpointer data)
{
    gtk_show_about_dialog (NULL, 
                       "program-name", "Teuthida",
                       "version", "0.0.1-pre",
                       "comments", "Warning: pre-alpha software!",
                       "copyright", "Copyright (C) 2009 Luka Napotnik",
                       "title", "About Teuthida",
                       NULL);
}

void
teuthida_menu_view_grid(GtkAction *action, gpointer data)
{
    TCanvas *canvas = (TCanvas *)data;
    printf("GRID\n");
    t_canvas_set_grid(canvas, TRUE);
}

GtkWidget *
teuthida_menu(TCanvas *canvas)
{
    GtkUIManager *manager;
    GtkWidget *ui;
    GError *error = NULL;
    GtkAction *action;
    GtkActionGroup *action_group;
    GtkWidget *item, *check_grid;

    manager = gtk_ui_manager_new();


    check_grid = gtk_check_button_new();
    action_group = gtk_action_group_new("FileActions");

    /* File Menu. */
    action = gtk_action_new("FileMenuAction", "_File", NULL, NULL);
    gtk_action_group_add_action(action_group, action);
    action = gtk_action_new("FileNewAction", "_New Document", NULL, GTK_STOCK_NEW);
    gtk_action_group_add_action(action_group, action);
    g_signal_connect(G_OBJECT(action), "activate",
        G_CALLBACK(teuthida_menu_file_new), canvas);
    action = gtk_action_new("FileQuitAction", "_Quit", NULL, GTK_STOCK_QUIT);
    gtk_action_group_add_action(action_group, action);
    g_signal_connect(G_OBJECT(action), "activate",
        G_CALLBACK(gtk_main_quit), NULL);

    /* Edit Menu. */
    action = gtk_action_new("EditMenuAction", "_Edit", NULL, NULL);
    gtk_action_group_add_action(action_group, action);
    action = gtk_action_new("EditCutAction", "_Cut", NULL, GTK_STOCK_CUT);
    gtk_action_group_add_action(action_group, action);
    
    /* View Menu. */
    action = gtk_action_new("ViewMenuAction", "_View", NULL, NULL);
    gtk_action_group_add_action(action_group, action);
    action = gtk_action_new("ViewGridAction", "Show Grid", NULL, NULL);
    item = gtk_action_create_menu_item(action);
    gtk_action_disconnect_proxy(action, item);
    gtk_action_connect_proxy(action, check_grid);
    gtk_action_group_add_action(action_group, action);
    g_signal_connect(G_OBJECT(action), "activate",
        G_CALLBACK(teuthida_menu_view_grid), canvas);



    /* Help Menu. */
    action = gtk_action_new("HelpMenuAction", "_Help", NULL, NULL);
    gtk_action_group_add_action(action_group, action);
    action = gtk_action_new("HelpAboutAction", "_About", NULL, GTK_STOCK_ABOUT);
    gtk_action_group_add_action(action_group, action);

    g_signal_connect(G_OBJECT(action), "activate",
        G_CALLBACK(teuthida_menu_help_about), NULL);

    gtk_ui_manager_insert_action_group(manager, action_group, 0);

    gtk_ui_manager_add_ui_from_string(manager, MENU_XML, -1, &error);
    if (error)
        printf("Error: %s\n", error->message);

    ui = gtk_ui_manager_get_widget(manager, "/MenuBar");
    if (!ui)
        printf("Fail!!\n");


    return ui;
}

void
teuthida_init()
{
    GtkWidget *canvas, *menu;

    teuthida_main = g_malloc(sizeof(*teuthida_main));

    teuthida_main->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    teuthida_main->paned_main = gtk_hpaned_new();
    teuthida_main->scroll = gtk_scrolled_window_new(NULL, NULL);
    teuthida_main->box_main = gtk_vbox_new(FALSE, 2);
    teuthida_main->item_view = gtk_tree_view_new();

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(teuthida_main->scroll),
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    teuthida_main->document = document_new(640, 480, "Untitled");
    t_document_new = NULL;

    canvas = GTK_WIDGET(t_canvas_new(teuthida_main->document));
    menu = teuthida_menu((TCanvas *)canvas);

    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(teuthida_main->scroll),
            canvas);
    gtk_box_pack_start(GTK_BOX(teuthida_main->box_main), menu, FALSE, FALSE, 2);
    gtk_paned_add1(GTK_PANED(teuthida_main->paned_main), teuthida_main->item_view);
    gtk_paned_add2(GTK_PANED(teuthida_main->paned_main), teuthida_main->scroll);

    gtk_paned_set_position(GTK_PANED(teuthida_main->paned_main), 150);
    gtk_box_pack_start(GTK_BOX(teuthida_main->box_main), teuthida_main->paned_main,
            TRUE, TRUE, 2);




    gtk_window_set_title(GTK_WINDOW(teuthida_main->window), "Teuthida");
    g_signal_connect(G_OBJECT(teuthida_main->window), "destroy", gtk_main_quit, NULL);
    gtk_window_set_default_size(GTK_WINDOW(teuthida_main->window), 700, 600);
    gtk_container_add(GTK_CONTAINER(teuthida_main->window), teuthida_main->box_main);
    gtk_widget_show_all(teuthida_main->window);
}

