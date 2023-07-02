// RUN: %clang_cc1 -triple x86_64-pc-linux-gnu -emit-llvm -fcheck-div-rem-overflow -o - %s | FileCheck %s

int f(int x, int y) {
  // CHECK: %[[B0:.*]] = icmp eq i32 %[[D:.*]], 0
  // CHECK: %[[B1:.*]] = icmp eq i32 %[[N:.*]], -2147483648
  // CHECK: %[[B2:.*]] = icmp eq i32 %[[D]], -1
  // CHECK: %[[B3:.*]] = and i1 %[[B1]], %[[B2]]
  // CHECK: %[[B4:.*]] = or i1 %[[B0]], %[[B3]]
  // CHECK: br i1 %[[B4]], label %[[L2:[0-9a-z_.]*]], label %[[L1:[0-9a-z_.]*]]

  // CHECK: {{^|:}}[[L1]]
  // CHECK-NEXT: sdiv i32 %[[N]], %[[D]]

  // CHECK: {{^|:}}[[L2]]
  // CHECK-NEXT: call void @llvm.trap()
  // CHECK-NEXT: unreachable

  return x / y;
}

int g(int x, int y) {
  // CHECK: %[[B0:.*]] = icmp eq i32 %[[D:.*]], 0
  // CHECK: %[[B1:.*]] = icmp eq i32 %[[N:.*]], -2147483648
  // CHECK: %[[B2:.*]] = icmp eq i32 %[[D]], -1
  // CHECK: %[[B3:.*]] = and i1 %[[B1]], %[[B2]]
  // CHECK: %[[B4:.*]] = or i1 %[[B0]], %[[B3]]
  // CHECK: br i1 %[[B4]], label %[[L2:[0-9a-z_.]*]], label %[[L1:[0-9a-z_.]*]]

  // CHECK: {{^|:}}[[L1]]
  // CHECK-NEXT: srem i32 %[[N]], %[[D]]

  // CHECK: {{^|:}}[[L2]]
  // CHECK-NEXT: call void @llvm.trap()
  // CHECK-NEXT: unreachable

  return x % y;
}
