; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=m68k-linux -verify-machineinstrs | FileCheck %s

; op reg, reg

define zeroext i8 @lsrb(i8 zeroext %a, i8 zeroext %b) nounwind {
; CHECK-LABEL: lsrb:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    move.b (11,%sp), %d0
; CHECK-NEXT:    move.b (7,%sp), %d1
; CHECK-NEXT:    lsr.b %d0, %d1
; CHECK-NEXT:    move.l %d1, %d0
; CHECK-NEXT:    and.l #255, %d0
; CHECK-NEXT:    rts
  %1 = lshr i8 %a, %b
  ret i8 %1
}

define zeroext i16 @lsrw(i16 zeroext %a, i16 zeroext %b) nounwind {
; CHECK-LABEL: lsrw:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    move.w (10,%sp), %d0
; CHECK-NEXT:    move.w (6,%sp), %d1
; CHECK-NEXT:    lsr.w %d0, %d1
; CHECK-NEXT:    move.l %d1, %d0
; CHECK-NEXT:    and.l #65535, %d0
; CHECK-NEXT:    rts
  %1 = lshr i16 %a, %b
  ret i16 %1
}

define i32 @lsrl(i32 %a, i32 %b) nounwind {
; CHECK-LABEL: lsrl:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    move.l (8,%sp), %d1
; CHECK-NEXT:    move.l (4,%sp), %d0
; CHECK-NEXT:    lsr.l %d1, %d0
; CHECK-NEXT:    rts
  %1 = lshr i32 %a, %b
  ret i32 %1
}

; op reg, imm

define zeroext i8 @lsrib(i8 zeroext %a) nounwind {
; CHECK-LABEL: lsrib:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    move.b (7,%sp), %d0
; CHECK-NEXT:    lsr.b #3, %d0
; CHECK-NEXT:    and.l #255, %d0
; CHECK-NEXT:    rts
  %1 = lshr i8 %a, 3
  ret i8 %1
}

define zeroext i16 @lsriw(i16 zeroext %a) nounwind {
; CHECK-LABEL: lsriw:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    move.w (6,%sp), %d0
; CHECK-NEXT:    lsr.w #5, %d0
; CHECK-NEXT:    and.l #65535, %d0
; CHECK-NEXT:    rts
  %1 = lshr i16 %a, 5
  ret i16 %1
}

define i32 @lsril(i32 %a) nounwind {
; CHECK-LABEL: lsril:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    move.l (4,%sp), %d0
; CHECK-NEXT:    lsr.l #7, %d0
; CHECK-NEXT:    rts
  %1 = lshr i32 %a, 7
  ret i32 %1
}