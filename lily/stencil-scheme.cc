/*
  stencil-scheme.cc -- implement Stencil scheme accessors

  source file of the GNU LilyPond music typesetter

  (c) 1997--2005 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#include <math.h>

#include "font-metric.hh"
#include "libc-extension.hh"
#include "lookup.hh"
#include "stencil.hh"


/*
  TODO: naming add/combine.
*/
/*
  UGH. Junk all mutators.
*/
LY_DEFINE (ly_stencil_set_extent_x, "ly:stencil-set-extent!",
	   3, 0, 0, (SCM stil, SCM axis, SCM np),
	   "Set the extent of @var{stil} "
	   "(@var{extent} must be a pair of numbers) "
	   "in @var{axis} direction (0 or 1 for x- and y-axis respectively).")
{
  Stencil *s = unsmob_stencil (stil);
  SCM_ASSERT_TYPE (s, stil, SCM_ARG1, __FUNCTION__, "stencil");
  SCM_ASSERT_TYPE (is_axis (axis), axis, SCM_ARG2, __FUNCTION__, "axis");
  SCM_ASSERT_TYPE (is_number_pair (np), np, SCM_ARG3, __FUNCTION__,
		   "number pair");

  Interval iv = ly_scm2interval (np);
  s->dim_[Axis (scm_to_int (axis))] = iv;

  return SCM_UNSPECIFIED;
}

LY_DEFINE (ly_translate_stencil_axis, "ly:stencil-translate-axis",
	   3, 0, 0, (SCM stil, SCM amount, SCM axis),
	   "Return a copy of @var{stil} but translated by @var{amount} in @var{axis} direction.")
{
  Stencil *s = unsmob_stencil (stil);
  SCM_ASSERT_TYPE (s, stil, SCM_ARG1, __FUNCTION__, "stencil");
  SCM_ASSERT_TYPE (scm_is_number (amount), amount, SCM_ARG2, __FUNCTION__, "number");

  Real real_amount = scm_to_double (amount);
#if 0
  SCM_ASSERT_TYPE (!isinf (real_amount) && !isnan (real_amount),
		   amount, SCM_ARG2, __FUNCTION__, "finite number");
#endif

  SCM_ASSERT_TYPE (is_axis (axis), axis, SCM_ARG3, __FUNCTION__, "axis");

  SCM new_s = s->smobbed_copy ();
  Stencil *q = unsmob_stencil (new_s);
  q->translate_axis (real_amount, Axis (scm_to_int (axis)));
  return new_s;

}

LY_DEFINE (ly_translate_stencil, "ly:stencil-translate",
	   2, 0, 0, (SCM stil, SCM offset),
	   "Return a @var{stil}, "
	   "but translated by @var{offset} (a pair of numbers).")
{
  Stencil *s = unsmob_stencil (stil);
  SCM_ASSERT_TYPE (s, stil, SCM_ARG1, __FUNCTION__, "stencil");
  SCM_ASSERT_TYPE (is_number_pair (offset), offset, SCM_ARG2, __FUNCTION__, "number pair");
  Offset o = ly_scm2offset (offset);

  SCM new_s = s->smobbed_copy ();
  Stencil *q = unsmob_stencil (new_s);
  q->translate (o);
  return new_s;
}

LY_DEFINE (ly_stencil_expr, "ly:stencil-expr",
	   1, 0, 0, (SCM stil),
	   "Return the expression of @var{stil}.")
{
  Stencil *s = unsmob_stencil (stil);
  SCM_ASSERT_TYPE (s, stil, SCM_ARG1, __FUNCTION__, "stencil");
  return s->expr ();
}

LY_DEFINE (ly_stencil_get_extent, "ly:stencil-extent",
	   2, 0, 0, (SCM stil, SCM axis),
	   "Return a pair of numbers signifying the extent of @var{stil} in "
	   "@var{axis} direction (0 or 1 for x and y axis respectively).")
{
  Stencil *s = unsmob_stencil (stil);
  SCM_ASSERT_TYPE (s, stil, SCM_ARG1, __FUNCTION__, "stencil");
  SCM_ASSERT_TYPE (is_axis (axis), axis, SCM_ARG2, __FUNCTION__, "axis");

  return ly_interval2scm (s->extent (Axis (scm_to_int (axis))));
}

LY_DEFINE (ly_stencil_empty_p, "ly:stencil-empty?",
	   1, 0, 0, (SCM stil),
	   "Return whether @var{stil} is empty ")
{
  Stencil *s = unsmob_stencil (stil);
  SCM_ASSERT_TYPE (s, stil, SCM_ARG1, __FUNCTION__, "stencil");
  return scm_from_bool (s->is_empty ());
}

LY_DEFINE (ly_stencil_origin, "ly:stencil-origin",
	   2, 0, 0, (SCM stil, SCM axis),
	   "Return a pair of numbers signifying the origin @var{stil} in "
	   "@var{axis} direction (0 or 1 for x and y axis respectively).")
{
  Stencil *s = unsmob_stencil (stil);
  SCM_ASSERT_TYPE (s, stil, SCM_ARG1, __FUNCTION__, "stencil");
  SCM_ASSERT_TYPE (is_axis (axis), axis, SCM_ARG2, __FUNCTION__, "axis");

  return scm_from_double (s->origin ()[Axis (scm_to_int (axis))]);
}

LY_DEFINE (ly_stencil_moved_to_edge, "ly:stencil-moved-to-edge",
	   4, 2, 0, (SCM first, SCM axis, SCM direction, SCM second,
		     SCM padding, SCM minimum),
	   "Similar to @code{ly:stencil-combine-edge}, but returns "
	   "@var{second} positioned to be next to @var{first}. ")
{
  /*
    C&P from combine-at-edge.
  */
  Stencil *s1 = unsmob_stencil (first);
  Stencil *s2 = unsmob_stencil (second);
  Stencil first_stencil;

  SCM_ASSERT_TYPE (is_axis (axis), axis, SCM_ARG3, __FUNCTION__, "axis");
  SCM_ASSERT_TYPE (is_direction (direction), direction, SCM_ARG4, __FUNCTION__, "dir");

  Real p = 0.0;
  if (padding != SCM_UNDEFINED)
    {
      SCM_ASSERT_TYPE (scm_is_number (padding), padding, SCM_ARG5, __FUNCTION__, "number");
      p = scm_to_double (padding);
    }
  Real m = 0.0;
  if (minimum != SCM_UNDEFINED)
    {
      SCM_ASSERT_TYPE (scm_is_number (minimum), minimum, SCM_ARG6, __FUNCTION__, "number");
      m = scm_to_double (minimum);
    }

  if (s1)
    first_stencil = *s1;

  if (s2)
    return first_stencil.moved_to_edge (Axis (scm_to_int (axis)),
					Direction (scm_to_int (direction)),
					*s2, p, m).smobbed_copy ();
  else
    return Stencil ().smobbed_copy ();
}

LY_DEFINE (ly_stencil_combine_at_edge, "ly:stencil-combine-at-edge",
	   4, 2, 0, (SCM first, SCM axis, SCM direction,
		     SCM second,
		     SCM padding,
		     SCM minimum),
	   "Construct a stencil by putting @var{second} next to @var{first}. "
	   "@var{axis} can be 0 (x-axis) or 1 (y-axis), "
	   "@var{direction} can be -1 (left or down) or 1 (right or up). "
	   "The stencils are juxtaposed with  @var{padding} as extra space. "
	   "If this puts the reference points closer than @var{minimum}, "
	   "they are moved by the latter amount."
	   "@var{first} and @var{second} may also be '() or #f.")
{
  Stencil *s1 = unsmob_stencil (first);
  Stencil *s2 = unsmob_stencil (second);
  Stencil result;

  SCM_ASSERT_TYPE (s1 || first == SCM_BOOL_F || first == SCM_EOL,
		   first, SCM_ARG1, __FUNCTION__, "Stencil, #f or ()");
  SCM_ASSERT_TYPE (s2 || second == SCM_BOOL_F || second == SCM_EOL,
		   second, SCM_ARG4, __FUNCTION__, "Stencil, #f or ()");
  SCM_ASSERT_TYPE (is_axis (axis), axis, SCM_ARG2, __FUNCTION__, "axis");
  SCM_ASSERT_TYPE (is_direction (direction), direction, SCM_ARG3, __FUNCTION__, "dir");

  Real p = 0.0;
  if (padding != SCM_UNDEFINED)
    {
      SCM_ASSERT_TYPE (scm_is_number (padding), padding, SCM_ARG5, __FUNCTION__, "number");
      p = scm_to_double (padding);
    }
  Real m = 0.0;
  if (minimum != SCM_UNDEFINED)
    {
      SCM_ASSERT_TYPE (scm_is_number (minimum), minimum, SCM_ARG6, __FUNCTION__, "number");
      m = scm_to_double (minimum);
    }

  if (s1)
    result = *s1;

  if (s2)
    result.add_at_edge (Axis (scm_to_int (axis)),
			Direction (scm_to_int (direction)), *s2, p, m);

  return result.smobbed_copy ();
}

LY_DEFINE (ly_stencil_add, "ly:stencil-add",
	   0, 0, 1, (SCM args),
	   "Combine stencils. Takes any number of arguments.")
{
#define FUNC_NAME __FUNCTION__
  SCM_VALIDATE_REST_ARGUMENT (args);

  Stencil result;

  while (!SCM_NULLP (args))
    {
      Stencil *s = unsmob_stencil (scm_car (args));
      if (!s)
	SCM_ASSERT_TYPE (s, scm_car (args), SCM_ARGn, __FUNCTION__, "Stencil");

      result.add_stencil (*s);
      args = scm_cdr (args);
    }

  return result.smobbed_copy ();
}

LY_DEFINE (ly_make_stencil, "ly:make-stencil",
	   3, 0, 0, (SCM expr, SCM xext, SCM yext),
	   " \n"
	   "Stencils are a device independent output expressions."
	   "They carry two pieces of information: \n\n"
	   "1: a specification of how to print this object. "
	   "This specification is processed by the output backends, "
	   " for example @file{scm/output-tex.scm}.\n\n"
	   "2: the vertical and horizontal extents of the object.\n\n")
{
  SCM_ASSERT_TYPE (is_number_pair (xext), xext, SCM_ARG2, __FUNCTION__, "number pair");
  SCM_ASSERT_TYPE (is_number_pair (yext), yext, SCM_ARG3, __FUNCTION__, "number pair");

  Box b (ly_scm2interval (xext), ly_scm2interval (yext));
  Stencil s (b, expr);
  return s.smobbed_copy ();
}

LY_DEFINE (ly_stencil_align_to_x, "ly:stencil-align-to!",
	   3, 0, 0, (SCM stil, SCM axis, SCM dir),
	   "Align @var{stil} using its own extents. "
	   "@var{dir} is a number -1, 1 are left and right respectively. "
	   "Other values are interpolated (so 0 means the center. ")
{
  SCM_ASSERT_TYPE (unsmob_stencil (stil), stil, SCM_ARG1, __FUNCTION__, "stencil");
  SCM_ASSERT_TYPE (is_axis (axis), axis, SCM_ARG2, __FUNCTION__, "axis");
  SCM_ASSERT_TYPE (scm_is_number (dir), dir, SCM_ARG3, __FUNCTION__, "number");

  unsmob_stencil (stil)->align_to ((Axis)scm_to_int (axis),
				   scm_to_double (dir));
  return stil;
}

LY_DEFINE (ly_stencil_fonts, "ly:stencil-fonts",
	   1, 0, 0, (SCM s),
	   " Analyse @var{s}, and return a list of fonts used in @var{s}.")
{
  Stencil *stil = unsmob_stencil (s);
  SCM_ASSERT_TYPE (stil, s, SCM_ARG1, __FUNCTION__, "Stencil");
  return find_expression_fonts (stil->expr ());
}

struct Stencil_interpret_arguments
{
  SCM func;
  SCM arg1;
};

void stencil_interpret_in_scm (void *p, SCM expr)
{
  Stencil_interpret_arguments *ap = (Stencil_interpret_arguments *) p;
  scm_call_2 (ap->func, ap->arg1, expr);
}

LY_DEFINE (ly_interpret_stencil_expression, "ly:interpret-stencil-expression",
	   4, 0, 0, (SCM expr, SCM func, SCM arg1, SCM offset),
	   "Parse EXPR, feed bits to FUNC with first arg ARG1")
{
  SCM_ASSERT_TYPE (ly_c_procedure_p (func), func, SCM_ARG1, __FUNCTION__,
		   "procedure");

  Stencil_interpret_arguments a;
  a.func = func;
  a.arg1 = arg1;
  Offset o = ly_scm2offset (offset);

  interpret_stencil_expression (expr, stencil_interpret_in_scm, (void *) &a, o);

  return SCM_UNSPECIFIED;
}

LY_DEFINE (ly_bracket, "ly:bracket",
	   4, 0, 0,
	   (SCM a, SCM iv, SCM t, SCM p),
	   "Make a bracket in direction @var{a}. The extent of the bracket is "
	   "given by @var{iv}. The wings protude by an amount of @var{p}, which "
	   "may be negative. The thickness is given by @var{t}.")
{
  SCM_ASSERT_TYPE (is_axis (a), a, SCM_ARG1, __FUNCTION__, "axis");
  SCM_ASSERT_TYPE (is_number_pair (iv), iv, SCM_ARG2, __FUNCTION__, "number pair");
  SCM_ASSERT_TYPE (scm_is_number (t), a, SCM_ARG3, __FUNCTION__, "number");
  SCM_ASSERT_TYPE (scm_is_number (p), a, SCM_ARG4, __FUNCTION__, "number");

  return Lookup::bracket ((Axis)scm_to_int (a), ly_scm2interval (iv),
			  scm_to_double (t),
			  scm_to_double (p),
			  0.95 * scm_to_double (t)).smobbed_copy ();
}

LY_DEFINE (ly_filled_box, "ly:round-filled-box",
	   3, 0, 0,
	   (SCM xext, SCM yext, SCM blot),
	   "Make a @code{Stencil} "
	   "that prints a black box of dimensions @var{xext}, "
	   "@var{yext} and roundness @var{blot}.")
{
  SCM_ASSERT_TYPE (is_number_pair (xext), xext, SCM_ARG1, __FUNCTION__, "number pair");
  SCM_ASSERT_TYPE (is_number_pair (yext), yext, SCM_ARG2, __FUNCTION__, "number pair");
  SCM_ASSERT_TYPE (scm_is_number (blot), blot, SCM_ARG3, __FUNCTION__, "number");

  return Lookup::round_filled_box (Box (ly_scm2interval (xext), ly_scm2interval (yext)),
				   scm_to_double (blot)).smobbed_copy ();
}

