/*
 * The internal definitions
 *
 * Copyright (c) 2011, Joachim Metz <jbmetz@users.sourceforge.net>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBEXE_INTERNAL_DEFINITIONS_H )
#define _LIBEXE_INTERNAL_DEFINITIONS_H

#include <common.h>
#include <byte_stream.h>

#define LIBEXE_ENDIAN_BIG					_BYTE_STREAM_ENDIAN_BIG
#define LIBEXE_ENDIAN_LITTLE					_BYTE_STREAM_ENDIAN_LITTLE

/* Define HAVE_LOCAL_LIBEXE for local use of libexe
 */
#if !defined( HAVE_LOCAL_LIBEXE )
#include <libexe/definitions.h>

/* The definitions in <libexe/definitions.h> are copied here
 * for local use of libexe
 */
#else
#define LIBEXE_VERSION						20111021

/* The version string
 */
#define LIBEXE_VERSION_STRING					"20111021"

/* The access flags definitions
 * bit 1        set to 1 for read access
 * bit 2        set to 1 for write access
 * bit 3-8      not used
 */
enum LIBEXE_ACCESS_FLAGS
{
	LIBEXE_ACCESS_FLAG_READ					= 0x01,
/* Reserved: not supported yet */
	LIBEXE_ACCESS_FLAG_WRITE				= 0x02
};

/* The file access macros
 */
#define LIBEXE_OPEN_READ					( LIBEXE_ACCESS_FLAG_READ )
/* Reserved: not supported yet */
#define LIBEXE_OPEN_WRITE					( LIBEXE_ACCESS_FLAG_WRITE )
/* Reserved: not supported yet */
#define LIBEXE_OPEN_READ_WRITE					( LIBEXE_ACCESS_FLAG_READ | LIBEXE_ACCESS_FLAG_WRITE )

/* The target architecture type definitions
 */
enum LIBEXE_TARGET_ARCHITECTURE_TYPES
{
	LIBEXE_TARGET_ARCHITECTURE_TYPE_UNKNOWN			= 0x0000,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_I386			= 0x014c,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_R3000			= 0x0162,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_R4000			= 0x0166,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_R10000			= 0x0168,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_ALPHA			= 0x0184,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_SH3			= 0x01a2,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_SH4			= 0x01a6,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_ARM			= 0x01c0,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_THUMB			= 0x01c2,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_POWERPC			= 0x01f0,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_IA64			= 0x0200,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_MIPS16			= 0x0266,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_M68K			= 0x0268,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_ALPHA64			= 0x0284,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_MIPSFPU			= 0x0366,
	LIBEXE_TARGET_ARCHITECTURE_TYPE_MIPSFPU16		= 0x0466
};

/* The file characteristic flags definitions
 */
enum LIBEXE_FILE_CHARACTERISTIC_FLAGS
{
	LIBEXE_FILE_CHARACTERISTIC_FLAG_RELOCS_STRIPPED		= 0x0001,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_EXECUTABLE_IMAGE	= 0x0002,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_LINE_NUMS_STRIPPED	= 0x0004,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_LOCAL_SYMS_STRIPPED	= 0x0008,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_AGGRESSIVE_WS_TRIM	= 0x0010,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_LARGE_ADDRESS_AWARE	= 0x0020,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_16BIT_MACHINE		= 0x0040,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_BYTES_REVERSED_LO	= 0x0080,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_32BIT_MACHINE		= 0x0100,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_DEBUG_STRIPPED		= 0x0200,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_REMOVABLE_RUN_FROM_SWAP	= 0x0400,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_SYSTEM			= 0x1000,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_DLL			= 0x2000,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_UP_SYSTEM_ONLY		= 0x4000,
	LIBEXE_FILE_CHARACTERISTIC_FLAG_BYTES_REVERSED_HI	= 0x8000
};

#endif

/* The COFF optional header signatures
 */
enum LIBEXE_COFF_OPTIONAL_HEADER_SIGNATURES
{
	LIBEXE_COFF_OPTIONAL_HEADER_SIGNATURE_PE32		= 0x010b,

	LIBEXE_COFF_OPTIONAL_HEADER_SIGNATURE_PE32_PLUS		= 0x020b
};

#endif
