/*

sudo -s
cd /home/wgmlgz/Downloads/emsdk && source emsdk_env.sh && cd /home/wgmlgz/code/School/Forest/TreeLib/
emcc -o ../Frontend/build.js TreeLibExport.cpp -O3 -s WASM=1 -s NO_EXIT_RUNTIME=1  -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']" --preload-file file.txt   -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' -std=c++14

*/

#include "TreeLib.h"

#ifdef __EMSCRIPTEN__
#define PREFIX(type) EMSCRIPTEN_KEEPALIVE type
#include <emscripten.h>
#else 
#define PREFIX(type) type
#endif

#ifdef __cplusplus
extern "C" {
#endif

    PREFIX(int) EXPORT_readChar() {
        return readChar();
    }
    PREFIX(void) EXPORT_selectTree(int n) {
        selectTree(n);
    }
    PREFIX(void) EXPORT_insert(int insert_data) {
        insert(insert_data);
    }
    PREFIX(void) EXPORT_getName() {
        getName();
    }
    PREFIX(int) EXPORT_getStackSize() {
        return getStackSize();
    }
    PREFIX(void) EXPORT_getState(int state = -1) {
        getState(state);
    }
    PREFIX(void) EXPORT_getLines(int state = -1) {
        getLines(state);
    }


#ifdef __cplusplus
}
#endif
