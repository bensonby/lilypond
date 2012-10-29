%% DO NOT EDIT this file manually; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% Make any changes in LSR itself, or in Documentation/snippets/new/ ,
%% and then run scripts/auxiliar/makelsr.py
%%
%% This file is in the public domain.
\version "2.17.6"

\header {
  lsrtags = "rhythms"

  texidoc = "
The addition of a final @code{mark} can result in the loss of a final
tuplet marking.  This can be overcome by setting @code{TupletBracket
#'full-length-to-extent} to @code{false}.

"
  doctitle = "Preventing final mark from removing final tuplet"
} % begin verbatim


\new Staff {
   \set tupletFullLength = ##t
   \time 1/8
   \times 2/3 { c'16 c'16 c'16 }
   \times 2/3 { c'16 c'16 c'16 }
   \times 2/3 { c'16 c'16 c'16 }
   \override Score.RehearsalMark.break-visibility = #'#(#t #t #t)
   \override Score.RehearsalMark.direction = #DOWN
   \override Score.RehearsalMark.self-alignment-X = #RIGHT
% due to issue 2362 the following line is commented
%   \mark "Composed Feb 2007 - Feb 2008"
% and a shorter mark is used.
   \mark "1234"
}

\new Staff {
  \set tupletFullLength = ##t

  \override TupletBracket.full-length-to-extent = ##f

  \time 1/8
  \times 2/3 { c'16 c'16 c'16 }
  \times 2/3 { c'16 c'16 c'16 }
  \times 2/3 { c'16 c'16 c'16 }
  \override Score.RehearsalMark.break-visibility = #'#(#t #t #t)
  \override Score.RehearsalMark.direction = #DOWN
  \override Score.RehearsalMark.self-alignment-X = #RIGHT
% due to issue 2362 the following line is commented
%   \mark "Composed Feb 2007 - Feb 2008"
% and a shorter mark is used.
   \mark "1234"
}
