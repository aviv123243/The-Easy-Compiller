; Floating-point constant macros
FP8 MACRO value
    LOCAL vname
    .const
    align 8
    vname REAL8 value
    .code
    EXITM <vname>
ENDM

.data
format_int db "%d ", 10, 0
format_float db "%lf ", 10, 0

.code
extern ExitProcess : proc
extern printf : proc

main PROC
	call function_main
	mov ecx, eax
	call ExitProcess
 main ENDP
function_printInt:
	push rbp
	mov rbp, rsp
	sub rsp, 16
	sub rsp, 32
	mov rdx, QWORD PTR [rbp+16]
	lea rcx, format_int
	call printf
	add rsp, 32
	mov eax, 0
	mov rsp, rbp
	pop rbp
	ret
function_printFloat:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	movsd xmm1, QWORD PTR [rbp+16]
	lea rcx, format_float
	call printf
	add rsp, 32
	mov eax, 0
	mov rsp, rbp
	pop rbp
	ret

function_mod:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov rbx, QWORD PTR [rbp+16]
	mov QWORD PTR [rbp-8], rbx
	mov rbx, QWORD PTR [rbp+24]
	mov QWORD PTR [rbp-16], rbx
	mov rbx, QWORD ptr [rbp - 16]
	mov r10, 0
	cmp rbx, r10
	sete al
	movzx rbx, al
	cmp rbx, 0
	jz L0
	mov r10, QWORD ptr [rbp - 8]
	mov rax, r10
	jmp function_mod_epilogue

	jmp L1
L0:
	mov r10, QWORD ptr [rbp - 8]
	mov r11, QWORD ptr [rbp - 8]
	mov r12, QWORD ptr [rbp - 16]
	mov rax, r11
	cqo
	idiv r12
	mov r11, rax
	mov r12, QWORD ptr [rbp - 16]
	imul r11, r12
	sub r10, r11
	mov rax, r10
	jmp function_mod_epilogue

L1:
function_mod_epilogue:
	mov rsp, rbp
	pop rbp
	ret

function_isPrime:
	push rbp
	mov rbp, rsp
	sub rsp, 48
	mov r10, QWORD PTR [rbp+16]
	mov QWORD PTR [rbp-8], r10
	mov r10, 1
	mov QWORD ptr [rbp - 24], r10
	mov r10, 2
	mov QWORD ptr [rbp - 16], r10
L2:
	mov r11, QWORD ptr [rbp - 16]
	mov r12, QWORD ptr [rbp - 8]
	cmp r11, r12
	setl al
	movzx r11, al
	cmp r11, 0
	jz L3
	mov r12, QWORD ptr [rbp - 16]
	push r12
	mov r12, QWORD ptr [rbp - 8]
	push r12
	call function_mod
	mov r12, rax
	mov r13, 0
	cmp r12, r13
	sete al
	movzx r12, al
	cmp r12, 0
	jz L4
	mov r13, 0
	mov QWORD ptr [rbp - 24], r13
	jmp L5
L4:
L5:
	mov r14, QWORD ptr [rbp - 16]
	mov r13, r14
	inc r14
	mov QWORD ptr [rbp - 16], r14
	jmp L2
L3:
	mov r14, QWORD ptr [rbp - 24]
	mov rax, r14
	jmp function_isPrime_epilogue

function_isPrime_epilogue:
	mov rsp, rbp
	pop rbp
	ret

function_main:
	push rbp
	mov rbp, rsp
	sub rsp, 16
	mov r14, 17
	mov QWORD ptr [rbp - 8], r14
	mov r14, QWORD ptr [rbp - 8]
	push r14
	call function_isPrime
	mov r14, rax
	push r14
	call function_printInt
	mov r14, rax
	mov r14, 0
	mov rax, r14
	jmp function_main_epilogue

function_main_epilogue:
	mov rsp, rbp
	pop rbp
	ret


END