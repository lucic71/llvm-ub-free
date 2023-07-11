// RUN: %clang_cc1 -O2 -emit-llvm -o - %s | FileCheck --check-prefixes=CHECK %s
// RUN: %clang_cc1 -O2 -fdrop-inbounds-from-gep -emit-llvm -o - %s | FileCheck --check-prefixes=CHECK-ENABLED %s

int a[5];

int* foo1(int c) {
  return a + c;

  // CHECK: [[IDXEXT:%.*]] = sext i32 [[C:%.*]] to i64
  // CHECK-NEXT: [[ADDPTR:%.*]] = getelementptr inbounds i32, ptr [[A:@.*]], i64 [[IDXEXT]]
  // CHECK-NEXT: ret ptr [[ADDPTR]]

  // CHECK-ENABLED: [[IDXEXT:%.*]] = sext i32 [[C:%.*]] to i64
  // CHECK-ENABLED-NEXT: [[ADDPTR:%.*]] = getelementptr i32, ptr [[A:@.*]], i64 [[IDXEXT]]
  // CHECK-ENABLED-NEXT: ret ptr [[ADDPTR]]
}

int* foo2() {
  return a + 6;

  // CHECK: ret ptr getelementptr inbounds ([5 x i32], ptr @a, i64 1, i64 1)

  // CHECK-ENABLED: ret ptr getelementptr ([5 x i32], ptr @a, i64 1, i64 1)
}

int foo3() {
  return a[6];

  // CHECK:   [[RET:%.*]] = load i32, ptr getelementptr inbounds ([5 x i32], ptr @a, i64 1, i64 1)
  // CHECK-NEXT: ret i32 [[RET]]

  // CHECK-ENABLED:   [[RET:%.*]] = load i32, ptr getelementptr inbounds ([5 x i32], ptr @a, i64 1, i64 1)
  // CHECK-ENABLED-NEXT: ret i32 [[RET]]
}

int foo4() {
  return *(a + 6);

  // CHECK:   [[RET:%.*]] = load i32, ptr getelementptr inbounds ([5 x i32], ptr @a, i64 1, i64 1)
  // CHECK-NEXT: ret i32 [[RET]]

  // CHECK-ENABLED:   [[RET:%.*]] = load i32, ptr getelementptr ([5 x i32], ptr @a, i64 1, i64 1)
  // CHECK-ENABLED-NEXT: ret i32 [[RET]]
}
