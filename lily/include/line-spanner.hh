/*
  line-spanner.hh -- declare Line_spanner

  source file of the GNU LilyPond music typesetter

  (c) 2000--2007 Jan Nieuwenhuizen <janneke@gnu.org>
*/

#ifndef LINE_SPANNER_HH
#define LINE_SPANNER_HH

#include "lily-proto.hh"
#include "grob-interface.hh"

class Line_spanner
{
public:
  DECLARE_SCHEME_CALLBACK (print, (SCM));
  DECLARE_SCHEME_CALLBACK (after_line_breaking, (SCM));
  static Stencil line_stencil (Grob *me, Offset f, Offset t);
  DECLARE_GROB_INTERFACE();

private:
  static Offset get_broken_offset (Grob *me, Direction dir);
  static Offset broken_trend_offset (Grob *me, Direction dir);
};

#endif /* LINE_SPANNER_HH */
