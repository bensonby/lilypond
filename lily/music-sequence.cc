/*   
  music-sequence.cc --  implement Music_sequence
  
  source file of the GNU LilyPond music typesetter
  
  (c) 1998--2004 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#include "music-list.hh"
#include "warn.hh"
#include "pitch.hh"
#include "input.hh"

Music_sequence::Music_sequence (SCM x)
  : Music (x)
{
}

SCM
Music_sequence::music_list () const
{
  return get_property ("elements");
}

void
transpose_music_list (SCM lst, Pitch rq)
{
  for (SCM s = lst; scm_is_pair (s);  s = scm_cdr (s))
    unsmob_music (scm_car (s))->transpose (rq);    
}

Moment
Music_sequence::cumulative_length (SCM l) 
{
  Moment cumulative;
  Moment last_len; 

  for (SCM s = l; scm_is_pair (s);  s = scm_cdr (s))
    {
      Moment l = unsmob_music (scm_car (s))->get_length ();
      if (last_len.grace_part_ && l.main_part_)
	{
	  last_len.grace_part_ = Rational (0);
	}
      cumulative += last_len;
      last_len = l;
    }

  last_len.grace_part_ = Rational (0);
  cumulative += last_len;

  return  cumulative;
}

Moment
Music_sequence::maximum_length (SCM l)
{
  Moment dur = 0;
  for (SCM s = l; scm_is_pair (s);  s = scm_cdr (s))
    {
      Music * m = unsmob_music (scm_car (s));
      Moment l = m->get_length ();
      dur = dur >? l;
    }

  return dur;
}

MAKE_SCHEME_CALLBACK(Music_sequence,maximum_length_callback,1);
SCM
Music_sequence::maximum_length_callback (SCM m)
{
  Music* me = unsmob_music (m);
  return maximum_length (me->get_property ("elements")).smobbed_copy();
}

MAKE_SCHEME_CALLBACK(Music_sequence,cumulative_length_callback,1);
SCM
Music_sequence::cumulative_length_callback (SCM m)
{
  Music* me = unsmob_music (m);
  return cumulative_length (me->get_property ("elements")).smobbed_copy();
}

Pitch
music_list_to_relative (SCM l,Pitch p, bool ret_first)
{
  Pitch first = p;
  int count = 0;

  Pitch last = p;
  for (SCM s = l; scm_is_pair (s);  s = scm_cdr (s))
    {
      if (Music *m = unsmob_music (scm_car (s)))
	{
	  last = m->to_relative_octave (last);
	  if (!count ++)
	    first = last;
	}
    }

  return  (ret_first)?  first : last;
}


void
compress_music_list (SCM l, Moment m)
{
  for (SCM s = l; scm_is_pair (s);  s = scm_cdr (s))
    unsmob_music (scm_car (s))->compress (m);
}

ADD_MUSIC (Music_sequence);

Moment
Music_sequence::minimum_start (SCM l)
{
  Moment m;
  
  for (SCM s = l; scm_is_pair (s);  s = scm_cdr (s))
    {
      m = m <? unsmob_music (scm_car (s))->start_mom ();
    }
  return m;
}

Moment
Music_sequence::first_start (SCM l) 
{
  Moment m;
  
  for (SCM s = l; scm_is_pair (s);  s = scm_cdr (s))
    {
      Music * mus = unsmob_music (scm_car (s));
      Moment l = mus->get_length ();
      Moment s = mus->start_mom ();
      if (l.to_bool () || s.to_bool ())
	return s;
    }
  return m;
}


