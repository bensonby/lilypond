% DO NOT EDIT this file manually; it is automatically
% generated from Documentation/snippets/new
% Make any changes in Documentation/snippets/new/
% and then run scripts/auxiliar/makelsr.py
%
% This file is in the public domain.
%% Note: this file works from version 2.14.0
\version "2.14.0"

\header {
%%%    Translation of GIT committish: 6977ddc9a3b63ea810eaecb864269c7d847ccf98

  texidoces = "

El fragmento de código que aparece a continuación produce una lista de
todas las llaves y disposiciones de llave posibles para los diagramas
de posiciones de instrumentos de viento madera, tal y como están
definidos en @file{scm/define-woodwind-diagrams.scm}.  La lista se
presenta en la consola y en el archivo de registro de salida, pero no
en la salida de música.

"

  doctitlees = "Listas de llaves para los diagramas de viento madera"

%%%    Translation of GIT committish: ab9e3136d78bfaf15cc6d77ed1975d252c3fe506

  texidocde="
Dieses Schnipsel erzeugt eine Liste aller möglichen Löcher und Locheinstellungen
für Holzbläserdiagramme, wie sie in der Datei
@file{scm/define-woodwind-diagrams.scm} definiert sind.  Die Liste wird auf
der Kommandozeile und in der Log-Datei angezeigt, nicht in den Noten.
"
  doctitlede = "Liste der Löcher für Holzbläserdiagramme"


%% Translation of GIT committish: 496c48f1f2e4d345ae3637b2c38ec748a55cda1d
  texidocfr = "
Le code suivant vous permettra d'obtenir une liste de toutes les
possibilités en matière de doigtés pour bois, tels qu'ils sont définis
dans le fichier @file{scm/define-woodwind-diagrams.scm}.  Cette liste
sera produite en console et dans le fichier de journalisation, mais pas
sous forme de musique.
"
  doctitlefr = "Liste des différents diagrammes de doigtés pour bois"

  lsrtags = "winds"

  texidoc="
The snippet below produces a list of all possible keys and key
settings for woodwind diagrams as defined in
@file{scm/define-woodwind-diagrams.scm}.  The list will be displayed
in the log file, but not in the music.  If output to the console
is wanted, omit the @code{(current-error-port)} from the commands.
"
  doctitle = "Woodwind diagrams key lists"
} % begin verbatim


#(print-keys-verbose 'piccolo (current-error-port))
#(print-keys-verbose 'flute (current-error-port))
#(print-keys-verbose 'flute-b-extension (current-error-port))
#(print-keys-verbose 'tin-whistle (current-error-port))
#(print-keys-verbose 'oboe (current-error-port))
#(print-keys-verbose 'clarinet (current-error-port))
#(print-keys-verbose 'bass-clarinet (current-error-port))
#(print-keys-verbose 'low-bass-clarinet (current-error-port))
#(print-keys-verbose 'saxophone (current-error-port))
#(print-keys-verbose 'soprano-saxophone (current-error-port))
#(print-keys-verbose 'alto-saxophone (current-error-port))
#(print-keys-verbose 'tenor-saxophone (current-error-port))
#(print-keys-verbose 'baritone-saxophone (current-error-port))
#(print-keys-verbose 'bassoon (current-error-port))
#(print-keys-verbose 'contrabassoon (current-error-port))
