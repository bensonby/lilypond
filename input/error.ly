\version "0.0.57";

\include "this-is-hopefully-a-nonexisting-file"



mwa = \melodic{
	\meter 3/4;
	[ a8 a8 a8 a8 a8 ]	% 
	[ a8 ]	% 
%       segfault
	< { [ bes^"1"~  a bes-. g-. ] a4-.^"4" } { [ e ] } { [ c ] } > |
	a ) b ] c 	% warning
	&   		% ok; error
	a b ) ] 	% ok; error
%        a.........	% fatal error -- assert
	a b c
	|.|		% 
	abc		% ok; print error, no \output
	\bla 		%  STRING, reduced to lyric_elt.
	a [ b 		% warning, still \output
        < a( b >	% warning, still \output
	a b ,c
	a b c-*
	a b c&
	< a-. b-. >
	
}

bla = \lyric{
	These Gates will open just like windows. % ok; warning
}


% Setting up music ...lilypond: ../flower/include/cursor.inl:98: class Cursor<void *> Cursor<void *>::operator ++(int): Assertion 'pointer_' failed.
%IOT trap/Abort
% als geen music in staff

\include "this-is-hopefully-a-nonexisting-file"
\score{
	\staff{ bla }
	\staff{ mwa }
}
