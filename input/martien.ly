%
% Viola Quartet
% Martien Lohman (194x-????) 
%
% quite alive at the time of writing; 
% copyright by ml
%
% 
% The purpose of this file is to demonstrate features of LilyPond;
% respect the copyright.
%
% \barnumbering5
% \barnumberstyle\boxed

globalmusic= \melodic{
		\meter {2/4}
%		\key fis
		\skip {56*2}
%		\key bes es as
		\skip {8*2}
		\meter {6/8}
		\skip{ 48*8}
		\meter {2/4}
		\skip {16*2}
%		\key fis
}

include "mlalt.ly"
include "mlvio1.ly"
include "mlvio2.ly"
include "mlcello.ly"

\score{
	\staff{ globalmusic alto }
	\staff{ globalmusic violinI }
	\staff{ globalmusic violinII }
	\staff{ globalmusic cello }
	\paper{
		\unitspace 24\mm
		\width 195\mm
		\output "martien.out"
	}
	\midi{ 
		\tempo 4:80
	}
}
