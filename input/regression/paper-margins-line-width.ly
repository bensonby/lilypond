\version "2.13.4"

\header {
  texidoc = "If only line-width is given, systems are vertically centered."
}

someNotes = \relative c' { \repeat unfold 40 { c4 d e f }}

\paper {
  line-width = 100 \mm
}

\score { \someNotes }
