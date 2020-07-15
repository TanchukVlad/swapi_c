swapi -- creates GUI for swapi.dev using gtk+ 3
===========================================================

Description about swapi. This program creates GUI for swapi.dev using gtk+ 3.
Shows information about people, planets, species, vehicles, starships from 
The Star Wars API. Can search object and show the list of objects. 

.. c:autodoc:: inc/swapi.h src/swapi.c
   :clang: -I/lib/clang/10.0.0/include, -I../inc, -std=gnu18, -DHAWKMOTH 
