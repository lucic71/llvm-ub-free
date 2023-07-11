// RUN: %clang_cc1 -O0 -emit-llvm -o - %s | FileCheck --check-prefixes=CHECK %s
// RUN: %clang_cc1 -O0 -fno-use-default-alignment -emit-llvm -o - %s | FileCheck --check-prefixes=CHECK-ENABLED %s

int f(int c) {
  int a[5];
  return a[c];

  // CHECK: [[CADDR:%.*]] = alloca i32, align 4
  // CHECK-NEXT: [[A:%.*]] = alloca [5 x i32], align 16
  // CHECK-NEXT: store i32 [[C:%.*]], ptr [[CADDR]], align 4
  // CHECK-NEXT: [[VAL0:%.*]] = load i32, ptr [[CADDR]], align 4
  // CHECK-NEXT: [[IDXPROM:%.*]] = sext i32 [[VAL0]] to i64
  // CHECK-NEXT: [[ARRAYIDX:%.*]] = getelementptr inbounds [5 x i32], ptr [[A]], i64 0, i64 [[IDXPROM]]
  // CHECK-NEXT: [[VAL1:%.*]] = load i32, ptr [[ARRAYIDX]], align 4
  // CHECK-NEXT: ret i32 [[VAL1]]

  // CHECK-ENABLED: [[CADDR:%.*]] = alloca i32, align 4
  // CHECK-ENABLED-NEXT: [[A:%.*]] = alloca [5 x i32], align 16
  // CHECK-ENABLED-NEXT: store i32 [[C:%.*]], ptr [[CADDR]], align 1
  // CHECK-ENABLED-NEXT: [[VAL0:%.*]] = load i32, ptr [[CADDR]], align 1
  // CHECK-ENABLED-NEXT: [[IDXPROM:%.*]] = sext i32 [[VAL0]] to i64
  // CHECK-ENABLED-NEXT: [[ARRAYIDX:%.*]] = getelementptr inbounds [5 x i32], ptr [[A]], i64 0, i64 [[IDXPROM]]
  // CHECK-ENABLED-NEXT: [[VAL1:%.*]] = load i32, ptr [[ARRAYIDX]], align 1
  // CHECK-ENABLED-NEXT: ret i32 [[VAL1]]
}

int f1(int *a) {
  int b[5];
  memcpy(b, a, 5);
  return b[2];

 // CHECK: [[AADDR:%.*]] = alloca ptr, align 8
 // CHECK-NEXT: [[B:%.*]] = alloca [5 x i32], align 16
 // CHECK-NEXT: store ptr [[A:%.*]], ptr [[AADDR]], align 8
 // CHECK-NEXT: [[ARRAYDECAY:%.*]] = getelementptr inbounds [5 x i32], ptr [[B]], i64 0, i64 0
 // CHECK-NEXT: [[VAL0:%.*]] = load ptr, ptr [[AADDR]], align 8
 // CHECK-NEXT: call void @llvm.memcpy.p0.p0.i64(ptr align 16 [[ARRAYDECAY]], ptr align 4 [[VAL0]], i64 5, i1 false)
 // CHECK-NEXT: [[ARRAYIDX:%.*]] = getelementptr inbounds [5 x i32], ptr [[B]], i64 0, i64 2
 // CHECK-NEXT: [[VAL1:%.*]] = load i32, ptr [[ARRAYIDX]], align 8
 // CHECK-NEXT: ret i32 [[VAL1]]

 // CHECK-ENABLED: [[AADDR:%.*]] = alloca ptr, align 8
 // CHECK-ENABLED-NEXT: [[B:%.*]] = alloca [5 x i32], align 16
 // CHECK-ENABLED-NEXT: store ptr [[A:%.*]], ptr [[AADDR]], align 1
 // CHECK-ENABLED-NEXT: [[ARRAYDECAY:%.*]] = getelementptr inbounds [5 x i32], ptr [[B]], i64 0, i64 0
 // CHECK-ENABLED-NEXT: [[VAL0:%.*]] = load ptr, ptr [[AADDR]], align 1
 // CHECK-ENABLED-NEXT: call void @llvm.memcpy.p0.p0.i64(ptr align 1 [[ARRAYDECAY]], ptr align 1 [[VAL0]], i64 5, i1 false)
 // CHECK-ENABLED-NEXT: [[ARRAYIDX:%.*]] = getelementptr inbounds [5 x i32], ptr [[B]], i64 0, i64 2
 // CHECK-ENABLED-NEXT: [[VAL1:%.*]] = load i32, ptr [[ARRAYIDX]], align 1
 // CHECK-ENABLED-NEXT: ret i32 [[VAL1]]
}

