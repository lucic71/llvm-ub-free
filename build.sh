#!/bin/sh -ex

# Compile with my clang
CC=/ssd/llvm-project-master/build/bin/clang CXX=/ssd/llvm-project-master/build/bin/clang++ PATH=/ssd/llvm-project-master/build/bin/clang:$PATH \
	cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD=X86 -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_ENABLE_PROJECTS="llvm;clang" -S ./llvm -B build/
ninja -C build/
