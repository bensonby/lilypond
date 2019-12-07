% DO NOT EDIT this file manually; it is automatically
% generated from Documentation/snippets/new
% Make any changes in Documentation/snippets/new/
% and then run scripts/auxiliar/makelsr.py
%
% This file is in the public domain.
%% Note: this file works from version 2.19.56
\version "2.19.56"

\header {
  lsrtags = "pitches, staff-notation"

  texidoc = "
Quotations take into account the transposition of both source and
target.  In this example, all instruments play sounding middle C; the
target is an instrument in F.  The target part may be transposed using
@code{\\transpose}.  In this case, all the pitches (including the
quoted ones) are transposed.

"
  doctitle = "Quoting another voice with transposition"
} % begin verbatim

\addQuote clarinet {
  \transposition bes
  \repeat unfold 8 { d'16 d' d'8 } % begin verbatim

}

\addQuote sax {
  \transposition es'
  \repeat unfold 16 { a8 }
}

quoteTest = {
  % french horn
  \transposition f
  g'4
  << \quoteDuring "clarinet" { \skip 4 } s4^"clar." >>
  << \quoteDuring "sax" { \skip 4 } s4^"sax." >>
  g'4
}

{
  \new Staff \with {
    instrumentName = \markup { \column { Horn "in F" } }
  }
  \quoteTest
  \transpose c' d' << \quoteTest s4_"up a tone" >>
}
