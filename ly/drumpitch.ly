% GM drum pitches.
% I use different accidentals to distinguish drums at the same GM pitch.
% Always accidental 0 (white keys) or 1 (black keys) to get the "correct" gm name.
% i.e. fis, for closed highat ; ges, for highat.

% 2001/03/25 Rune Zedeler <rune@zedeler.dk>


#(define drum-pitch-names `(
	(acousticbassdrum bda	,(make-pitch -3 6 0 ))
	(bassdrum	  bd	,(make-pitch -2 0 0 ))
	(hisidestick	  ssh	,(make-pitch -3 6 2))
	(sidestick	  ss	,(make-pitch -2 0 1))
	(losidestick	  ssl	,(make-pitch -2 1 -1))
	(acousticsnare	  sna	,(make-pitch -2 1 0))
	(snare		  sn	,(make-pitch -2 2 -2))
	(handclap	  hc	,(make-pitch -2 1 1))
	(electricsnare	  sne	,(make-pitch -2 2 0))
	(lowfloortom	  tomfl	,(make-pitch -2 3 0))
	(closedhihat	  hhc	,(make-pitch -2 3 1))
	(hihat		  hh	,(make-pitch -2 4 -1))
	(highfloortom	  tomfh	,(make-pitch -2 4 0))
	(pedalhihat	  hhp	,(make-pitch -2 4 1))
	(lowtom		  toml	,(make-pitch -2 5 0))
	(openhihat	  hho	,(make-pitch -2 5 1))
	(halfopenhihat	  hhho	,(make-pitch -2 5 1))
	(lowmidtom	  tomml	,(make-pitch -2 6 0))
	(himidtom	  tommh	,(make-pitch -1 0 0))
	(crashcymbala	  cymca	,(make-pitch -1 0 1))
	(crashcymbal	  cymc	,(make-pitch -1 1 -1))
	(hightom	  tomh	,(make-pitch -1 1 0))
	(ridecymbala	  cymra	,(make-pitch -1 1 1))
	(ridecymbal	  cymr	,(make-pitch -1 2 -1))
	(chinesecymbal	  cymch	,(make-pitch -1 2 0))
	(ridebell	  rb	,(make-pitch -1 3 0))
	(tambourine	  tamb	,(make-pitch -1 3 1))
	(splashcymbal	  cyms	,(make-pitch -1 4 0))
	(cowbell	  cb	,(make-pitch -1 4 1))
	(crashcymbalb	  cymcb	,(make-pitch -1 5 0))
	(vibraslap	  vibs	,(make-pitch -1 5 1))
	(ridecymbalb	  cymrb	,(make-pitch -1 6 0))
	(hibongo	  boh	,(make-pitch 0 0 0))
	(lobongo	  bol	,(make-pitch 0 0 1))
	(mutehiconga	  cghm	,(make-pitch 0 1 0))
	(openhiconga	  cgho	,(make-pitch 0 1 1))
	(hiconga	  cgh	,(make-pitch 0 2 -1))
	(loconga	  cgl	,(make-pitch 0 2 0))
	(hitimbale	  timh	,(make-pitch 0 3 0))
	(lotimbale	  timl	,(make-pitch 0 3 1))
	(hiagogo	  agh	,(make-pitch 0 4 0))
	(loagogo	  agl	,(make-pitch 0 4 1))
	(cabasa		  cab	,(make-pitch 0 5 0))
	(maracas	  mar	,(make-pitch 0 5 1))
	(shortwhistle	  whs	,(make-pitch 0 6 0))
	(longwhistle	  whl	,(make-pitch 1 0 0))
	(shortguiro	  guis	,(make-pitch 1 0 1))
	(longguiro	  guil	,(make-pitch 1 1 0))
	(guiro		  gui	,(make-pitch 1 0 2))
	(claves		  cl	,(make-pitch 1 1 1))
	(hiwoodblock	  wbh	,(make-pitch 1 2 0))
	(lowoodblock	  wbl	,(make-pitch 1 3 0))
	(mutecuica	  cuim	,(make-pitch 1 3 1))
	(opencuica	  cuio	,(make-pitch 1 4 0))
	(mutetriangle	  trim	,(make-pitch 1 4 1))
	(triangle	  tri	,(make-pitch 1 4 2))
	(opentriangle	  trio	,(make-pitch 1 5 0))
	; "transposing" pitches:
	(oneup		  ua	,(make-pitch 0 1 0))
	(twoup		  ub	,(make-pitch 0 2 0))
	(threeup	  uc	,(make-pitch 0 3 0))
	(fourup		  ud	,(make-pitch 0 4 0))
	(fiveup		  ue	,(make-pitch 0 5 0))
	(onedown	  da	,(make-pitch -1 6 0))
	(twodown	  db	,(make-pitch -1 5 0))
	(threedown	  dc	,(make-pitch -1 4 0))
	(fourdown	  dd	,(make-pitch -1 3 0))
	(fivedown	  de	,(make-pitch -1 2 0))
))

#(define drums `(
	(acousticbassdrum default 	,#f	  ,(make-pitch -1 4 0))
	(bassdrum	  default 	,#f	  ,(make-pitch -1 4 0))
	(sidestick	  cross		,#f	  ,(make-pitch 0 1 0))
	(acousticsnare	  default 	,#f	  ,(make-pitch 0 1 0))
	(snare		  default 	,#f	  ,(make-pitch 0 1 0))
	(handclap	  triangle	,#f	  ,(make-pitch 0 1 0))
	(electricsnare	  default 	,#f	  ,(make-pitch 0 1 0))
	(lowfloortom	  default 	,#f	  ,(make-pitch -1 3 0))
	(closedhihat	  cross		"stopped" ,(make-pitch 0 3 0))
	(hihat		  cross		,#f	  ,(make-pitch 0 3 0))
	(highfloortom	  default 	,#f	  ,(make-pitch -1 5 0))
	(pedalhihat	  cross		,#f	  ,(make-pitch -1 2 0))
	(lowtom		  default 	,#f	  ,(make-pitch 0 0 0))
	(openhihat	  cross		"open"	  ,(make-pitch 0 3 0))
	(halfopenhihat	  xcircle	,#f	  ,(make-pitch 0 3 0))
	(lowmidtom	  default 	,#f	  ,(make-pitch 0 1 0))
	(himidtom	  default 	,#f	  ,(make-pitch 0 2 0))
	(crashcymbala	  xcircle 	,#f	  ,(make-pitch 0 5 0))
	(crashcymbal	  xcircle 	,#f	  ,(make-pitch 0 5 0))
	(hightom	  default 	,#f	  ,(make-pitch 0 4 0))
	(ridecymbala	  cross		,#f	  ,(make-pitch 0 5 0))
	(ridecymbal	  cross		,#f	  ,(make-pitch 0 5 0))
	(chinesecymbal	  mensural 	,#f	  ,(make-pitch 0 5 0))
	(ridebell	  default	,#f	  ,(make-pitch 0 5 0))
	(splashcymbal	  diamond 	,#f	  ,(make-pitch 0 5 0))
	(cowbell	  triangle	,#f	  ,(make-pitch 0 5 0))
	(crashcymbalb	  cross		,#f	  ,(make-pitch 0 5 0))
	(vibraslap	  diamond 	,#f	  ,(make-pitch 0 4 0))
	(ridecymbalb	  cross		,#f	  ,(make-pitch 0 5 0))
 ))

#(define timbales `(
	(losidestick	  cross		,#f	  ,(make-pitch -1 6 0))
	(lotimbale	  default	,#f	  ,(make-pitch -1 6 0))
	(cowbell	  triangle	,#f	  ,(make-pitch 0 0 0))
	(hisidestick	  cross		,#f	  ,(make-pitch 0 1 0))
	(hitimbale	  default	,#f	  ,(make-pitch 0 1 0))
 ))

#(define congas `(
	(losidestick	  cross		,#f	  ,(make-pitch -1 6 0))
	(loconga	  default	,#f	  ,(make-pitch -1 6 0))
	(hisidestick	  cross		,#f	  ,(make-pitch 0 1 0))
	(hiconga	  default	,#f	  ,(make-pitch 0 1 0))
	(openhiconga	  default	open"	  ,(make-pitch 0 1 0))
	(mutehiconga	  default	stopped"  ,(make-pitch 0 1 0))
 ))

#(define bongos `(
	(lobongo	  default	,#f	  ,(make-pitch -1 6 0))
	(hibongo	  default	,#f	  ,(make-pitch 0 1 0))
 ))

#(define guiro `(
	(shortguiro	  default	"staccato",(make-pitch 0 0 0))
	(longguiro	  default	"tenuto"  ,(make-pitch 0 0 0))
	(guiro		  default	,#f	  ,(make-pitch 0 0 0))
 ))

#(define triangle `(
	(opentriangle	  cross		"open"	  ,(make-pitch 0 0 0))
	(mutetriangle	  cross		"stopped" ,(make-pitch 0 0 0))
	(triangle	  cross		,#f	  ,(make-pitch 0 0 0))
 ))



\pitchnames
#(append (map (lambda (x) (cons (car x) (caddr x))) drum-pitch-names)
	 (map (lambda (x) (cons (cadr x) (caddr x))) drum-pitch-names)
 )


\version "1.3.142";
