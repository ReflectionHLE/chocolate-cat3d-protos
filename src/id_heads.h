/* Catacomb 3-D Source Code
 * Copyright (C) 1993-2014 Flat Rock Software
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

// ID_GLOB.H


//#include <ALLOC.H>
#include <ctype.h>
//#include <DOS.H>
#include <errno.h>
#include <fcntl.h>
//#include <IO.H>
//#include <MEM.H>
//#include <PROCESS.H>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <SYS\STAT.H>

#define __ID_GLOB__

//
//	ID Engine
//	Types.h - Generic types, #defines, etc.
//	v1.0d1
//

#ifndef	__TYPES__
#define	__TYPES__

#include <stdbool.h>
#include <stdint.h>

// Command line arguments
extern int _argc;
extern char **_argv;

typedef	bool id0_boolean_t;
typedef int8_t id0_char_t;
typedef int8_t id0_signed_char_t;
typedef uint8_t id0_unsigned_char_t;
//typedef int16_t id0_short_t; // only found with an unused variable (c3_main.c)
typedef int16_t id0_int_t;
typedef uint16_t id0_unsigned_t;
typedef int32_t id0_long_t;
typedef uint32_t id0_unsigned_long_t;

typedef uint8_t id0_byte_t;
typedef uint16_t id0_word_t;
typedef uint32_t id0_longword_t;
// Possibly unused in any of the 3D Catacomb games (as released by FlatRockSoft)
//typedef uint8_t * id0_ptr_t;		Ptr;

// TODO (CHOCO CAT3D):
// Any better alternative? (Used only in c3_draw.c:BuildTables())
typedef float id0_float_t;
typedef double id0_double_t;

// Used in place of MAXINT in c3_draw.c (which defines ID0_MININT separately)
#define ID0_MAXINT 32767

typedef	struct
		{
			id0_int_t	x,y;
		} Point;
typedef	struct
		{
			Point	ul,lr;
		} Rect;

#define	id0_nil_t	((void *)0)

// TODO (CHOCO CAT3D): These should really be removed, but just in case...
#define id0_far
#define id0_huge
#define id0_seg

#endif

//--------------------------------------------------------------------------

#define	EXTENSION	"C3D"

extern	id0_char_t id0_far introscn;

#include "gfxe_c3d.h"
#include "audioc3d.h"

//--------------------------------------------------------------------------

#define CAT3D

#define	TEXTGR	0
#define	CGAGR	1
#define	EGAGR	2
#define	VGAGR	3

// FIXME (Chocolate Cat3D): Hack because we begin implementing CGA first
#define GRMODE	CGAGR
//#define GRMODE	EGAGR

#if GRMODE == EGAGR
#define GREXT	"EGA"
#endif
#if GRMODE == CGAGR
#define GREXT	"CGA"
#endif

//#define PROFILE

#include "id_mm.h"
#include "id_ca.h"
#include "id_vw.h"
#include "id_in.h"
#include "id_sd.h"
#include "id_us.h"


void	Quit (id0_char_t *error);		// defined in user program

//
// replacing refresh manager with custom routines
//

#define	PORTTILESWIDE		21      // all drawing takes place inside a
#define	PORTTILESHIGH		14		// non displayed port of this size

#define UPDATEWIDE			(PORTTILESWIDE+1)
#define UPDATEHIGH			PORTTILESHIGH

#define	MAXTICS				6
#define DEMOTICS			3

#define	UPDATETERMINATE	0x0301

extern	id0_unsigned_t	mapwidth,mapheight,tics;
extern	id0_boolean_t		compatability;

extern	id0_byte_t		*updateptr;
extern	id0_unsigned_t	uwidthtable[UPDATEHIGH];
extern	id0_unsigned_t	blockstarts[UPDATEWIDE*UPDATEHIGH];
