/************************************************************

File: event_data.h

The most basic data unit in EventShareOS is the C,V pair. 
The value is sent with the control action. A simple unsigned
integer is not really sufficient for most data. 

Structures and record data types need more than just 4 bytes.
event_data is a built in queue to allowing sharing of data 
between modules. The argument can be made why not share the 
data directly between modules?  While this is a valid question,
it does break the paradigm of not allowing direct communication 
between modules. Once any functions are shared between modules 
the the road to spaghetti code becomes real. 

Since events are SHARED between modules if subscribed, why not
large data chunks?  This module is mechanism to allow the 
sharing of large data between modules in the same manner as a
C,V pair.  

Assumptions:
The data shared will be written as bytes into memory. It is
the responsibility of each module to copy into their own 
memory the data. This is to prevent mucking up the data for
other modules. If you can read, then you can write. 

At each run of the event loop the data block will be cleaned
for next time use.  

Data blocks are allocated on the largest size needed. For 
example, if you have two data structs one is 8 bytes the other
is 12 bytes, then the minimum size for a data block is 12. 

Data block structure is statically allocated as one large 
chunk then dynamically divided at runtime. 

************************************************************/

#include <stdint.h>


