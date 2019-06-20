stockfish.pexe
==============

[![npm version](https://badge.fury.io/js/stockfish.pexe.svg)](https://badge.fury.io/js/stockfish.pexe)
[![Build Status](https://travis-ci.org/niklasf/stockfish.pexe.svg?branch=ddugovic)](https://travis-ci.org/niklasf/stockfish.pexe)
[![No maintenance intended](https://img.shields.io/badge/no%20maintenance%20intended-x-red.svg)](https://blog.chromium.org/2017/05/goodbye-pnacl-hello-webassembly.html)

A multi-threaded [Stockfish](https://github.com/official-stockfish/Stockfish)
that runs in Chrome using [PNaCl](https://www.chromium.org/nativeclient/pnacl).
Also see [stockfish.js](https://github.com/niklasf/stockfish.js) as a fallback.

Unmaintained, since [PNaCl is deprecated](https://blog.chromium.org/2017/05/goodbye-pnacl-hello-webassembly.html) and will be replaced by [WebAssembly](https://github.com/niklasf/stockfish.wasm).

About 500 KB uncompressed, 400 KB gzipped.

Usage
-----

See ``nacl/index.html`` for an example.

Building
--------

1. Install the [NaCl SDK](https://developer.chrome.com/native-client/sdk/download)
   and setup an environment variable
   ``NACL_SDK_ROOT=path/to/nacl_sdk/pepper_49``
2. ``cd nacl``
3. ``make``

Running
-------

- Start an HTTP server, for instance ``python3 -m http.server ./nacl``
- Browse http://127.0.0.1:8080/ in chrome

Changes to original Stockfish
-----------------------------

* Replace ``src/main.cpp`` with ``src/nacl.cpp``.
* Turn ``UCI::loop`` into ``UCI::command``.
* Remove Syzygy tablebases.
* Recover from (all but minimum) transposition table allocation failures.

Acknowledgements
----------------

Thanks to [@exoticorn](https://github.com/exoticorn/stockfish-nacl) for
providing a PNaCl module for the older Stockfish 5.
