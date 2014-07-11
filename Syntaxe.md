Variable
========

Types
-----

bool : boolean (true or false)
char : character ('x')
int  : integer number ([+-][0-9]+)
float :  floating point number ([+-][0-9]*.[0-9]+)
string : String ("value")
auto : auto detect the type (boolean, char ...)

TODO

* tuple
* tab
* dic

Other type (not directly usable)
--------------------------------

null : null value
function : callable variable. use it as name(params...) always return a value
library : loaded system library


Operation
---------

+,-,/,*,% operators can be used

the return value type depend of the parameters

--------------------------------------------------------------------------------
|left\right | bool   | char   | int    | float  | string | tuple | tab   | dic |
--------------------------------------------------------------------------------
|    bool   | bool   |        |        |        |        |       |       |     |
--------------------------------------------------------------------------------
|    char   | char   | char   |        |        |        |       |       |     |
--------------------------------------------------------------------------------
|    int    | int    | int    | int    |        |        |       |       |     |
--------------------------------------------------------------------------------
|    float  | float  | float  | float  | float  |        |       |       |     |
--------------------------------------------------------------------------------
|    string | string | string | string | string | string |       |       |     |
--------------------------------------------------------------------------------
|    tuple  | tuple  | tuple  | tuple  | tuple  | tuple  | tuple | tuble |     |
--------------------------------------------------------------------------------
|    tab    | tab    | tab    | tab    | tab    | tab    | tab   | tab   |     | 
--------------------------------------------------------------------------------
|    dic    |  X     |    X   |   X    |    X   |    X   |   X   |   X   | dic |
--------------------------------------------------------------------------------


not implemented

Logical
-------

and, ar, xor, not, <, <=, >, >=, equals,==, not_equals, != operators can be used

return a bool value

not implemented


Declaration
===========

type (name)+

A declaration is a value

Affectation
===========

type (name)+ = value
(name)+ = value

A affectation is a value
You can do :

bool b1 b2 b3 = char c1 c2 c3 = int i1 i2 i3 = float f1 f2 f3 = string s1 s2 s3 = auto a1 a2 a3 = "43.9"


Builtins
========

print
-----

display the value of the parameter

usage :
* print
** display all values in the context
* print value(,value)*
** display all the value separated with a space

show
----

same as print, but dispaly more information like types.

delete
------

remove a value from the current context


help
----

TODO

wget
----

TODO

run
---

TODO

compile
-------

take filenames as agment, and compile them as a library. The file have to be valid C or C++11 code.
Produce a Library variable

Usage:

compile value_list + [with [flags(value_list)] [link(value_list)] ] as identifier

The first value_list is the filename to use.
flags specify optionals flags for the compilation (like "-o3", "-Wall")
link specify optionals extern library to link with

identifer is the variable name where the library will be store (in context and in the hard drive)

g++ or clang have to be in system path.


source
------

TODO


Import
======

import
------

Load a library (.so/.dll) in the context as a variable

usage:
import libname as identifier

identifer is the variable name where the library will be store


from .. import
--------------

Load a function from a library.
The function have to be : export "C" (for name)

The result is a Variable function that is callable

usage:

from lib_var import (type)? funcname as identifer

libvar have to be a valid Library variable
type is optional and define the return type of the function. It can be bool, char,int, float or string
funcname is the function name in the library code
identifer is the name of the variable where the function will be store.







