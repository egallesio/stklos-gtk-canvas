# Makefile for stklos-gtk-base example 
#
#          Author: Erick Gallesio [eg@essi.fr]
#   Creation date:  8-Apr-2008 18:28 (eg)
#Last file update: 19-Aug-2009 09:22 (eg)

CC     = gcc
CFLAGS = -Wall			 	\
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED \
	-DGTK_DISABLE_DEPRECATED


all: canvas-in-C canvas

canvas: canvas.stk
	stklos-compile -o canvas canvas.stk


canvas-in-C: canvas-in-C.c
	$(CC) canvas-in-C.c -o canvas-in-C $(CFLAGS) \
              `pkg-config goocanvas --cflags --libs`

clean:
	/bin/rm -f *~ canvas canvas-in-C

