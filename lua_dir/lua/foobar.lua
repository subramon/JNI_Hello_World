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
local function foobar(str, num)
  utils.cprint(str, num)
  return str .. "_" .. tostring(num)
end
return foobar
