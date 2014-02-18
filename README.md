# dvbcut

This is a clone from http://sourceforge.net/projects/dvbcut/

## About

dvbcut is a Qt application that allows you to select certain parts of
an MPEG transport stream (as received via Digital Video Broadcasting,
DVB) and save these parts into a single MPEG output file. It follows a
"keyhole surgery" approach where the input video and audio data is
mostly kept unchanged, and only very few frames at the beginning
and/or end of the selected range are re-encoded in order to obtain a
valid MPEG file.

## Purpose

This is an attempt to port dvbcut to a recent (2.1.3) ffmpeg version.
The repository also serves as a place for some patches, I've done in
the past.

I cloned the repository with 

    git svn clone --stdlayout http://svn.code.sf.net/p/dvbcut/code/ dvbcut.git

and build with 

    autoconf
    ./configure --with-qt3-include=/usr/include/qt3/ --with-ffmpeg=/usr/local/

Adjust your paths accordingly. More options are shown with 

    ./configure --help
