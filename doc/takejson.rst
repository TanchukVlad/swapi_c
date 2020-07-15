TakeJson -- takes json file using httpie to make an API request for a resource.
===============================================================================

This file makes rerquest to the swapi.dev and takes JSON file. 
Uses libcurl -- the multiprotocol file transfer library. 
More about libcurl: https://curl.haxx.se/libcurl/.

.. c:autodoc:: inc/takejson.h src/takejson.c
   :clang: -I/lib/clang/10.0.0/include, -I../inc, -std=gnu18, -DHAWKMOTH 

