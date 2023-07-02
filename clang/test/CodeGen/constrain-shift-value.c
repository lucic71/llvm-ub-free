// RUN: %clang_cc1 -triple x86_64-pc-linux-gnu -emit-llvm -fconstrain-shift-value -O2 -o - %s | FileCheck %s

char f(char x, char y) {
  // CHECK: %[[X:.*]] = zext i8 %[[I8X:.*]] to i32
  // CHECK: %[[I8MASK:.*]] = and i8 %[[Y:.*]], 31 
  // CHECK-NEXT: %[[MASK:.*]] = zext i8 %[[I8MASK]] to i32
  // CHECK-NEXT: %[[RES:.*]] = shl i32 %[[X]], %[[MASK]]

  return x << y;
}

int g(int x, int y) {
  // CHECK: %[[MASK:.*]] = and i32 %[[Y:.*]], 31 
  // CHECK-NEXT: %[[RES:.*]] = shl i32 %[[X:.*]], %[[MASK]]

  return x << y;
}

long h(long x, long y) {
  // CHECK: %[[MASK:.*]] = and i64 %[[Y:.*]], 63 
  // CHECK-NEXT: %[[RES:.*]] = shl i64 %[[X:.*]], %[[MASK]]

  return x << y;
}

char i(char x, long y) {
  // CHECK: %[[X:.*]] = zext i8 %[[I8X:.*]] to i32
  // CHECK: %[[TRUNCMASK:.*]] = trunc i64 %[[I64Y:.*]] to i32
  // CHECK: %[[MASK:.*]] = and i32 %[[TRUNCMASK]], 31 
  // CHECK-NEXT: %[[RES:.*]] = shl i32 %[[X]], %[[MASK]]

  return x << y;
}
