/*
  rest.hh -- declare Rest

  source file of the GNU LilyPond music typesetter

  (c)  1997--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/


#ifndef REST_HH
#define REST_HH

#include "rhythmic-head.hh"

class  Rest : public Rhythmic_head
{
protected:
  virtual void after_line_breaking ();
  virtual Molecule do_brew_molecule () const;
};
#endif // REST_HH
