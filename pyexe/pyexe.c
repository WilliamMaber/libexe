/*
 * Python bindings module for libexe (pyexe)
 *
 * Copyright (c) 2011-2014, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyexe.h"
#include "pyexe_error.h"
#include "pyexe_file.h"
#include "pyexe_file_object_io_handle.h"
#include "pyexe_libcerror.h"
#include "pyexe_libcstring.h"
#include "pyexe_libexe.h"
#include "pyexe_python.h"
#include "pyexe_section.h"
#include "pyexe_sections.h"
#include "pyexe_unused.h"

#if !defined( LIBEXE_HAVE_BFIO )
LIBEXE_EXTERN \
int libexe_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libexe_error_t **error );
#endif

/* The pyexe module methods
 */
PyMethodDef pyexe_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pyexe_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	{ "check_file_signature",
	  (PyCFunction) pyexe_check_file_signature,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_file_signature(filename) -> Boolean\n"
	  "\n"
	  "Checks if a file has an executable (EXE) signature." },

	{ "check_file_signature_file_object",
	  (PyCFunction) pyexe_check_file_signature_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_file_signature_file_object(file_object) -> Boolean\n"
	  "\n"
	  "Checks if a file has an executable (EXE) signature using a file-like object." },

	{ "open",
	  (PyCFunction) pyexe_file_new_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> Object\n"
	  "\n"
	  "Opens a file." },

	{ "open_file_object",
	  (PyCFunction) pyexe_file_new_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> Object\n"
	  "\n"
	  "Opens a file using a file-like object." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pyexe/libexe version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_get_version(
           PyObject *self PYEXE_ATTRIBUTE_UNUSED,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYEXE_UNREFERENCED_PARAMETER( self )
	PYEXE_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libexe_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = libcstring_narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         errors ) );
}

/* Checks if the file has an executable (EXE) signature
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_check_file_signature(
           PyObject *self PYEXE_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	static char *function       = "pyexe_check_file_signature";
	static char *keyword_list[] = { "filename", NULL };
	const char *filename        = NULL;
	int result                  = 0;

	PYEXE_UNREFERENCED_PARAMETER( self )

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|s",
	     keyword_list,
	     &filename ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_check_file_signature(
	          filename,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyexe_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to check file signature.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( result != 0 )
	{
		return( Py_True );
	}
	return( Py_False );
}

/* Checks if the file has an executable (EXE) signature using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_check_file_signature_file_object(
           PyObject *self PYEXE_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error         = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	PyObject *file_object            = NULL;
	static char *function            = "pyexe_check_file_signature_file_object";
	static char *keyword_list[]      = { "file_object", NULL };
	int result                       = 0;

	PYEXE_UNREFERENCED_PARAMETER( self )

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|O",
	     keyword_list,
	     &file_object ) == 0 )
	{
		return( NULL );
	}
	if( pyexe_file_object_initialize(
	     &file_io_handle,
	     file_object,
	     &error ) != 1 )
	{
		pyexe_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_check_file_signature_file_io_handle(
	          file_io_handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyexe_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to check file signature.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &file_io_handle,
	     &error ) != 1 )
	{
		pyexe_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( result != 0 )
	{
		return( Py_True );
	}
	return( Py_False );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( NULL );
}

/* Declarations for DLL import/export
 */
#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif

/* Initializes the pyexe module
 */
PyMODINIT_FUNC initpyexe(
                void )
{
	PyObject *module                   = NULL;
	PyTypeObject *file_type_object     = NULL;
	PyTypeObject *section_type_object  = NULL;
	PyTypeObject *sections_type_object = NULL;
	PyGILState_STATE gil_state         = 0;

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
	module = Py_InitModule3(
	          "pyexe",
	          pyexe_module_methods,
	          "Python libexe module (pyexe)." );

	PyEval_InitThreads();

	gil_state = PyGILState_Ensure();

	/* Setup the file type object
	 */
	pyexe_file_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyexe_file_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyexe_file_type_object );

	file_type_object = &pyexe_file_type_object;

	PyModule_AddObject(
	 module,
	"file",
	(PyObject *) file_type_object );

	/* Setup the sections type object
	 */
	pyexe_sections_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyexe_sections_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyexe_sections_type_object );

	sections_type_object = &pyexe_sections_type_object;

	PyModule_AddObject(
	 module,
	 "_sections",
	 (PyObject *) sections_type_object );

	/* Setup the section type object
	 */
	pyexe_section_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyexe_section_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyexe_section_type_object );

	section_type_object = &pyexe_section_type_object;

	PyModule_AddObject(
	 module,
	 "section",
	 (PyObject *) section_type_object );

on_error:
	PyGILState_Release(
	 gil_state );
}

