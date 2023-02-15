emcc main.c -o test.js -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap','UTF8ToString']" -s "EXPORTED_FUNCTIONS=['_malloc','_free']"
