\version "1.0.20";

\score{
	\notes \relative c {
	      c d c f c g c b, c g, c f, c c'' c
% run with find-quarts should suggest:
%	      c d c f c g' c, b c g c f, c' c'' c,,
	}
}

