global = \notes {
	\key a \minor;
	\time 6/4;
%	\skip 1.*34;
%	\bar ".|";
}

melody = \notes\relative c''{
	r2 r r 
	r2 r r
	r4 a'8-- \< a--	a-- a-- c-- \!b-- a--\> gis f \!e 
	es8 \grace b c r4 r2 r
}

basloopje = \notes\relative c{
	d,8(	a' d f a d f d a f d	)a
}

accompany = \notes \relative c{
	\notes\relative c \basloopje
	\notes\relative c \basloopje
	\notes\relative c \basloopje
	\notes\relative c \basloopje
}

\score{
	\notes \context PianoStaff <
		\context Staff=up < 
			\global
			\context Voice=foo {
			\property Voice.verticalDirection = #1
			\property Voice.scriptVerticalDirection = #1
			\melody 
			}
		>
		\context Staff=down <
			\global
			\clef bass;
			\autochange Staff \accompany
		>
	>

	\paper {
		gourlay_maxmeasures = 4.;
		indent = 8.\mm;
		textheight = 295.\mm;

		% ugly is beautiful
		slur_beautiful = 5.0;

		\translator{ 
			\PianoStaffContext
			defaultBarType = #"" 
		}
		\translator{ 
			\StaffContext
			% don't auto-generate bars: not a good idea: -> no breakpoints
			% barAuto = "0";
			% urg defaultBarType = #""
			defaultBarType = #"" 
			\remove "Time_signature_engraver";

			slurVerticalDirection = #1
			verticalDirection = -1
			autoBeamSettings \push (end * * * *)  = #(make-moment 1 2)
		}
	}
	\midi {
		\tempo 4 = 54;
	}
}

