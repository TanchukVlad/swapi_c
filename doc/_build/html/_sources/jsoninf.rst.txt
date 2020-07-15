JsonInf -- reads information about some object in JSON file
===========================================================

JsonInf can reads information from JSON file and show the string from object in 
this file. Uses libjson-c-dev -- JSON-C implements a reference counting object 
model that allows you to easily construct JSON objects in C, output them as 
JSON formatted strings and parse JSON formatted strings back into the C 
representation of JSON objects.  

.. c:autodoc:: inc/jsoninf.h src/jsoninf.c
   :clang: -I/lib/clang/10.0.0/include, -I../inc, -std=gnu18, -DHAWKMOTH 
