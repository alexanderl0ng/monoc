#!/bin/bash
set -eu
cd "$(dirname "$0")"

# --- Unpack Arguments --------------------------------------------------------
for arg in "$@"; do declare $arg='1'; done
if [ -z "${gcc:+1}" ];      then clang=1; fi
if [ -z "${release:+1}" ];  then debug=1; fi
if [ -n "${debug:+1}" ];    then echo "[debug mode]"; fi
if [ -n "${release:+1}" ];  then echo "[release mode]"; fi
if [ -n "${clang:+1}" ];    then compiler="${CC:-clang}"; echo "[clang compile]"; fi
if [ -n "${gcc:+1}" ];      then compiler="${CC:-gcc}"; echo "[gcc compile]"; fi

# --- Compile/Link Line Definitions --------------------------------------------

diagnostic_flags=(
  -Wall
  -fdiagnostics-absolute-paths
  -Wno-unknown-warning-option
)

suppressed_warnings=(
  -Wno-unused-function
  -Wno-unused-variable
  -Wno-unused-value
  -Wno-unused-local-typedef
  -Wno-unused-but-set-variable
  -Wno-incompatible-pointer-types-discards-qualifiers
  -Wno-compare-distinct-pointer-types
  -Wno-writable-strings
  -Wno-missing-braces
  -Wno-initializer-overrides
  -Wno-deprecated-register
  -Wno-deprecated-declarations
  -Wno-single-bit-bitfield-constant-conversion
  -Wno-for-loop-analysis
)

platform_macros=(
  -D_USE_MATH_DEFINES
  -Dstrdup=_strdup
  -Dgnu_printf=printf
)

# clang_standard="-std=c++17"
clang_include="-I../src/"
clang_sources="../src/utils.c ../src/merge.c ../src/parallel_merge.c"
clang_common="${diagnostic_flags[*]} ${platform_macros[*]}"
# clang_common="$clang_common ${suppressed_warnings[*]}"
clang_debug="$compiler -g -O0 -DBUILD_DEBUG=1 $clang_common"
clang_release="$compiler -g -O2 -DBUILD_DEBUG=0 $clang_common"
clang_link=""
clang_out="-o"

# gcc_standard="-std=c++17"
gcc_include="-I../src/"
gcc_common="${diagnostic_flags[*]} ${platform_macros[*]}"
gcc_common="$gcc_common ${suppressed_warnings[*]}"
gcc_debug="$compiler -g -O0 -DBUILD_DEBUG=1 $gcc_common"
gcc_release="$compiler -g -O2 -DBUILD_DEBUG=0 $gcc_common"
gcc_link=""
gcc_out="-o"

# --- Choose Compile/Link Lines ------------------------------------------------
if [ -n "${gcc:+1}" ];      then compile_debug="$gcc_debug"; fi
if [ -n "${gcc:+1}" ];      then compile_release="$gcc_release"; fi
if [ -n "${gcc:+1}" ];      then compile_include="$gcc_include"; fi
if [ -n "${gcc:+1}" ];      then compile_link="$gcc_link"; fi
if [ -n "${gcc:+1}" ];      then out="$gcc_out"; fi
if [ -n "${clang:+1}" ];    then compile_debug="$clang_debug"; fi
if [ -n "${clang:+1}" ];    then compile_release="$clang_release"; fi
if [ -n "${clang:+1}" ];    then compile_include="$clang_include"; fi
if [ -n "${clang:+1}" ];    then compile_link="$clang_link"; fi
if [ -n "${clang:+1}" ];    then out="$clang_out"; fi
if [ -n "${debug:+1}" ];    then compile="$compile_debug"; fi
if [ -n "${release:+1}" ];  then compile="$compile_release"; fi

# --- Prep Directories ---------------------------------------------------------
mkdir -p build

# --- Build Everything ---------------------------------------------------------
cd build
if [ -n "${main:+1}" ];             then didbuild=1 && $compile ../src/main.c $clang_sources $compile_include $compile_link $out main; fi
if [ -n "${merge:+1}" ];            then didbuild=1 && $compile ../src/merge.c $compile_include $compile_link $out merge; fi
if [ -n "${parallel_merge:+1}" ];   then didbuild=1 && $compile ../src/parallel_merge.c $compile_include $compile_link $out parallel_merge; fi
cd ..

# --- Warn On No Builds -------------------------------------------------------
if [ -z "${didbuild:+1}" ]
then
  echo "[WARNING] no valid build target specified; must use build target names as arguments to this script, like \`./build.sh main\`"
  exit 1
fi
