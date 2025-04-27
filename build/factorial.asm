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

function_fact:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov rbx, QWORD PTR [rbp+16]
	mov QWORD PTR [rbp-8], rbx
	mov rbx, 1
	mov QWORD ptr [rbp - 24], rbx
	mov rbx, QWORD ptr [rbp - 8]
	mov QWORD ptr [rbp - 16], rbx
L0:
	mov r10, QWORD ptr [rbp - 16]
	mov r11, 0
	cmp r10, r11
	setg al
	movzx r10, al
	cmp r10, 0
	jz L1
	mov r11, QWORD ptr [rbp - 24]
	mov r12, QWORD ptr [rbp - 16]
	imul r11, r12
	mov QWORD ptr [rbp - 24], r11
	mov r12, QWORD ptr [rbp - 16]
	mov r11, r12
	dec r12
	mov QWORD ptr [rbp - 16], r12
	jmp L0
L1:
	mov r12, QWORD ptr [rbp - 24]
	mov rax, r12
	jmp function_fact_epilogue

function_fact_epilogue:
	mov rsp, rbp
	pop rbp
	ret

function_main:
	push rbp
	mov rbp, rsp
	sub rsp, 16
	mov r12, 5
	mov QWORD ptr [rbp - 8], r12
	mov r12, QWORD ptr [rbp - 8]
	push r12
	call function_fact
	mov r12, rax
	push r12
	call function_printInt
	mov r12, rax
	mov r12, 0
	mov rax, r12
	jmp function_main_epilogue

function_main_epilogue:
	mov rsp, rbp
	pop rbp
	ret


END