/*
  span-bar.cc -- implement Span_bar

  source file of the GNU LilyPond music typesetter

  (c)  1997--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#include "span-bar.hh"
#include "lookup.hh"
#include "dimensions.hh"
#include "paper-def.hh"
#include "molecule.hh"
#include "warn.hh"
#include "axis-group-interface.hh"
#include "group-interface.hh"
#include "score-element.hh"
#include "bar.hh"

void
Span_bar::add_bar (Score_element*me, Score_element*b)
{
  Pointer_group_interface gi (me);
  gi.add_element (b);

  me->add_dependency (b);
}

MAKE_SCHEME_CALLBACK(Span_bar,width_callback,2);
SCM
Span_bar::width_callback (SCM element_smob, SCM scm_axis)
{
  Score_element *se = unsmob_element (element_smob);
  Axis a = (Axis) gh_scm2int (scm_axis);
  assert (a == X_AXIS);
  String gl = ly_scm2string (se->get_elt_property ("glyph"));

  /*
    urg.
   */
  Molecule m = Bar::compound_barline (se, gl, 40 PT);
  
  return ly_interval2scm ( m.extent (X_AXIS));
}

MAKE_SCHEME_CALLBACK(Span_bar,before_line_breaking,1);
SCM
Span_bar::before_line_breaking (SCM smob)
{
  evaluate_empty (unsmob_element (smob));
  evaluate_glyph (unsmob_element (smob));

  /*
    no need to call   Bar::before_line_breaking (), because the info
    in ELEMENTS already has been procced by Bar::before_line_breaking().
   */
  return SCM_UNSPECIFIED;
}

MAKE_SCHEME_CALLBACK(Span_bar,center_on_spanned_callback,2);
SCM
Span_bar::center_on_spanned_callback (SCM element_smob, SCM axis)
{
  Score_element *me = unsmob_element (element_smob);
  Axis a = (Axis) gh_scm2int (axis);
  assert (a == Y_AXIS);
  Interval i (get_spanned_interval (me));

  /*
    Bar::brew_molecule delivers a barline of y-extent (-h/2,h/2), so
    we have to translate ourselves to be in the center of the 
    interval that we span.  */

  return gh_double2scm (i.center ());
}

void
Span_bar::evaluate_empty (Score_element*me)
{
  /*
    TODO: filter all hara-kiried out of ELEMENS list, and then
    optionally do suicide. Call this cleanage function from
    center_on_spanned_callback() as well.
    
   */
  if (!gh_pair_p (me->get_elt_property ("elements")))
    {
      me->suicide ();
    }
}

void
Span_bar::evaluate_glyph (Score_element*me)
{
  SCM elts = me->get_elt_property ("elements");
  Score_element * b = unsmob_element (gh_car (elts));
  SCM glsym =ly_symbol2scm ("glyph");
  SCM gl =b ->get_elt_property (glsym);
  if (!gh_string_p (gl))
    {
      me->suicide ();
      return ; 
    }

  String type = ly_scm2string (gl);
  
  if (type == "|:") 
    {
      type = ".|";
    }
  else if (type== ":|")
    {
      type = "|.";
    }
  else if (type== ":|:")
    {
      type = ".|.";
    }

  gl = ly_str02scm (type.ch_C());
  if (scm_equal_p (me->get_elt_property (glsym), gl) != SCM_BOOL_T)
    me->set_elt_property (glsym, gl);
}

Interval
Span_bar::get_spanned_interval (Score_element*me) 
{
  return ly_scm2interval (Axis_group_interface::group_extent_callback (me->self_scm(), gh_int2scm (Y_AXIS))); 
}


MAKE_SCHEME_CALLBACK(Span_bar,get_bar_size,1);
SCM
Span_bar::get_bar_size (SCM smob)
{
  Score_element* me =  unsmob_element (smob);
  Interval iv (get_spanned_interval (me));
  if (iv.empty_b ())
    {
      /*
	This happens if the bars are hara-kiried from under us.
       */
      me->suicide ();
      return gh_double2scm (-1);
    }
  return gh_double2scm (iv.length ());
}
void
Span_bar::set_interface (Score_element *me)
{
  Bar::set_interface (me);
  
  me->set_interface (ly_symbol2scm ("span-bar-interface"));
  me->set_extent_callback (SCM_EOL, Y_AXIS);
}

bool
Span_bar::has_interface (Score_element*m)
{
  return m && m->has_interface (ly_symbol2scm ("span-bar-interface"));
}
