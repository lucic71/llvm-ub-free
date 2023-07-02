// RUN: %clang_cc1 -fno-constrain-bool-value -emit-llvm -O2 %s -o - | FileCheck %s

bool f(bool *x) {
  // CHECK: %[[CVAL:.*]] = load i8, ptr %{{.*}}, align 1, !tbaa !{{.*}}
  // CHECK: %[[ANDRES:.*]] = and i8 %[[CVAL]], 1
  // CHECK: %[[TOBOOL:.*]] = icmp ne i8 %[[ANDRES]], 0
  // CHECK: ret i1 %[[TOBOOL]]
  return *x;
}

// CHECK-NOT: [[RANGE_i8_0_2:.*]] = !{i8 0, i8 2}
