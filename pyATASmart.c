#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>

#include <atasmart.h>

#include <Python.h>

 static PyObject *pyATASmart_powerOn(PyObject *self, PyObject *args)
{

int ret;
 uint64_t ms;
 SkDisk *d;
 
 if (!PyArg_ParseTuple(args, "s", &device))
    {
        return NULL;
    }
 if ((ret = sk_disk_open(device, &d)) < 0) {
                       
                        return Py_BuildValue("s", "Failed to open disk");
                }
                      

                              if ((ret = sk_disk_smart_read_data(d)) < 0) {
                                return Py_BuildValue("s", "Failed to read SMART data");
                                
                        }

                        if ((ret = sk_disk_smart_get_power_on(d, &ms)) < 0) {
                              return Py_BuildValue("s", "Failed to get power on time");
                                
                        }
			return Py_BuildValue("K", (unsigned long long) ms);
}

static PyMethodDef pyATASmart_methods[] = {
        { "powerOn", (PyCFunction)pyATASmart_powerOn, METH_VARARGS, NULL },
        { NULL, NULL, 0, NULL }
};
 
PyMODINIT_FUNC initpyATASmart()
{
        Py_InitModule3("pyATASmart", pyATASmart_methods, "Python bindings for the libatasmart library");
}

