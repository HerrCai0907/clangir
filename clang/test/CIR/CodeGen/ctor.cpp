// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -fclangir -emit-cir %s -o %t.cir
// RUN: FileCheck --input-file=%t.cir %s

struct Struk {
  int a;
  Struk() {}
  void test() {}
};

void baz() {
  Struk s;
}

// CHECK: !rec_Struk = !cir.record<struct "Struk" {!s32i}>

// CHECK:   cir.func linkonce_odr @_ZN5StrukC2Ev(%arg0: !cir.ptr<!rec_Struk>
// CHECK-NEXT:     %0 = cir.alloca !cir.ptr<!rec_Struk>, !cir.ptr<!cir.ptr<!rec_Struk>>, ["this", init] {alignment = 8 : i64}
// CHECK-NEXT:     cir.store %arg0, %0 : !cir.ptr<!rec_Struk>, !cir.ptr<!cir.ptr<!rec_Struk>>
// CHECK-NEXT:     %1 = cir.load %0 : !cir.ptr<!cir.ptr<!rec_Struk>>, !cir.ptr<!rec_Struk>
// CHECK-NEXT:     cir.return

// CHECK:   cir.func linkonce_odr @_ZN5StrukC1Ev(%arg0: !cir.ptr<!rec_Struk>
// CHECK-NEXT:     %0 = cir.alloca !cir.ptr<!rec_Struk>, !cir.ptr<!cir.ptr<!rec_Struk>>, ["this", init] {alignment = 8 : i64}
// CHECK-NEXT:     cir.store %arg0, %0 : !cir.ptr<!rec_Struk>, !cir.ptr<!cir.ptr<!rec_Struk>>
// CHECK-NEXT:     %1 = cir.load %0 : !cir.ptr<!cir.ptr<!rec_Struk>>, !cir.ptr<!rec_Struk>
// CHECK-NEXT:     cir.call @_ZN5StrukC2Ev(%1) : (!cir.ptr<!rec_Struk>) -> ()
// CHECK-NEXT:     cir.return

// CHECK:   cir.func dso_local @_Z3bazv()
// CHECK-NEXT:     %0 = cir.alloca !rec_Struk, !cir.ptr<!rec_Struk>, ["s", init] {alignment = 4 : i64}
// CHECK-NEXT:     cir.call @_ZN5StrukC1Ev(%0) : (!cir.ptr<!rec_Struk>) -> ()
// CHECK-NEXT:     cir.return
