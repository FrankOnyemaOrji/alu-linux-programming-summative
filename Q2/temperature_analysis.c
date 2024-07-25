#include <Python.h>
#include <stdio.h>

// Function to initialize the Python interpreter and call the Python script
void analyze_temperatures(const char *filename) {
    Py_Initialize();

    // Import necessary Python modules
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;

    pName = PyUnicode_DecodeFSDefault("temperature_analysis"); // Python script name
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "analyze_temperatures");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_Pack(1, PyUnicode_FromString(filename));
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != NULL) {
                double mean = PyFloat_AsDouble(PyTuple_GetItem(pValue, 0));
                double mode = PyFloat_AsDouble(PyTuple_GetItem(pValue, 1));
                double stddev = PyFloat_AsDouble(PyTuple_GetItem(pValue, 2));
                
                printf("Mean Temperature: %.2f K\n", mean);
                printf("Mode Temperature: %.2f K\n", mode);
                printf("Standard Deviation: %.2f K\n", stddev);
                
                Py_DECREF(pValue);
            } else {
                PyErr_Print();
                fprintf(stderr, "Call to Python function failed\n");
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"analyze_temperatures\"\n");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"temperature_analysis\"\n");
    }
    
    Py_Finalize();
}

int main() {
    const char *filename = "temperature.csv";
    analyze_temperatures(filename);
    return 0;
}
