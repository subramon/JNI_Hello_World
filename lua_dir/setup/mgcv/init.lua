local root = 'mgcv'
local G = {}
G.T = require (root .. '/bar')
G.foo = require 'foo' -- from lua_dir/lua/
G.foobar = require 'foobar' -- from lua_dir/lua/
return G
