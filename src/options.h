/**
 * options.h
 *
 *  Copyright 2008 Imanol Celaya <ilcra1989@gmail.com>
 *
 *  This file is part of pyalpm.
 *
 *  pyalpm is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  pyalpm is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with pyalpm.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _PY_ALPM_OPTIONS_METHODS_H
#define _PY_ALPM_OPTIONS_METHODS_H

#include <Python.h>

/** boolean options */

PyObject* option_get_usesyslog_alpm(PyObject *self, void* closure);
int option_set_usesyslog_alpm(PyObject *self, PyObject *value, void* closure);

PyObject* option_get_usedelta_alpm(PyObject *self, void* closure);
int option_set_usedelta_alpm(PyObject *self, PyObject *value, void* closure);

PyObject* option_get_checkspace_alpm(PyObject *self, void* closure);
int option_set_checkspace_alpm(PyObject *self, PyObject *value, void* closure);

/** list options */
PyObject* option_get_cachedirs_alpm(PyObject *self, void* closure);
PyObject* option_get_noupgrades_alpm(PyObject *self, void* closure);
PyObject* option_get_noextracts_alpm(PyObject *self, void* closure);
PyObject* option_get_ignorepkgs_alpm(PyObject *self, void* closure);
PyObject* option_get_ignoregrps_alpm(PyObject *self, void* closure);

int option_set_cachedirs_alpm(PyObject *self, PyObject *value, void *closure);
int option_set_noupgrades_alpm(PyObject *self, PyObject *value, void *closure);
int option_set_noextracts_alpm(PyObject *self, PyObject *value, void *closure);
int option_set_ignorepkgs_alpm(PyObject *self, PyObject *value, void *closure);
int option_set_ignoregrps_alpm(PyObject *self, PyObject *value, void *closure);

PyObject * option_add_noupgrade_alpm(PyObject *self, PyObject *args);
PyObject * option_remove_noupgrade_alpm(PyObject *self, PyObject *args);

PyObject * option_add_cachedir_alpm(PyObject *self, PyObject *args);
PyObject * option_remove_cachedir_alpm(PyObject *self, PyObject *args);

PyObject * option_add_noextract_alpm(PyObject *self, PyObject *args);
PyObject * option_remove_noextract_alpm(PyObject *self, PyObject *args);

PyObject * option_add_ignorepkg_alpm(PyObject *self, PyObject *args);
PyObject * option_remove_ignorepkg_alpm(PyObject *self, PyObject *args);

PyObject * option_add_ignoregrp_alpm(PyObject *self, PyObject *args);
PyObject * option_remove_ignoregrp_alpm(PyObject *self, PyObject *args);

/** Callback options */
int pyalpm_option_set_logcb(PyObject *self, PyObject *value, void *closure);
int pyalpm_option_set_dlcb(PyObject *self, PyObject *value, void *closure);
int pyalpm_option_set_totaldlcb(PyObject *self, PyObject *value, void *closure);
int pyalpm_option_set_fetchcb(PyObject *self, PyObject *value, void *closure);
PyObject* pyalpm_option_get_logcb(PyObject *self, void *closure);
PyObject* pyalpm_option_get_dlcb(PyObject *self, void *closure);
PyObject* pyalpm_option_get_totaldlcb(PyObject *self, void *closure);
PyObject* pyalpm_option_get_fetchcb(PyObject *self, void *closure);

#endif

/* vim: set ts=2 sw=2 et: */
