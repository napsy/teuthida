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

#ifndef __TEUTHIDA_MAIN_H__
#define __TEUTHIDA_MAIN_H__

struct teuthida_main_s {
    GtkWidget *window;
    GtkWidget *box_main,
              *paned_main;
    GtkWidget *item_view;
};

struct teuthida_main_s *teuthida_main;


void
teuthida_init();

#endif /* __TEUTHIDA_MAIN_H__ */

