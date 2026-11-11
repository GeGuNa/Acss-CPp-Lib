#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"
RAYLIB_INCLUDE="$BUILD_DIR/_deps/raylib-src/src"
RAYLIB_LIB_DIR="$BUILD_DIR/_deps/raylib-build/raylib"

if [ ! -f "$BUILD_DIR/libacss.a" ]; then
    echo "error: $BUILD_DIR/libacss.a not found." >&2
    echo "Build the main project first:" >&2
    echo "  cd \"$PROJECT_ROOT\" && cmake -B build -S . && cmake --build build --target acss" >&2
    exit 1
fi
if [ ! -d "$RAYLIB_INCLUDE" ] || [ ! -d "$RAYLIB_LIB_DIR" ]; then
    echo "error: raylib headers/library not found under $BUILD_DIR/_deps -- " >&2
    echo "this script only supports the FetchContent-built raylib, not a system-installed one." >&2
    exit 1
fi

if [ "$#" -gt 0 ]; then
    FILES=("$@")
else
    shopt -s nullglob
    FILES=("$SCRIPT_DIR"/*.cpp)
    shopt -u nullglob
    if [ "${#FILES[@]}" -eq 0 ]; then
        echo "no .cpp files found in $SCRIPT_DIR"
        exit 0
    fi
fi

PLATFORM_LIBS="-lm -lpthread -ldl -lX11"
if [[ "$(uname -s)" == "Darwin" ]]; then
    PLATFORM_LIBS="-framework IOKit -framework Cocoa -framework OpenGL"
fi

for f in "${FILES[@]}"; do
    if [[ "$f" != /* ]]; then f="$SCRIPT_DIR/$f"; fi
    if [ ! -f "$f" ]; then
        echo "skipping $f -- not found" >&2
        continue
    fi
    out="${f%.cpp}"
    echo "compiling $(basename "$f") -> $(basename "$out")"
    g++ -std=c++14 -O2 \
        -I "$PROJECT_ROOT/include" -I "$RAYLIB_INCLUDE" \
        "$f" \
        -L "$BUILD_DIR" -lacss \
        -L "$RAYLIB_LIB_DIR" -lraylib \
        $PLATFORM_LIBS \
        -o "$out"
done

echo "done."
