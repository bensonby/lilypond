% table16.ly
%
% spacing info for LilyPond. Do not edit this if you're not a guru.
% It has a lot of hard-wired stringconstants
%


table_sixteen= 
\symboltables {
   \texid 	"\input lilyponddefs \musixsixteendefs"
   % index TeXstring, 	xmin xmax ymin ymax


	%{ 
	"back" "\backorfront"		0.0\pt	6.0\pt	0.0\pt	3.0\pt
	"-front" "\backorfront"		0.0\pt	6.0\pt	0.0\pt	3.0\pt
	"heel" "\heel"			0.0\pt	6.0\pt	-1.0\pt	5.0\pt
	"toe" "\\toe"			0.0\pt	6.0\pt	-1.0\pt	5.0\pt
	"bheel" "\bheel"			0.0\pt	6.0\pt	-1.0\pt	5.0\pt
	"btoe" "\btoe"			0.0\pt	6.0\pt	-1.0\pt	5.0\pt
	"fheel" "\fheel"			0.0\pt	6.0\pt	-1.0\pt	5.0\pt
	"ftoe" "\ftoe"			0.0\pt	6.0\pt	-1.0\pt	5.0\pt
	"-back" "\backorfront"		0.0\pt	6.0\pt	0.0\pt	3.0\pt
	"front" "\backorfront"		0.0\pt	6.0\pt	0.0\pt	3.0\pt
	"turn"  "\\turn"			-2.0\pt	7.0\pt	0.0\pt	4.0\pt
	%}

     "style" = \table {
		"roman"	"\settext{%}"	0.0\pt	7.50\pt	0.0\pt	8.0\pt
		"italic"	"\setitalic{%}"	0.0\pt	0.0\pt	0.0\pt	8.0\pt
		"dynamic"	"\setdynamic{%}"	0.0\pt	0.0\pt	0.0\pt	8.0\pt
     }
     "dynamics" = \table {

	"mf" "\dynmf"
	"fff" "\dynfff"
	"ff" "\dynff"
	"f" "\dynf"
	"mp" "\dynmp"
	"p" "\dynp"
	"pp" "\dynpp"
	"ppp" "\dynppp"
	"fp" "\dynfp"
	"sf" "\dynsf"
	"sfz" "\dynsfz"

	}
     "align" = \table {
		"-1"	"\leftalign{%}"
		"0"	"\centeralign{%}"
		"1"	"\rightalign{%}"
 	}

     "clefs" = \table {
	"violin"	"\violinclef"		0.0\pt	12.8\pt	-10.0\pt	18.0\pt
	"bass"	"\bassclef" 		0.0\pt	12.8\pt	0.0\pt	16.0\pt
	"alto"	"\altoclef"		0.0\pt	12.8\pt	0.0\pt	16.0\pt
	"tenor"	"\altoclef"		0.0\pt	12.8\pt	0.0\pt	16.0\pt
	"violin_change"	"\cviolinclef" 	0.0\pt	11.2\pt	-12.0\pt	12.0\pt
	"bass_change"	"\cbassclef"	0.0\pt	11.2\pt	0.0\pt	16.0\pt
	"alto_change"	"\caltoclef" 	0.0\pt	11.2\pt	0.0\pt	16.0\pt
	"tenor_change"	"\caltoclef" 	0.0\pt	11.2\pt	0.0\pt	16.0\pt
     }

     "slur" = \table {
	"whole"	"\slurchar%{%}"
	"half"	"\hslurchar%{%}"
     }

     "streepjes" = \table {
	"toplines"	"\\topledgerlines{%}{%}"	-1.0\pt	7.0\pt	0.0\pt	0.0\pt
	"botlines"	"\\botledgerlines{%}{%}"	-1.0\pt	7.0\pt	0.0\pt	0.0\pt
     }

     "bars" = \table {
	"empty"	"\emptybar"
	""	""			0.0\pt	0.0\pt	0.0\pt	16.0\pt
	"|"	"\maatstreep{%}"	0.0\pt	0.64\pt 0.0\pt	16.0\pt
	"||"	"\doublebar{%}"		0.0\pt	4.0\pt	0.0\pt	16.0\pt
	"|."	"\finishbar{%}"		-4.0\pt	0.0\pt	0.0\pt	16.0\pt
	".|"	"\startbar{%}"		0.0\pt	4.0\pt	0.0\pt	16.0\pt
	":|"	"\repeatbar"		-8.0\pt	0.0\pt	0.0\pt	16.0\pt
	"|:"	"\startrepeat"		0.0\pt	8.0\pt	0.0\pt 16.0\pt
	":|:"	"\repeatbarstartrepeat"	0.0\pt	16.0\pt	0.0\pt	16.0\pt

     }

     "meters" = \table {
	"C"	"\fourfourmeter"		0.0\pt	10.0\pt	-5.0\pt	5.0\pt
	"C2"	"\allabreve"		0.0\pt	10.0\pt	-5.0\pt	5.0\pt
     }

     % dims ignored for this table
     "param" = \table {
	"brace"	"\pianobrace{%}"	0.0\pt	0.0\pt	0.0\pt	0.0\pt
	"meter"	"\generalmeter{%}{%}"	0.0\pt	10.0\pt	-8.0\pt	8.0\pt
	"linestaf"	"\linestafsym{%}{%}"
	"stem"	"\stem{%}{%}"
	"fill"	"\hbox{}"
	% ugh. 8pt
	"crescendosym"	"\crescendosym{%}"	0.0\pt	0.0\pt	-3.0\pt	3.0\pt
	"decrescendosym"	"\decrescendosym{%}"	0.0\pt	0.0\pt	-3.0\pt	3.0\pt
     }


     "beamslopes" = \table {
	"slope"		"\beamslope{%}{%}"  2.0\pt 64.0\pt 0.0\pt 0.0\pt
	"horizontal"	"\rulesym{%}{%}"	
     }
     \include "font-en-tja16.ly"
}

