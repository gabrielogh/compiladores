_fibonacci:                      ## -- Begin function fibonacci
  .cfi_startproc
  enter $64, $0
  movq  %rdi, -8(%rbp)
  movq  $0, -24(%rbp)
  movq  $1, -32(%rbp)
  movq  $1, -16(%rbp)
LBB_1:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_2
  movq  -24(%rbp), %rax
  addq  -32(%rbp), %rax
  movq  %rax, -56(%rbp)
  movq  %rax, -40(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -24(%rbp)
  movq  -40(%rbp), %rax
  movq  %rax, -32(%rbp)
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -64(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_1
LBB_2:
  movq  -32(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_potencia:                      ## -- Begin function potencia
  .cfi_startproc
  enter $64, $0
  movq  %rdi, -8(%rbp)
  movq  %rsi, -16(%rbp)
  movq  $1, -24(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -32(%rbp)
LBB_3:
  movq  -24(%rbp), %rax
  cmpq  -16(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -40(%rbp)
  cmpl  $0, -40(%rbp)
  je LBB_4
  movq  -32(%rbp), %rax
  imulq  -8(%rbp), %rax
  movq  %rax, -48(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -56(%rbp)
  movq  %rax, -24(%rbp)
  jmp LBB_3
LBB_4:
  movq  -32(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_factorial:                      ## -- Begin function factorial
  .cfi_startproc
  enter $80, $0
  movq  %rdi, -8(%rbp)
  movq  $15, -16(%rbp)
  movq -8(%rbp), %rax
  cmpq  -16(%rbp), %rax
  setg %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -40(%rbp)
  cmpl  $0, -40(%rbp)
  je LBB_5
  movq  $1, %rax
  negq %rax
  movq  %rax, -48(%rbp)
  movq  -48(%rbp), %rax
  jmp LBB_6
LBB_5:
  movq  $0, -24(%rbp)
  movq  $1, -32(%rbp)
LBB_7:
  movq  -24(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -56(%rbp)
  cmpl  $0, -56(%rbp)
  je LBB_8
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -64(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  imulq  -24(%rbp), %rax
  movq  %rax, -72(%rbp)
  movq  %rax, -32(%rbp)
  jmp LBB_7
LBB_8:
  movq  -32(%rbp), %rax
LBB_6:
  leave
  retq                      ## -- End function
  .cfi_endproc

_nthprime:                      ## -- Begin function nthprime
  .cfi_startproc
  enter $128, $0
  movq  %rdi, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $2, -24(%rbp)
  movq  -8(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -40(%rbp)
  movq  %rax, -8(%rbp)
LBB_9:
  movq -8(%rbp), %rax
  cmpq $0, %rax
  setg %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_10
  movq  $0, -32(%rbp)
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -56(%rbp)
  movq  %rax, -16(%rbp)
LBB_11:
  movq  -32(%rbp), %rax
  xorq  $-1, %rax
  andq  $1, %rax
  movq  %rax, -64(%rbp)
  movq  -24(%rbp), %rax
  cmpq  -16(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -72(%rbp)
  movq  -64(%rbp), %rax
  andq  -72(%rbp), %rax
  movq  %rax, -80(%rbp)
  cmpl  $0, -80(%rbp)
  je LBB_12
  movq -16(%rbp), %rax
  cqto
  idivq -24(%rbp)
  movq %rdx, -88(%rbp)
  movq  -88(%rbp), %rax
  cmpq  $0, %rax
  sete %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq  %rsi, -96(%rbp)
  cmpl  $0, -96(%rbp)
  je LBB_13
  movq  $1, -32(%rbp)
  jmp LBB_14
LBB_13:
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -104(%rbp)
  movq  %rax, -24(%rbp)
LBB_14:
  jmp LBB_11
LBB_12:
  movq  $2, -24(%rbp)
  movq  -32(%rbp), %rax
  xorq  $-1, %rax
  andq  $1, %rax
  movq  %rax, -112(%rbp)
  cmpl  $0, -112(%rbp)
  je LBB_15
  movq  -8(%rbp), %rax
  subq  $1, %rax
  movq  %rax, -120(%rbp)
  movq  %rax, -8(%rbp)
LBB_15:
  jmp LBB_9
LBB_10:
  movq  -16(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_gcd:                      ## -- Begin function gcd
  .cfi_startproc
  enter $96, $0
  movq  %rdi, -8(%rbp)
  movq  %rsi, -16(%rbp)
  movq  $1, -24(%rbp)
  movq  -24(%rbp), %rax
  movq  %rax, -32(%rbp)
LBB_16:
  movq  -8(%rbp), %rax
  addq  -16(%rbp), %rax
  movq  %rax, -40(%rbp)
  movq  -24(%rbp), %rax
  cmpq  -40(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_17
  movq -8(%rbp), %rax
  cqto
  idivq -24(%rbp)
  movq %rdx, -56(%rbp)
  movq  -56(%rbp), %rax
  cmpq  $0, %rax
  sete %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq  %rsi, -64(%rbp)
  movq -16(%rbp), %rax
  cqto
  idivq -24(%rbp)
  movq %rdx, -72(%rbp)
  movq  -72(%rbp), %rax
  cmpq  $0, %rax
  sete %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq  %rsi, -80(%rbp)
  movq  -64(%rbp), %rax
  andq  -80(%rbp), %rax
  movq  %rax, -88(%rbp)
  cmpl  $0, -88(%rbp)
  je LBB_18
  movq  -24(%rbp), %rax
  movq  %rax, -32(%rbp)
LBB_18:
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -96(%rbp)
  movq  %rax, -24(%rbp)
  jmp LBB_16
LBB_17:
  movq  -32(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_test:                      ## -- Begin function test
  .cfi_startproc
  enter $240, $0
  movq  $3, %rdi
  callq  _factorial
  movq %rax, -64(%rbp)
  movq  %rax, -24(%rbp)
  movq  $4, %rdi
  callq  _factorial
  movq %rax, -80(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  movq  %rax, -88(%rbp)
  movq  -88(%rbp), %rdi
  movq  -32(%rbp), %rax
  movq  %rax, -96(%rbp)
  movq  -96(%rbp), %rsi
  callq  _gcd
  movq %rax, -104(%rbp)
  movq  %rax, -16(%rbp)
  movq  -16(%rbp), %rax
  movq  %rax, -112(%rbp)
  movq  -112(%rbp), %rdi
  callq  _print
  movq  -24(%rbp), %rax
  movq  %rax, -128(%rbp)
  movq  -128(%rbp), %rdi
  movq  -32(%rbp), %rax
  movq  %rax, -136(%rbp)
  movq  -136(%rbp), %rsi
  callq  _gcd
  movq %rax, -144(%rbp)
  movq  %rax, -40(%rbp)
  movq  -40(%rbp), %rax
  movq  %rax, -152(%rbp)
  movq  -152(%rbp), %rdi
  callq  _nthprime
  movq %rax, -160(%rbp)
  movq  %rax, -8(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -168(%rbp)
  movq  -168(%rbp), %rdi
  callq  _print
  movq  -40(%rbp), %rax
  movq  %rax, -184(%rbp)
  movq  -184(%rbp), %rdi
  callq  _nthprime
  movq %rax, -192(%rbp)
  movq  %rax, -48(%rbp)
  movq  $3, %rdi
  movq  -48(%rbp), %rax
  movq  %rax, -208(%rbp)
  movq  -208(%rbp), %rsi
  callq  _potencia
  movq %rax, -216(%rbp)
  movq  %rax, -8(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -224(%rbp)
  movq  -224(%rbp), %rdi
  callq  _print
  leave
  retq                      ## -- End function
  .cfi_endproc

_test1:                      ## -- Begin function test1
  .cfi_startproc
  enter $32, $0
  movq  $2, -8(%rbp)
  callq _test
  movq %rax, -16(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -24(%rbp)
  movq  -24(%rbp), %rdi
  callq  _print
  leave
  retq                      ## -- End function
  .cfi_endproc

    .globl  _main
_main:                      ## -- Begin function main
  .cfi_startproc
  enter $448, $0
  callq _printGuiones
  movq %rax, -40(%rbp)
  movq  $5, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $1, -24(%rbp)
LBB_19:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_20
  movq  -24(%rbp), %rax
  movq  %rax, -56(%rbp)
  movq  -56(%rbp), %rdi
  callq  _fibonacci
  movq %rax, -64(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -72(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -80(%rbp)
  movq  -80(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -96(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_19
LBB_20:
  callq _printGuiones
  movq %rax, -104(%rbp)
  movq  $4, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $3, -24(%rbp)
LBB_21:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -112(%rbp)
  cmpl  $0, -112(%rbp)
  je LBB_22
  movq  -24(%rbp), %rax
  movq  %rax, -120(%rbp)
  movq  -120(%rbp), %rdi
  callq  _factorial
  movq %rax, -128(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -136(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -144(%rbp)
  movq  -144(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -160(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_21
LBB_22:
  callq _printGuiones
  movq %rax, -168(%rbp)
  movq  $30, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $4, -24(%rbp)
LBB_23:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -176(%rbp)
  cmpl  $0, -176(%rbp)
  je LBB_24
  movq  -24(%rbp), %rax
  movq  %rax, -184(%rbp)
  movq  -184(%rbp), %rdi
  callq  _nthprime
  movq %rax, -192(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -200(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -208(%rbp)
  movq  -208(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -224(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_23
LBB_24:
  callq _printGuiones
  movq %rax, -232(%rbp)
  movq  $3, -8(%rbp)
  movq  $0, -16(%rbp)
LBB_25:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -240(%rbp)
  cmpl  $0, -240(%rbp)
  je LBB_26
  movq  $8, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -248(%rbp)
  movq  -248(%rbp), %rax
  movq  %rax, -256(%rbp)
  movq  -256(%rbp), %rdi
  movq  $2, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -264(%rbp)
  movq  -264(%rbp), %rax
  movq  %rax, -272(%rbp)
  movq  -272(%rbp), %rsi
  callq  _gcd
  movq %rax, -280(%rbp)
  movq  -280(%rbp), %rax
  movq  %rax, -288(%rbp)
  movq  -288(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -304(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_25
LBB_26:
  callq _printGuiones
  movq %rax, -312(%rbp)
  movq  $3, -8(%rbp)
  movq  $0, -16(%rbp)
LBB_27:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -320(%rbp)
  cmpl  $0, -320(%rbp)
  je LBB_28
  movq  $2, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -328(%rbp)
  movq  -328(%rbp), %rax
  movq  %rax, -336(%rbp)
  movq  -336(%rbp), %rdi
  movq  $1, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -344(%rbp)
  movq  -344(%rbp), %rax
  movq  %rax, -352(%rbp)
  movq  -352(%rbp), %rsi
  callq  _potencia
  movq %rax, -360(%rbp)
  movq  -360(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -368(%rbp)
  movq  -368(%rbp), %rax
  movq  %rax, -376(%rbp)
  movq  -376(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -392(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_27
LBB_28:
  callq _printGuiones
  movq %rax, -400(%rbp)
  callq _test
  movq %rax, -408(%rbp)
  callq _printGuiones
  movq %rax, -416(%rbp)
  callq _test1
  movq %rax, -424(%rbp)
  callq _printGuiones
  movq %rax, -432(%rbp)
  movq  $100, _globalVariable(%rip)
  movq  _globalVariable(%rip), %rdi
  callq  _print
  leave
  retq                      ## -- End function
  .cfi_endproc


  .comm _globalVariable,8,8                  ## @globalVariable
_fibonacci:                      ## -- Begin function fibonacci
  .cfi_startproc
  enter $64, $0
  movq  %rdi, -8(%rbp)
  movq  $0, -24(%rbp)
  movq  $1, -32(%rbp)
  movq  $1, -16(%rbp)
LBB_29:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_30
  movq  -24(%rbp), %rax
  addq  -32(%rbp), %rax
  movq  %rax, -56(%rbp)
  movq  %rax, -40(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -24(%rbp)
  movq  -40(%rbp), %rax
  movq  %rax, -32(%rbp)
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -64(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_29
LBB_30:
  movq  -32(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_potencia:                      ## -- Begin function potencia
  .cfi_startproc
  enter $64, $0
  movq  %rdi, -8(%rbp)
  movq  %rsi, -16(%rbp)
  movq  $1, -24(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -32(%rbp)
LBB_31:
  movq  -24(%rbp), %rax
  cmpq  -16(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -40(%rbp)
  cmpl  $0, -40(%rbp)
  je LBB_32
  movq  -32(%rbp), %rax
  imulq  -8(%rbp), %rax
  movq  %rax, -48(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -56(%rbp)
  movq  %rax, -24(%rbp)
  jmp LBB_31
LBB_32:
  movq  -32(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_factorial:                      ## -- Begin function factorial
  .cfi_startproc
  enter $80, $0
  movq  %rdi, -8(%rbp)
  movq  $15, -16(%rbp)
  movq -8(%rbp), %rax
  cmpq  -16(%rbp), %rax
  setg %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -40(%rbp)
  cmpl  $0, -40(%rbp)
  je LBB_33
  movq  $1, %rax
  negq %rax
  movq  %rax, -48(%rbp)
  movq  -48(%rbp), %rax
  jmp LBB_34
LBB_33:
  movq  $0, -24(%rbp)
  movq  $1, -32(%rbp)
LBB_35:
  movq  -24(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -56(%rbp)
  cmpl  $0, -56(%rbp)
  je LBB_36
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -64(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  imulq  -24(%rbp), %rax
  movq  %rax, -72(%rbp)
  movq  %rax, -32(%rbp)
  jmp LBB_35
LBB_36:
  movq  -32(%rbp), %rax
LBB_34:
  leave
  retq                      ## -- End function
  .cfi_endproc

_nthprime:                      ## -- Begin function nthprime
  .cfi_startproc
  enter $128, $0
  movq  %rdi, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $2, -24(%rbp)
  movq  -8(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -40(%rbp)
  movq  %rax, -8(%rbp)
LBB_37:
  movq -8(%rbp), %rax
  cmpq $0, %rax
  setg %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_38
  movq  $0, -32(%rbp)
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -56(%rbp)
  movq  %rax, -16(%rbp)
LBB_39:
  movq  -32(%rbp), %rax
  xorq  $-1, %rax
  andq  $1, %rax
  movq  %rax, -64(%rbp)
  movq  -24(%rbp), %rax
  cmpq  -16(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -72(%rbp)
  movq  -64(%rbp), %rax
  andq  -72(%rbp), %rax
  movq  %rax, -80(%rbp)
  cmpl  $0, -80(%rbp)
  je LBB_40
  movq -16(%rbp), %rax
  cqto
  idivq -24(%rbp)
  movq %rdx, -88(%rbp)
  movq  -88(%rbp), %rax
  cmpq  $0, %rax
  sete %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq  %rsi, -96(%rbp)
  cmpl  $0, -96(%rbp)
  je LBB_41
  movq  $1, -32(%rbp)
  jmp LBB_42
LBB_41:
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -104(%rbp)
  movq  %rax, -24(%rbp)
LBB_42:
  jmp LBB_39
LBB_40:
  movq  $2, -24(%rbp)
  movq  -32(%rbp), %rax
  xorq  $-1, %rax
  andq  $1, %rax
  movq  %rax, -112(%rbp)
  cmpl  $0, -112(%rbp)
  je LBB_43
  movq  -8(%rbp), %rax
  subq  $1, %rax
  movq  %rax, -120(%rbp)
  movq  %rax, -8(%rbp)
LBB_43:
  jmp LBB_37
LBB_38:
  movq  -16(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_gcd:                      ## -- Begin function gcd
  .cfi_startproc
  enter $96, $0
  movq  %rdi, -8(%rbp)
  movq  %rsi, -16(%rbp)
  movq  $1, -24(%rbp)
  movq  -24(%rbp), %rax
  movq  %rax, -32(%rbp)
LBB_44:
  movq  -8(%rbp), %rax
  addq  -16(%rbp), %rax
  movq  %rax, -40(%rbp)
  movq  -24(%rbp), %rax
  cmpq  -40(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_45
  movq -8(%rbp), %rax
  cqto
  idivq -24(%rbp)
  movq %rdx, -56(%rbp)
  movq  -56(%rbp), %rax
  cmpq  $0, %rax
  sete %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq  %rsi, -64(%rbp)
  movq -16(%rbp), %rax
  cqto
  idivq -24(%rbp)
  movq %rdx, -72(%rbp)
  movq  -72(%rbp), %rax
  cmpq  $0, %rax
  sete %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq  %rsi, -80(%rbp)
  movq  -64(%rbp), %rax
  andq  -80(%rbp), %rax
  movq  %rax, -88(%rbp)
  cmpl  $0, -88(%rbp)
  je LBB_46
  movq  -24(%rbp), %rax
  movq  %rax, -32(%rbp)
LBB_46:
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -96(%rbp)
  movq  %rax, -24(%rbp)
  jmp LBB_44
LBB_45:
  movq  -32(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_test:                      ## -- Begin function test
  .cfi_startproc
  enter $240, $0
  movq  $3, %rdi
  callq  _factorial
  movq %rax, -64(%rbp)
  movq  %rax, -24(%rbp)
  movq  $4, %rdi
  callq  _factorial
  movq %rax, -80(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  movq  %rax, -88(%rbp)
  movq  -88(%rbp), %rdi
  movq  -32(%rbp), %rax
  movq  %rax, -96(%rbp)
  movq  -96(%rbp), %rsi
  callq  _gcd
  movq %rax, -104(%rbp)
  movq  %rax, -16(%rbp)
  movq  -16(%rbp), %rax
  movq  %rax, -112(%rbp)
  movq  -112(%rbp), %rdi
  callq  _print
  movq  -24(%rbp), %rax
  movq  %rax, -128(%rbp)
  movq  -128(%rbp), %rdi
  movq  -32(%rbp), %rax
  movq  %rax, -136(%rbp)
  movq  -136(%rbp), %rsi
  callq  _gcd
  movq %rax, -144(%rbp)
  movq  %rax, -40(%rbp)
  movq  -40(%rbp), %rax
  movq  %rax, -152(%rbp)
  movq  -152(%rbp), %rdi
  callq  _nthprime
  movq %rax, -160(%rbp)
  movq  %rax, -8(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -168(%rbp)
  movq  -168(%rbp), %rdi
  callq  _print
  movq  -40(%rbp), %rax
  movq  %rax, -184(%rbp)
  movq  -184(%rbp), %rdi
  callq  _nthprime
  movq %rax, -192(%rbp)
  movq  %rax, -48(%rbp)
  movq  $3, %rdi
  movq  -48(%rbp), %rax
  movq  %rax, -208(%rbp)
  movq  -208(%rbp), %rsi
  callq  _potencia
  movq %rax, -216(%rbp)
  movq  %rax, -8(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -224(%rbp)
  movq  -224(%rbp), %rdi
  callq  _print
  leave
  retq                      ## -- End function
  .cfi_endproc

_test1:                      ## -- Begin function test1
  .cfi_startproc
  enter $32, $0
  movq  $2, -8(%rbp)
  callq _test
  movq %rax, -16(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -24(%rbp)
  movq  -24(%rbp), %rdi
  callq  _print
  leave
  retq                      ## -- End function
  .cfi_endproc

    .globl  _main
_main:                      ## -- Begin function main
  .cfi_startproc
  enter $448, $0
  callq _printGuiones
  movq %rax, -40(%rbp)
  movq  $5, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $1, -24(%rbp)
LBB_47:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_48
  movq  -24(%rbp), %rax
  movq  %rax, -56(%rbp)
  movq  -56(%rbp), %rdi
  callq  _fibonacci
  movq %rax, -64(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -72(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -80(%rbp)
  movq  -80(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -96(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_47
LBB_48:
  callq _printGuiones
  movq %rax, -104(%rbp)
  movq  $4, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $3, -24(%rbp)
LBB_49:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -112(%rbp)
  cmpl  $0, -112(%rbp)
  je LBB_50
  movq  -24(%rbp), %rax
  movq  %rax, -120(%rbp)
  movq  -120(%rbp), %rdi
  callq  _factorial
  movq %rax, -128(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -136(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -144(%rbp)
  movq  -144(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -160(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_49
LBB_50:
  callq _printGuiones
  movq %rax, -168(%rbp)
  movq  $30, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $4, -24(%rbp)
LBB_51:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -176(%rbp)
  cmpl  $0, -176(%rbp)
  je LBB_52
  movq  -24(%rbp), %rax
  movq  %rax, -184(%rbp)
  movq  -184(%rbp), %rdi
  callq  _nthprime
  movq %rax, -192(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -200(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -208(%rbp)
  movq  -208(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -224(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_51
LBB_52:
  callq _printGuiones
  movq %rax, -232(%rbp)
  movq  $3, -8(%rbp)
  movq  $0, -16(%rbp)
LBB_53:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -240(%rbp)
  cmpl  $0, -240(%rbp)
  je LBB_54
  movq  $8, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -248(%rbp)
  movq  -248(%rbp), %rax
  movq  %rax, -256(%rbp)
  movq  -256(%rbp), %rdi
  movq  $2, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -264(%rbp)
  movq  -264(%rbp), %rax
  movq  %rax, -272(%rbp)
  movq  -272(%rbp), %rsi
  callq  _gcd
  movq %rax, -280(%rbp)
  movq  -280(%rbp), %rax
  movq  %rax, -288(%rbp)
  movq  -288(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -304(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_53
LBB_54:
  callq _printGuiones
  movq %rax, -312(%rbp)
  movq  $3, -8(%rbp)
  movq  $0, -16(%rbp)
LBB_55:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -320(%rbp)
  cmpl  $0, -320(%rbp)
  je LBB_56
  movq  $2, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -328(%rbp)
  movq  -328(%rbp), %rax
  movq  %rax, -336(%rbp)
  movq  -336(%rbp), %rdi
  movq  $1, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -344(%rbp)
  movq  -344(%rbp), %rax
  movq  %rax, -352(%rbp)
  movq  -352(%rbp), %rsi
  callq  _potencia
  movq %rax, -360(%rbp)
  movq  -360(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -368(%rbp)
  movq  -368(%rbp), %rax
  movq  %rax, -376(%rbp)
  movq  -376(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -392(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_55
LBB_56:
  callq _printGuiones
  movq %rax, -400(%rbp)
  callq _test
  movq %rax, -408(%rbp)
  callq _printGuiones
  movq %rax, -416(%rbp)
  callq _test1
  movq %rax, -424(%rbp)
  callq _printGuiones
  movq %rax, -432(%rbp)
  movq  $100, _globalVariable(%rip)
  movq  _globalVariable(%rip), %rdi
  callq  _print
  leave
  retq                      ## -- End function
  .cfi_endproc


  .comm _globalVariable,8,8                  ## @globalVariable
  .comm _globalVariable,8,8                  ## @globalVariable
_fibonacci:                      ## -- Begin function fibonacci
  .cfi_startproc
  enter $64, $0
  movq  %rdi, -8(%rbp)
  movq  $0, -24(%rbp)
  movq  $1, -32(%rbp)
  movq  $1, -16(%rbp)
LBB_57:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_58
  movq  -24(%rbp), %rax
  addq  -32(%rbp), %rax
  movq  %rax, -56(%rbp)
  movq  %rax, -40(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -24(%rbp)
  movq  -40(%rbp), %rax
  movq  %rax, -32(%rbp)
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -64(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_57
LBB_58:
  movq  -32(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_potencia:                      ## -- Begin function potencia
  .cfi_startproc
  enter $64, $0
  movq  %rdi, -8(%rbp)
  movq  %rsi, -16(%rbp)
  movq  $1, -24(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -32(%rbp)
LBB_59:
  movq  -24(%rbp), %rax
  cmpq  -16(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -40(%rbp)
  cmpl  $0, -40(%rbp)
  je LBB_60
  movq  -32(%rbp), %rax
  imulq  -8(%rbp), %rax
  movq  %rax, -48(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -56(%rbp)
  movq  %rax, -24(%rbp)
  jmp LBB_59
LBB_60:
  movq  -32(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_factorial:                      ## -- Begin function factorial
  .cfi_startproc
  enter $80, $0
  movq  %rdi, -8(%rbp)
  movq  $15, -16(%rbp)
  movq -8(%rbp), %rax
  cmpq  -16(%rbp), %rax
  setg %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -40(%rbp)
  cmpl  $0, -40(%rbp)
  je LBB_61
  movq  $1, %rax
  negq %rax
  movq  %rax, -48(%rbp)
  movq  -48(%rbp), %rax
  jmp LBB_62
LBB_61:
  movq  $0, -24(%rbp)
  movq  $1, -32(%rbp)
LBB_63:
  movq  -24(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -56(%rbp)
  cmpl  $0, -56(%rbp)
  je LBB_64
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -64(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  imulq  -24(%rbp), %rax
  movq  %rax, -72(%rbp)
  movq  %rax, -32(%rbp)
  jmp LBB_63
LBB_64:
  movq  -32(%rbp), %rax
LBB_62:
  leave
  retq                      ## -- End function
  .cfi_endproc

_nthprime:                      ## -- Begin function nthprime
  .cfi_startproc
  enter $128, $0
  movq  %rdi, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $2, -24(%rbp)
  movq  -8(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -40(%rbp)
  movq  %rax, -8(%rbp)
LBB_65:
  movq -8(%rbp), %rax
  cmpq $0, %rax
  setg %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_66
  movq  $0, -32(%rbp)
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -56(%rbp)
  movq  %rax, -16(%rbp)
LBB_67:
  movq  -32(%rbp), %rax
  xorq  $-1, %rax
  andq  $1, %rax
  movq  %rax, -64(%rbp)
  movq  -24(%rbp), %rax
  cmpq  -16(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -72(%rbp)
  movq  -64(%rbp), %rax
  andq  -72(%rbp), %rax
  movq  %rax, -80(%rbp)
  cmpl  $0, -80(%rbp)
  je LBB_68
  movq -16(%rbp), %rax
  cqto
  idivq -24(%rbp)
  movq %rdx, -88(%rbp)
  movq  -88(%rbp), %rax
  cmpq  $0, %rax
  sete %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq  %rsi, -96(%rbp)
  cmpl  $0, -96(%rbp)
  je LBB_69
  movq  $1, -32(%rbp)
  jmp LBB_70
LBB_69:
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -104(%rbp)
  movq  %rax, -24(%rbp)
LBB_70:
  jmp LBB_67
LBB_68:
  movq  $2, -24(%rbp)
  movq  -32(%rbp), %rax
  xorq  $-1, %rax
  andq  $1, %rax
  movq  %rax, -112(%rbp)
  cmpl  $0, -112(%rbp)
  je LBB_71
  movq  -8(%rbp), %rax
  subq  $1, %rax
  movq  %rax, -120(%rbp)
  movq  %rax, -8(%rbp)
LBB_71:
  jmp LBB_65
LBB_66:
  movq  -16(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_gcd:                      ## -- Begin function gcd
  .cfi_startproc
  enter $96, $0
  movq  %rdi, -8(%rbp)
  movq  %rsi, -16(%rbp)
  movq  $1, -24(%rbp)
  movq  -24(%rbp), %rax
  movq  %rax, -32(%rbp)
LBB_72:
  movq  -8(%rbp), %rax
  addq  -16(%rbp), %rax
  movq  %rax, -40(%rbp)
  movq  -24(%rbp), %rax
  cmpq  -40(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_73
  movq -8(%rbp), %rax
  cqto
  idivq -24(%rbp)
  movq %rdx, -56(%rbp)
  movq  -56(%rbp), %rax
  cmpq  $0, %rax
  sete %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq  %rsi, -64(%rbp)
  movq -16(%rbp), %rax
  cqto
  idivq -24(%rbp)
  movq %rdx, -72(%rbp)
  movq  -72(%rbp), %rax
  cmpq  $0, %rax
  sete %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq  %rsi, -80(%rbp)
  movq  -64(%rbp), %rax
  andq  -80(%rbp), %rax
  movq  %rax, -88(%rbp)
  cmpl  $0, -88(%rbp)
  je LBB_74
  movq  -24(%rbp), %rax
  movq  %rax, -32(%rbp)
LBB_74:
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -96(%rbp)
  movq  %rax, -24(%rbp)
  jmp LBB_72
LBB_73:
  movq  -32(%rbp), %rax
  leave
  retq                      ## -- End function
  .cfi_endproc

_test:                      ## -- Begin function test
  .cfi_startproc
  enter $240, $0
  movq  $3, %rdi
  callq  _factorial
  movq %rax, -64(%rbp)
  movq  %rax, -24(%rbp)
  movq  $4, %rdi
  callq  _factorial
  movq %rax, -80(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  movq  %rax, -88(%rbp)
  movq  -88(%rbp), %rdi
  movq  -32(%rbp), %rax
  movq  %rax, -96(%rbp)
  movq  -96(%rbp), %rsi
  callq  _gcd
  movq %rax, -104(%rbp)
  movq  %rax, -16(%rbp)
  movq  -16(%rbp), %rax
  movq  %rax, -112(%rbp)
  movq  -112(%rbp), %rdi
  callq  _print
  movq  -24(%rbp), %rax
  movq  %rax, -128(%rbp)
  movq  -128(%rbp), %rdi
  movq  -32(%rbp), %rax
  movq  %rax, -136(%rbp)
  movq  -136(%rbp), %rsi
  callq  _gcd
  movq %rax, -144(%rbp)
  movq  %rax, -40(%rbp)
  movq  -40(%rbp), %rax
  movq  %rax, -152(%rbp)
  movq  -152(%rbp), %rdi
  callq  _nthprime
  movq %rax, -160(%rbp)
  movq  %rax, -8(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -168(%rbp)
  movq  -168(%rbp), %rdi
  callq  _print
  movq  -40(%rbp), %rax
  movq  %rax, -184(%rbp)
  movq  -184(%rbp), %rdi
  callq  _nthprime
  movq %rax, -192(%rbp)
  movq  %rax, -48(%rbp)
  movq  $3, %rdi
  movq  -48(%rbp), %rax
  movq  %rax, -208(%rbp)
  movq  -208(%rbp), %rsi
  callq  _potencia
  movq %rax, -216(%rbp)
  movq  %rax, -8(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -224(%rbp)
  movq  -224(%rbp), %rdi
  callq  _print
  leave
  retq                      ## -- End function
  .cfi_endproc

_test1:                      ## -- Begin function test1
  .cfi_startproc
  enter $32, $0
  movq  $2, -8(%rbp)
  callq _test
  movq %rax, -16(%rbp)
  movq  -8(%rbp), %rax
  movq  %rax, -24(%rbp)
  movq  -24(%rbp), %rdi
  callq  _print
  leave
  retq                      ## -- End function
  .cfi_endproc

    .globl  _main
_main:                      ## -- Begin function main
  .cfi_startproc
  enter $448, $0
  callq _printGuiones
  movq %rax, -40(%rbp)
  movq  $5, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $1, -24(%rbp)
LBB_75:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -48(%rbp)
  cmpl  $0, -48(%rbp)
  je LBB_76
  movq  -24(%rbp), %rax
  movq  %rax, -56(%rbp)
  movq  -56(%rbp), %rdi
  callq  _fibonacci
  movq %rax, -64(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -72(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -80(%rbp)
  movq  -80(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -96(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_75
LBB_76:
  callq _printGuiones
  movq %rax, -104(%rbp)
  movq  $4, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $3, -24(%rbp)
LBB_77:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -112(%rbp)
  cmpl  $0, -112(%rbp)
  je LBB_78
  movq  -24(%rbp), %rax
  movq  %rax, -120(%rbp)
  movq  -120(%rbp), %rdi
  callq  _factorial
  movq %rax, -128(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -136(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -144(%rbp)
  movq  -144(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -160(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_77
LBB_78:
  callq _printGuiones
  movq %rax, -168(%rbp)
  movq  $30, -8(%rbp)
  movq  $0, -16(%rbp)
  movq  $4, -24(%rbp)
LBB_79:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -176(%rbp)
  cmpl  $0, -176(%rbp)
  je LBB_80
  movq  -24(%rbp), %rax
  movq  %rax, -184(%rbp)
  movq  -184(%rbp), %rdi
  callq  _nthprime
  movq %rax, -192(%rbp)
  movq  %rax, -32(%rbp)
  movq  -24(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -200(%rbp)
  movq  %rax, -24(%rbp)
  movq  -32(%rbp), %rax
  movq  %rax, -208(%rbp)
  movq  -208(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -224(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_79
LBB_80:
  callq _printGuiones
  movq %rax, -232(%rbp)
  movq  $3, -8(%rbp)
  movq  $0, -16(%rbp)
LBB_81:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -240(%rbp)
  cmpl  $0, -240(%rbp)
  je LBB_82
  movq  $8, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -248(%rbp)
  movq  -248(%rbp), %rax
  movq  %rax, -256(%rbp)
  movq  -256(%rbp), %rdi
  movq  $2, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -264(%rbp)
  movq  -264(%rbp), %rax
  movq  %rax, -272(%rbp)
  movq  -272(%rbp), %rsi
  callq  _gcd
  movq %rax, -280(%rbp)
  movq  -280(%rbp), %rax
  movq  %rax, -288(%rbp)
  movq  -288(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -304(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_81
LBB_82:
  callq _printGuiones
  movq %rax, -312(%rbp)
  movq  $3, -8(%rbp)
  movq  $0, -16(%rbp)
LBB_83:
  movq  -16(%rbp), %rax
  cmpq  -8(%rbp), %rax
  setl %dl
  andb $1, %dl
  movzbl %dl, %esi
  movq %rsi, -320(%rbp)
  cmpl  $0, -320(%rbp)
  je LBB_84
  movq  $2, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -328(%rbp)
  movq  -328(%rbp), %rax
  movq  %rax, -336(%rbp)
  movq  -336(%rbp), %rdi
  movq  $1, %rax
  addq  -16(%rbp), %rax
  movq  %rax, -344(%rbp)
  movq  -344(%rbp), %rax
  movq  %rax, -352(%rbp)
  movq  -352(%rbp), %rsi
  callq  _potencia
  movq %rax, -360(%rbp)
  movq  -360(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -368(%rbp)
  movq  -368(%rbp), %rax
  movq  %rax, -376(%rbp)
  movq  -376(%rbp), %rdi
  callq  _print
  movq  -16(%rbp), %rax
  addq  $1, %rax
  movq  %rax, -392(%rbp)
  movq  %rax, -16(%rbp)
  jmp LBB_83
LBB_84:
  callq _printGuiones
  movq %rax, -400(%rbp)
  callq _test
  movq %rax, -408(%rbp)
  callq _printGuiones
  movq %rax, -416(%rbp)
  callq _test1
  movq %rax, -424(%rbp)
  callq _printGuiones
  movq %rax, -432(%rbp)
  movq  $100, _globalVariable(%rip)
  movq  _globalVariable(%rip), %rdi
  callq  _print
  leave
  retq                      ## -- End function
  .cfi_endproc


  .comm _globalVariable,8,8                  ## @globalVariable
  .comm _globalVariable,8,8                  ## @globalVariable
  .comm _globalVariable,8,8                  ## @globalVariable
