/*
  molecule.cc -- implement Molecule

  source file of the GNU LilyPond music typesetter

  (c)  1997--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#include <math.h>
#include <libc-extension.hh>

#include "font-metric.hh"
#include "dimensions.hh"
#include "interval.hh"
#include "string.hh"
#include "molecule.hh"
#include "debug.hh"
#include "killing-cons.tcc"

Interval
Molecule::extent(Axis a) const
{
  return dim_[a];
}

Molecule::Molecule (Box b, SCM func)
{
  expr_ = func;
  dim_ = b;
}

Molecule::Molecule()
{
  expr_ = SCM_EOL;
  set_empty (true);
}

void
Molecule::translate (Offset o)
{
  Axis a = X_AXIS;
  while (a < NO_AXES)
    {
      if (abs(o[a]) > 30 CM
	  || isinf (o[a]) || isnan (o[a]))
	{
	  programming_error ("Improbable offset for translation: setting to zero");
	  o[a] =  0.0;
	}
      incr (a);
    }

  expr_ = gh_list (ly_symbol2scm ("translate-molecule"),
		   ly_offset2scm (o),
		   expr_, SCM_UNDEFINED);
  if (!empty_b ())
    dim_.translate (o);
}
  

void
Molecule::translate_axis (Real x,Axis a)
{
  Offset o(0,0);
  o[a] = x;
  translate (o);
}  



void
Molecule::add_molecule (Molecule const &m)
{
  expr_ = gh_list (ly_symbol2scm ("combine-molecule"),
		   m.expr_,
		   expr_, SCM_UNDEFINED);
  dim_.unite (m.dim_);
}

void
Molecule::set_empty (bool e)
{
  if (e)
    {
      dim_[X_AXIS].set_empty ();
      dim_[Y_AXIS].set_empty ();
    }
  else
    {
      dim_[X_AXIS] = Interval(0,0);
      dim_[Y_AXIS] = Interval (0,0);
    }
}


void
Molecule::align_to (Axis a, Direction d)
{
  Interval i (extent (a));
  Real r =  (d == CENTER) ? i.center () : i[d];
  translate_axis (-r, a);
}

void
Molecule::add_at_edge (Axis a, Direction d, Molecule const &m, Real padding)
{
  Real my_extent= empty_b () ? 0.0 : dim_[a][d];
  Interval i (m.extent (a));
  if (i.empty_b ())
    programming_error ("Molecule::add_at_edge: adding empty molecule.");
  
  Real his_extent = i[-d];
  Real offset = my_extent -  his_extent;
  Molecule toadd (m);
  toadd.translate_axis (offset + d * padding, a);
  add_molecule (toadd);
}

bool
Molecule::empty_b () const
{
  return expr_ == SCM_EOL;
}

SCM
fontify_atom(Font_metric * met, SCM f)
{
  return  gh_list (ly_symbol2scm ("fontify"),
		   ly_quote_scm (met->description ()), f, SCM_UNDEFINED);
}

SCM
Molecule::get_expr () const
{
  return expr_;
}

Molecule
create_molecule (SCM scm_mol)
{
  if (!gh_pair_p (scm_mol))
    return Molecule ();

  SCM exp = gh_car (scm_mol);
  scm_mol = gh_cdr (scm_mol);
  Box b ;
  if (gh_pair_p (scm_mol))
    {
      Interval i1 = ly_scm2interval (gh_car (scm_mol));
      Interval i2 = ly_scm2interval (gh_cdr (scm_mol));  
      b = Box (i1,i2);
    }
  return Molecule (b, exp);
}

SCM
Molecule::create_scheme () const
{
  return gh_cons (expr_,
		  gh_cons (ly_interval2scm (dim_[X_AXIS]),
			   ly_interval2scm (dim_[Y_AXIS])));
}
