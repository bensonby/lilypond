\version "2.1.23"

\header {

    texidoc = "

Container by splitting the grouping (Axis_group_engraver) and creation
functionality into separate contexts, you can override interesting
things.

Notation like this is used in modern scores. Note that LilyPond is not
especially prepared for it: the clefs and time-signatures don't do
what you would expect.

    "

      }



\score  {
 \notes \relative c'' <<
 	\new StaffContainer {

	    %% need << >>, otherwise we descend to the voice inside SA  
	    << \new Staff { c4 c4 } >>
	    \skip 4  % s4 would create staff.
	    
	    << \new Staff { b4 b4 } >> 
	}
 	\new StaffContainer {
	    \skip 4
	    << \context Staff { e d f \bar ":|" } >>
	    \skip 4
	}
 >>

\paper {
	\translator {
		\ScoreContext
		\accepts StaffContainer
		\denies Staff
	}
	\translator {
		\type Engraver_group_engraver
		\consists Clef_engraver
		\consists Time_signature_engraver
		\consists Separating_line_group_engraver
		\consistsend "Axis_group_engraver"
		\accepts "Staff"
		
		\name StaffContainer
	}
	\translator {
		\StaffContext
		\remove Axis_group_engraver
		\remove Separating_line_group_engraver
		\remove Clef_engraver
		\remove Time_signature_engraver
	}
	raggedright=##t
}
}


