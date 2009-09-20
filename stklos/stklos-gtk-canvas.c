/*
 * stklos-gtk-canvas.c				-- Canvas for GTklos
 * 
 * Copyright © 2009 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 * 
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, 
 * USA.
 * 
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 19-Aug-2009 20:15 (eg)
 * Last file update: 20-Sep-2009 22:35 (eg)
 */

#include <stklos.h>
#ifdef HAVE_GOO
#  include <goocanvas.h>
#endif


static void error_bad_polyline(SCM obj)
{
  STk_error("bad Goo canvas polyline ~S", obj);
}

DEFINE_PRIMITIVE("goo-polyline-get-points", goocanv_get_points, subr1, (SCM line))
{
  SCM res = STk_nil;
#ifdef HAVE_GOO
  GooCanvasPoints* p;
  int i, len;

  if (!CPOINTERP(line) || CPOINTER_TYPE(line) != STk_intern("goo-canvas-polyline"))
    error_bad_polyline(line);
  
  g_object_get(G_OBJECT(CPOINTER_VALUE(line)), "points", &p, NULL);
  len = p->num_points * 2;
  for (i =  len-1 ; i >= 0; i--) {
    res = STk_cons(STk_double2real(p->coords[i]), res);
  }
  goo_canvas_points_unref(p);
#endif
  return res;
}
  
DEFINE_PRIMITIVE("goo-polyline-set-points!", goocanv_set_points, subr2, 
		 (SCM line, SCM lst))
{
#ifdef HAVE_GOO
  int i, len = STk_int_length(lst);
  SCM tmp = STk_nil;
  GooCanvasPoints* p;
  
  if (!CPOINTERP(line) || CPOINTER_TYPE(line) != STk_intern("goo-canvas-polyline"))
    STk_error("bad Goo canvas polyline ~S", line);

  if (len < 0) STk_error("bad list ~S", lst);
  if ((len % 2) != 0) STk_error("number of coordinates in ~S must be even", lst);
  
  p = goo_canvas_points_new(len / 2);
  goo_canvas_points_ref(p);
  
  for (i = 0; !NULLP(lst) ; lst = CDR(lst), i++) {
    double d = STk_number2double(CAR(lst));

    if (isnan(d)) STk_error("bad real number ~S", CAR(lst));
    p->coords[i] = d;
  }
  g_object_set(G_OBJECT(CPOINTER_VALUE(line)), "points", p, NULL);
  goo_canvas_points_ref(p);
#endif
  return STk_void;
} 

/* ----------------------------------------------------------------------
 * 
 * 	Module posix starts here
 *
 * ---------------------------------------------------------------------- 
 */
#include "stklos-gtk-canvas-inc.c"

MODULE_ENTRY_START("stklos-gtk-canvas")
{
  SCM module = STk_create_module(STk_intern("stklos-gtk-canvas"));

  ADD_PRIMITIVE_IN_MODULE(goocanv_get_points, module);
  ADD_PRIMITIVE_IN_MODULE(goocanv_set_points, module);

  /* Execute Scheme code */
  STk_execute_C_bytecode(__module_consts, __module_code);
} MODULE_ENTRY_END 

MODULE_ENTRY_INFO() {
   return STk_read_from_C_string(__module_infos);
}

