/*
    
    Copyright 2008 Imanol Celaya <ilcra1989@gmail.com>

This file is part of pyalpm.

    pyalpm is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    pyalpm is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with pyalpm.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <Python.h>

#include <alpm.h>
#include <alpm_list.h>

#include <string.h>

char VERSION[] = "0.1";

static PyObject *alpm_error = NULL;

static PyObject * initialize_alpm(PyObject *self)
{
  if(alpm_initialize() == -1)
  {
    PyErr_SetString(alpm_error, "failed to initialize alpm");
    return NULL;
  }
  else
  {
    return Py_None;
  }
}

static PyObject * release_alpm(PyObject *self)
{
  if(alpm_release() == -1)
  {
    PyErr_SetString(alpm_error, "failed to release alpm");
    return NULL;
  }
  else
  {
    return Py_None;
  }
}

static PyObject * option_get_logcb_alpm(PyObject *self)
{
  const char *str = NULL;
  if(alpm_option_get_logcb() == NULL)
  {
    PyErr_SetString(alpm_error, "failed getting logcb");
    return NULL;
  }
  else
  {
    str = alpm_option_get_logcb();
    
    return Py_BuildValue("s", str);
  }
}

void test_cb(pmloglevel_t level, char *fmt, va_list args)
{
  char msg[4][15];
  
  strcmp(msg[0], "Error: ");
  strcmp(msg[1], "Warning: ");
  strcmp(msg[2], "Debug: ");
  strcmp(msg[3], "Function: ");
  
  if(strlen(fmt))
  {
    switch(level)
    {
      case PM_LOG_ERROR: printf("%s", msg[0]); break;
      case PM_LOG_WARNING: printf("%s", msg[1]); break;
      case PM_LOG_DEBUG: printf("%s", msg[2]); break;
      case PM_LOG_FUNCTION: printf("%s", msg[3]); break;
      default: return;
    }
    vprintf(fmt, args);
  }
}

static PyObject * option_set_logcb_alpm(PyObject *self, PyObject *args)
{
  
  va_list cbargs;
  alpm_cb_log testcb;
  
  if(args == NULL)
  {
    PyErr_SetString(alpm_error, "invalid arguments");
    return NULL;
  }
  
  /*va_start(cbargs, args);
  
  va_end(cbargs);*/
  
  alpm_option_set_logcb(test_cb);
  
  return Py_None;
}

/*
The following functions take a string as argument(*_set_*)
while other (*_get_*) return a string
*/
static PyObject * option_get_root_alpm(PyObject *self)
{
  const char *str = NULL;
  
  if(alpm_option_get_root() == NULL)
  {
    PyErr_SetString(alpm_error, "failed getting root path");
    return NULL;
  }
  else
  {
    str = alpm_option_get_root();
    
    return Py_BuildValue("s", str);
  }
}

static PyObject * option_set_root_alpm(PyObject *self, PyObject *args)
{
  const char *path;

  if(!PyArg_ParseTuple(args, "s", &path))
  {
    PyErr_SetString(alpm_error, "error in the args");
    return NULL;
  }
  else
  {
    if(alpm_option_set_root(path) == -1)
    {
      PyErr_SetString(alpm_error, "failed setting root path");
      return NULL;
    }
    else
    {
      return Py_None;
    }
  }
}

static PyObject * option_set_dbpath_alpm(PyObject *self, PyObject *args)
{
  const char *path;
  if(!PyArg_ParseTuple(args, "s", &path))
  {
    PyErr_SetString(alpm_error, "error in the args");
    return NULL;
  }
  else
  {
    if(alpm_option_set_dbpath(path) == -1)
    {
      PyErr_SetString(alpm_error, "failed setting dbpath");
      return NULL;
    }
    else
    {
      return Py_None;
    }
  }
}

static PyObject * option_get_dbpath_alpm(PyObject *self)
{
  const char *str = NULL;
  
  if(alpm_option_get_dbpath() == NULL)
  {
    PyErr_SetString(alpm_error, "failed getting dbpath.");
    return NULL;
  }
  else
  {
    str = alpm_option_get_dbpath();
    
    return Py_BuildValue("s", str);
  }
}

static PyObject * option_set_logfile_alpm(PyObject *self, PyObject *args)
{
  const char *path;
  if(!PyArg_ParseTuple(args, "s", &path))
  {
    PyErr_SetString(alpm_error, "error in the args");
    return NULL;
  }
  else
  {
    if(alpm_option_set_logfile(path) == -1)
    {
      PyErr_SetString(alpm_error, "failed setting logfile");
      return NULL;
    }
    else
    {
      return Py_None;
    }
  }
}

static PyObject * option_get_logfile_alpm(PyObject *self)
{
  const char *str = NULL;
  
  if(alpm_option_get_logfile() == NULL)
  {
    PyErr_SetString(alpm_error, "failed getting logfile.");
    return NULL;
  }
  else
  {
    str = alpm_option_get_logfile();
    
    return Py_BuildValue("s", str);
  }
}

static PyObject * alpmversion_alpm(PyObject *self)
{
  const char *str;
  str = alpm_version();
  
  return Py_BuildValue("s", str);
}

static PyObject * version_alpm(PyObject *self)
{
  return Py_BuildValue("s", VERSION);
}

PyMethodDef methods[] = {
  {"initialize", initialize_alpm, METH_VARARGS, "initialize alpm."},
  {"release", release_alpm, METH_VARARGS, "release alpm."},
  {"getlogcb", option_get_logcb_alpm, METH_VARARGS, "call back function for logging."},
  {"setlogcb", option_set_logcb_alpm, METH_VARARGS, "sets logging config."},
  {"getroot", option_get_root_alpm, METH_VARARGS, "gets the root path."},
  {"setroot", option_set_root_alpm, METH_VARARGS, "sets the root path."},
  {"getdbpath", option_get_dbpath_alpm, METH_VARARGS, "gets the dbpath."},
  {"setdbpath", option_set_dbpath_alpm, METH_VARARGS, "sets the dbpath."},
  {"getlogfile", option_get_logfile_alpm, METH_VARARGS, "gets the logfile."},
  {"setlogfile", option_set_logfile_alpm, METH_VARARGS, "sets the logfile"},
  {"version", version_alpm, METH_VARARGS, "returns pyalpm version."},
  {"alpmversion", alpmversion_alpm, METH_VARARGS, "returns alpm version."},
  {NULL, NULL, 0, NULL}
};


PyMODINIT_FUNC initpyalpm()
{
  (void) Py_InitModule("pyalpm", methods);
  
  alpm_error = PyErr_NewException("alpm.error", NULL, NULL);
}