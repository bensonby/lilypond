\version "2.18.0"

\header {
  lsrtags = "text, tweaks-and-overrides"

  texidoc = "
The default font families for text can be overridden with
@code{make-pango-font-tree}.

"
  doctitle = "Changing the default text font family"
}

\paper {
  % change for other default global staff size.
  myStaffSize = #20
  %{
     run
         lilypond -dshow-available-fonts blabla
     to show all fonts available in the process log.
  %}

  #(define fonts
    (make-pango-font-tree "Times New Roman"
                          "Nimbus Sans,Nimbus Sans L"
                          "Luxi Mono"
;;                        "Helvetica"
;;                        "Courier"
     (/ myStaffSize 20)))
}

\relative c'' {
  c4^\markup {
    roman: foo \bold bla \italic bar \italic \bold baz
  }
  c'4_\markup {
    \override #'(font-family . sans)
    {
      sans: foo \bold bla \italic bar \italic \bold baz
    }
  }
  c'2^\markup {
    \override #'(font-family . typewriter)
    {
      mono: foo \bold bla \italic bar \italic \bold baz
    }
  }
}
