%% Toplevel initialisation file. 

%% switch on debugging.
#(if (and #t (defined? 'set-debug-cell-accesses!))
  (set-debug-cell-accesses! 5000))

\version "2.10.0"

\include "declarations-init.ly"


#(ly:set-option 'old-relative #f)
#(define toplevel-scores '())
#(define output-count 0) 
#(define $defaultheader #f)
#(define version-seen #f)
#(define expect-error #f) 
  
#(use-modules (scm clip-region))
\maininput
%% there is a problem at the end of the input file

%%
%% Above and below comments compensate for the parser's look-ahead.
%%

#(if (and (ly:get-option 'old-relative)
      (defined? 'input-file-name)
      (not (ly:get-option 'old-relative-used)))
  (old-relative-not-used-message input-file-name))%% there is a problem at the end of the input file

#(if (and (not version-seen)
      (defined? 'input-file-name))
  (version-not-seen-message input-file-name))

#(if (pair? toplevel-scores)
  ((if (defined? 'default-toplevel-book-handler)
    default-toplevel-book-handler
    toplevel-book-handler)
   parser
   (apply ly:make-book $defaultpaper $defaultheader toplevel-scores)))


#(if expect-error
  (ly:parser-clear-error parser))
