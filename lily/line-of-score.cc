/*
  scoreline.cc -- implement Line_of_score

  source file of the GNU LilyPond music typesetter

  (c) 1996--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#include "axis-group-interface.hh"
#include "debug.hh"
#include "line-of-score.hh"
#include "main.hh"
#include "paper-column.hh"
#include "paper-def.hh"
#include "paper-outputter.hh"
#include "paper-score.hh"
#include "string.hh"
#include "warn.hh"
#include "dimensions.hh"

Line_of_score::Line_of_score()
{
  set_elt_property ("columns", SCM_EOL);
  set_elt_property ("all-elements", SCM_EOL);

  Axis_group_interface (this).set_interface ();
  Axis_group_interface (this).set_axes (Y_AXIS,X_AXIS);
}


void
Line_of_score::typeset_element (Score_element * elem_p)
{
  elem_p->pscore_l_ = pscore_l_;
  Group_interface (this, "all-elements").add_element (elem_p);
  scm_unprotect_object (elem_p->self_scm_);
}

SCM
Line_of_score::output_lines ()
{
  for (SCM s = get_elt_property ("all-elements");
       gh_pair_p (s); s = gh_cdr (s))
    {
      unsmob_element (gh_car (s))->do_break_processing ();
    }

  for (SCM s = get_elt_property ("all-elements");
       gh_pair_p (s); s = gh_cdr (s))
    {
      unsmob_element (gh_car (s))->handle_broken_dependencies ();
    }
  handle_broken_dependencies ();
  
  for (int i=0; i < broken_into_l_arr_.size (); i++)
    {
      Line_of_score *line_l = dynamic_cast<Line_of_score*> (broken_into_l_arr_[i]);

      progress_indication ("[");
      line_l->post_processing ();
      progress_indication (to_str (i));
      progress_indication ("]");
    }

  SCM list = SCM_EOL; 
  for (int i=broken_into_l_arr_.size (); i--;)
    {
      Line_of_score * l =  dynamic_cast<Line_of_score*> (broken_into_l_arr_[i]);
      list = gh_cons (gh_cdr (l->output_), list);
    }
  return list;
}

// const?
void
Line_of_score::break_into_pieces (Array<Column_x_positions> const &breaking)
{
  for (int i=0; i < breaking.size (); i++)
    {
      Line_of_score *line_l = dynamic_cast <Line_of_score*> (clone());
      line_l->rank_i_ = i;
      Link_array<Paper_column> c (breaking[i].cols_);
      pscore_l_->typeset_line (line_l);
      
      line_l->set_bound(LEFT,c[0]);
      line_l->set_bound(RIGHT,c.top ());
      for (int j=0; j < c.size(); j++)
	{
	  c[j]->translate_axis (breaking[i].config_[j],X_AXIS);
	  c[j]->line_l_ = line_l;
	}
      
      broken_into_l_arr_.push (line_l);
    }
}


void
Line_of_score::output_molecule (SCM expr, Offset o)
{
  SCM offset_sym = ly_symbol2scm ("translate-molecule");
  SCM combine_sym = ly_symbol2scm ("combine-molecule");
enter:

  if (!gh_pair_p (expr))
    return;
  
  SCM head =gh_car (expr);
  if (head == offset_sym)
    {
      o += ly_scm2offset (gh_cadr (expr));
      expr = gh_caddr (expr);
      goto enter;
    }
  else if (head == combine_sym)
    {
      output_molecule (gh_cadr (expr), o);
      expr = gh_caddr (expr);
      goto enter;		// tail recursion
    }
  else
    {
      output_scheme (gh_list (ly_symbol2scm ("placebox"),
			      gh_double2scm (o[X_AXIS]),
			      gh_double2scm (o[Y_AXIS]),
			      expr,
			      SCM_UNDEFINED));
    }
}

void
Line_of_score::output_scheme (SCM s)
{
  gh_set_cdr_x (output_, gh_cons (s, gh_cdr (output_)));
}

void
Line_of_score::add_column (Paper_column*p)
{
  SCM cs = get_elt_property ("columns");
  Score_element * prev =  gh_pair_p (cs) ? unsmob_element (gh_car (cs)) : 0;
  int rank = prev ? dynamic_cast<Paper_column*> (prev)->rank_i () + 1 : 0; 

  p->set_rank (rank);
  set_elt_property ("columns",  gh_cons (p->self_scm_, cs));

  Axis_group_interface (this).add_element (p);
  typeset_element (p);
}

Link_array<Paper_column>
Line_of_score::column_l_arr ()const
{
  return Group_interface__extract_elements (this,
					    (Paper_column*) 0, "columns");

}

int
Line_of_score::compare (Line_of_score* const &p1,Line_of_score* const &p2)
{
  return p1->rank_i_ - p2->rank_i_;
}


void
fixup_refpoints (SCM s)
{
  for (; gh_pair_p (s); s = gh_cdr (s))
    {
      Score_element * se = unsmob_element (gh_car (s));
      if (se)
	{
	  se->fixup_refpoint ();
	  if (!dynamic_cast<Line_of_score*> (se) && !se->parent_l (Y_AXIS))
	    {
	      programming_error ("No parent!");
	    }
	}
    }
}


void
Line_of_score::pre_processing ()
{
  for (SCM s = get_elt_property ("all-elements"); gh_pair_p (s); s = gh_cdr (s))
    unsmob_element (gh_car (s))->do_breakable_col_processing ();
  
  fixup_refpoints (get_elt_property ("all-elements"));
  
  for (SCM s = get_elt_property ("all-elements"); gh_pair_p (s); s = gh_cdr (s))
    {
      Score_element* sc = unsmob_element (gh_car (s));
      sc->calculate_dependencies (PRECALCED, PRECALCING, &Score_element::before_line_breaking);
    }
  
  progress_indication ("\n" + _ ("Calculating column positions...") + " " );
  for (SCM s = get_elt_property ("all-elements"); gh_pair_p (s); s = gh_cdr (s))
    unsmob_element (gh_car (s))->do_space_processing ();
}

void
Line_of_score::post_processing ()
{
  fixup_refpoints (get_elt_property ("all-elements"));
  for (SCM s = get_elt_property ("all-elements");
       gh_pair_p (s); s = gh_cdr (s))
    {
      Score_element* sc = unsmob_element (gh_car (s));
      sc->calculate_dependencies (POSTCALCED, POSTCALCING, &Score_element::after_line_breaking);
    }

  Interval i(extent(Y_AXIS));
  if (i.empty_b())
    programming_error ("Huh?  Empty Line_of_score?");
  else
    translate_axis (- i[MAX], Y_AXIS);

  Real height = i.length ();
  if (height > 50 CM)
    {
      programming_error ("Improbable system height");
      height = 50 CM;
    }

  output_ = gh_cons (SCM_EOL, SCM_EOL);
  output_scheme (gh_list (ly_symbol2scm ("stop-line"), SCM_UNDEFINED));
  for (SCM s = get_elt_property ("all-elements"); gh_pair_p (s); s = gh_cdr (s))
    unsmob_element (gh_car (s))->output_processing ();
  output_scheme (gh_list (ly_symbol2scm ("start-line"),
			  gh_double2scm (height),
			  SCM_UNDEFINED));
}

void
Line_of_score::output_all () 
{
  calculate_dependencies (BREWED, BREWING, &Score_element::output_processing);
}

Link_array<Item> 
Line_of_score::broken_col_range (Item const*l, Item const*r) const
{
  Link_array<Item> ret;

  l = l->column_l ();
  r = r->column_l ();
  SCM s = get_elt_property ("columns");

  while (gh_car (s) != r->self_scm_)
    s = gh_cdr  (s);
    

  s = gh_cdr (s);
  
  while (gh_car (s) != l->self_scm_)
    {
      Paper_column *c
	= dynamic_cast<Paper_column*> (unsmob_element (gh_car (s)));
      if (c->breakable_b () && !c->line_l_)
	ret.push (c);

      s = gh_cdr  (s);
    }

  ret.reverse ();
  return ret;
}



