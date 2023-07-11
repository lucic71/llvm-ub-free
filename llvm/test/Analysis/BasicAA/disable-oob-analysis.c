// RUN: clang -cc1 -O2 -emit-llvm -o - %s | FileCheck --check-prefixes=CHECK %s
// RUN: clang -cc1 -O2 -mllvm -disable-oob-analysis -emit-llvm -o - %s | FileCheck --check-prefixes=CHECK-DISABLED %s

extern void *memset(void *, int, unsigned long);

int foo(int c) {
  int dst[2];
  memset(dst, 0, 3 * sizeof(int));
  return dst[c];

  // CHECK: ret i32 undef

  // CHECK-DISABLED: [[DST:%.*]] = alloca [2 x i32], align 4
  // CHECK-DISABLED-NEXT: call void @llvm.lifetime.start.p0(i64 8, ptr nonnull [[DST]])
  // CHECK-DISABLED-NEXT: call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(12) [[DST]], i8 0, i64 12, i1 false)
  // CHECK-DISABLED-NEXT: [[IDXPROM:%.*]] = sext i32 [[C:%.*]] to i64
  // CHECK-DISABLED-NEXT: [[ARRAYIDX:%.*]] = getelementptr inbounds [2 x i32], ptr [[DST]], i64 0, i64 [[IDXPROM]]
  // CHECK-DISABLED-NEXT: [[RET:%.*]] = load i32, ptr [[ARRAYIDX]], align 4
  // CHECK-DISABLED-NEXT: call void @llvm.lifetime.end.p0(i64 8, ptr nonnull [[DST]])
  // CHECK-DISABLED-NEXT: ret i32 [[RET]]
}

int bar(int c) {
  int x = 1;
  int *y = &x + c;
  int *z = y + 4;
  int *t = &x + 8;
  return *t == *z;

  // CHECK: ret i32 0

  // CHECK-DISABLED: [[X:%.*]] = alloca i32, align 4
  // CHECK-DISABLED-NEXT: call void @llvm.lifetime.start.p0(i64 4, ptr nonnull [[X]])
  // CHECK-DISABLED-NEXT: store i32 1, ptr [[X]], align 4
  // CHECK-DISABLED-NEXT: [[IDXEXT:%.*]] = sext i32 [[C:%.*]] to i64
  // CHECK-DISABLED-NEXT: [[ADDPTR:%.*]] = getelementptr inbounds i32, ptr [[X]], i64 [[IDXEXT]]
  // CHECK-DISABLED-NEXT: [[ADDPTR1:%.*]] = getelementptr inbounds i32, ptr [[ADDPTR]], i64 4
  // CHECK-DISABLED-NEXT: [[ADDPTR2:%.*]] = getelementptr inbounds i32, ptr [[X]], i64 8
  // CHECK-DISABLED-NEXT: [[VAL0:%.*]] = load i32, ptr [[ADDPTR2]], align 4
  // CHECK-DISABLED-NEXT: [[VAL1:%.*]] = load i32, ptr [[ADDPTR1]], align 4
  // CHECK-DISABLED-NEXT: [[CMP:%.*]] = icmp eq i32 [[VAL0]], [[VAL1]]
  // CHECK-DISABLED-NEXT: [[CONV:%.*]] = zext i1 [[CMP]] to i32
  // CHECK-DISABLED-NEXT: call void @llvm.lifetime.end.p0(i64 4, ptr nonnull [[X]])
  // CHECK-DISABLED-NEXT: ret i32 [[CONV]]
}
