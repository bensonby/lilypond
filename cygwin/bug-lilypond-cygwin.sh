#!@SHELL@
# /usr/bin/bug-lilypond-cygwin.sh -- harvest relevant info for bugreport
#
# Ideas
#   * add some kpathsea tricks
#   * distribute for other platforms too
#   * failure/success tracking and indication (-> rewrite in python)

set -x

name="$(basename $0)"
# Running this in new shell may yield deceptive results
if [ "$name" = "bug-lilypond-cygwin" ]; then
    # HMM
    cat <<EOF
Please source this script, ie do:

    . /usr/bin/bug-lilypond-cygwin > bug.txt

EOF
fi

docdir=@prefix@/share/doc/lilypond-@TOPLEVEL_VERSION@-1
[ ! -d $docdir ] && docdir=@prefix@/doc/lilypond-@TOPLEVEL_VERSION@-1
[ ! -d $docdir ] && docdir=$(echo /usr/doc/lilypond-[0-9]*)

echo
echo Availability of executables
echo ===========================
type -p tex
type -p latex
type -p kpsewhich
type -p lilypond
type -p python
type -p ly2dvi

type -p tex.exe
type -p latex.exe
type -p kpsewhich.exe
type -p lilypond.exe
type -p python.exe

lilypond --version
python -V
ly2dvi --version


echo
echo Test runs
echo =========
mkdir -p /tmp/lily
cd /tmp/lily
rm -f example-1.* sample2e.*
ls -l
latex \\nonstopmode \\input sample2e
kpsewhich feta20.mf
kpsewhich feta20.pk
cp $docdir/input/example-1.ly .
cp $docdir/input/example-2.ly .
lilypond example-1.ly
latex \\nonstopmode \\input example-1.tex
dvips -o example-1.ps example-1.dvi
ls -l
ly2dvi --verbose example-2
ls -l

echo
echo Environment settings
echo ====================
# If python is ok and ly2dvi runs, this all is not really necessary.
echo HOME="<$HOME>"
echo SHELL="<$SHELL>"
echo LILYPONDPREFIX="<$LILYPONDPREFIX>"
echo TEXMF="<$TEXMF>"
echo MFINPUTS="<$MFINPUTS>"
echo TFMFONTS="<$TFMFONTS>"
echo TEXINPUTS="<$TEXINPUTS>"
# do we want to know all?
#set

echo
echo System information
echo ==================
uname -a
cygcheck -s

if false; then
    cat /var/log/setup.log
    # cat /var/log/setup.log.full
fi
