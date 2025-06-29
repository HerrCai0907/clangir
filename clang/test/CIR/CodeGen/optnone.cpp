// RUN: %clang_cc1 -O0 -triple x86_64-unknown-linux-gnu -fclangir -emit-cir %s -o %t.cir
// RUN: FileCheck --input-file=%t.cir %s -check-prefix=CIR-O0
// RUN: %clang_cc1 -O0 -triple x86_64-unknown-linux-gnu -fclangir -emit-llvm %s -o %t.ll
// RUN: FileCheck --input-file=%t.ll %s -check-prefix=LLVM-O0

// RUN: %clang_cc1 -O2 -triple x86_64-unknown-linux-gnu -fclangir -emit-cir %s -o %t2.cir
// RUN: FileCheck --input-file=%t2.cir %s -check-prefix=CIR-O2
// RUN: %clang_cc1 -O2 -triple x86_64-unknown-linux-gnu -fclangir -emit-llvm %s -o %t2.ll
// RUN: FileCheck --input-file=%t2.ll %s -check-prefix=LLVM-O2

int s0(int a, int b) {
  int x = a + b;
  if (x > 0)
    x = 0;
  else
    x = 1;
  return x;
}

// CIR-O0: #fn_attr = #cir<extra({inline = #cir.inline<no>, nothrow = #cir.nothrow, optnone = #cir.optnone})>
// CIR-O0:   cir.func dso_local @_Z2s0ii(%arg0:{{.*}}, %arg1:{{.*}} -> {{.*}} extra(#fn_attr)

// CIR-O2-NOT: #fn_attr ={{.*}} optnone

// LLVM-O0: define dso_local i32 @_Z2s0ii(i32 %0, i32 %1) #[[#ATTR:]]
// LLVM-O0: attributes #[[#ATTR]] = { noinline nounwind optnone }
// LLVM-O2-NOT: attributes #[[#]] = { noinline nounwind optnone }
