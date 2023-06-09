; NOTE: Assertions have been autogenerated by utils/update_test_checks.py UTC_ARGS: --function-signature
; RUN: opt -trap-on-undef-br < %s -passes=ipsccp -S | FileCheck %s

; This test case used to end up like this:
;
;    While deleting: label %lor.rhs
;    Use still stuck around after Def is destroyed:  br i1 undef, label %lor.rhs, label %land.end
;    opt: ../lib/IR/Value.cpp: llvm::Value::~Value(): Assertion `use_empty() && "Uses remain when a value is destroyed!"' failed.
;
; due to ConstantFoldTerminator rewriting the switch into
;
;    br i1 undef, label %lor.rhs, label %land.end
;
; while SCCP implementation relied on the terminator to always be folded into
; an unconditional branch when ConstantFoldTerminator returned true.

define void @f4() {
; CHECK-LABEL: define {{[^@]+}}@f4() {
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[CALL:%.*]] = call i16 @f3(i16 undef)
; CHECK-NEXT:    ret void
;
entry:
  %call = call i16 @f3(i16 undef)
  ret void
}

define internal i16 @f3(i16 %p1) {
; CHECK-LABEL: define {{[^@]+}}@f3
; CHECK-SAME: (i16 [[P1:%.*]]) {
; CHECK-NEXT:  entry:
; CHECK-NEXT:    call void @llvm.trap()
; CHECK-NEXT:    unreachable
;
entry:
  switch i16 %p1, label %land.end [
  i16 0, label %land.end
  i16 1, label %lor.rhs
  ]

lor.rhs:
  br label %land.end

land.end:
  ret i16 0
}

