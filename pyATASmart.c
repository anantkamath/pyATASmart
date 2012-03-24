#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>

#include <atasmart.h>

#include <Python.h>


static PyObject *pyATASmart_diskOpen(PyObject *self, PyObject *args)//Incompatible with python memory manager
{

int ret;
 SkDisk *d;
 const char *device;
 if (!PyArg_ParseTuple(args, "s",&device))
    {
        return NULL;
    }
 if ((ret = sk_disk_open(device, &d)) < 0) {
                       PyErr_SetString(PyExc_OSError, "Failed to open disk");
                        
		       return NULL;
                }
        		return Py_BuildValue("O", d);
}



/*static PyObject *pyATASmart_diskFree(PyObject *self, PyObject *args) //Reimplemented original C function to be compatible with python memory manager
{


 SkDisk *d;

 if (!PyArg_ParseTuple(args, "O",&d))
    {
        return NULL;
    }
 //sk_disk_free(d); Reimplimentation:
 
         if (d->fd >= 0)
               close(d->fd);
        // PyMem_Free(d->name);
        //PyMem_Free(d->blob);
        //PyMem_Free(d);

 
 
}
*/




//Get the power-on time		
 static PyObject *pyATASmart_getPowerOn(PyObject *self, PyObject *args)
{

int ret;
 uint64_t ms;
 SkDisk *d;
 
 if (!PyArg_ParseTuple(args, "O", &d))
    {
        return NULL;
    }
                      

                              if ((ret = sk_disk_smart_read_data(d)) < 0) {
				PyErr_SetString(PyExc_OSError, "Failed to read SMART data");      
                                return NULL;
                                
                        }

                        if ((ret = sk_disk_smart_get_power_on(d, &ms)) < 0) {
                              
                              PyErr_SetString(PyExc_OSError, "Failed to get power on time");      
                                return NULL;  
                        }
			return Py_BuildValue("K", (unsigned long long) ms);
}

static PyObject *pyATASmart_getTemperature(PyObject *self, PyObject *args)
{

int ret;

 SkDisk *d;
uint64_t mkelvin;

                        

                	
 if (!PyArg_ParseTuple(args, "O", &d))
    {
        return NULL;
    }
                      

                              if ((ret = sk_disk_smart_read_data(d)) < 0) {
				PyErr_SetString(PyExc_OSError, "Failed to read SMART data");      
                                return NULL;
                                
                        }

                        if ((ret = sk_disk_smart_get_temperature(d, &mkelvin)) < 0) {
                              
                              PyErr_SetString(PyExc_OSError, "Failed to get disk temperature");      
                                return NULL;  
                        }
			return Py_BuildValue("K", (unsigned long long) mkelvin);
}



static PyMethodDef pyATASmart_methods[] = {
	{ "diskOpen", (PyCFunction)pyATASmart_diskOpen, METH_VARARGS, "Open a disk" },
        { "getPowerOn", (PyCFunction)pyATASmart_getPowerOn, METH_VARARGS, "Get the disk power-on time"},
        { "getTemperature", (PyCFunction)pyATASmart_getTemperature, METH_VARARGS, "Get the disk temperature" },
        { "diskFree", (PyCFunction)pyATASmart_diskFree, METH_VARARGS, NULL },
        { NULL, NULL, 0, NULL }
};
 
PyMODINIT_FUNC initpyATASmart()
{
        Py_InitModule3("pyATASmart", pyATASmart_methods, "Python bindings for the libatasmart library");
}

