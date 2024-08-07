local ffi = require 'ffi'
ffi.cdef([[
int
cprint(
    const char * const str,
    double num
    );
    ]]
    )
local utils = ffi.load("utils.so")
utils.cprint("abc", 123.456)
