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

function_max:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov rbx, QWORD PTR [rbp+16]
	mov QWORD PTR [rbp-8], rbx
	mov rbx, QWORD PTR [rbp+24]
	mov QWORD PTR [rbp-16], rbx
	mov rbx, QWORD ptr [rbp - 8]
	mov r10, QWORD ptr [rbp - 16]
	cmp rbx, r10
	setg al
	movzx rbx, al
	cmp rbx, 0
	jz L0
	mov r10, QWORD ptr [rbp - 8]
	mov QWORD ptr [rbp - 24], r10
	jmp L1
L0:
	mov r10, QWORD ptr [rbp - 16]
	mov QWORD ptr [rbp - 24], r10
L1:
	mov r10, QWORD ptr [rbp - 24]
	mov rax, r10
	jmp function_max_epilogue

function_max_epilogue:
	mov rsp, rbp
	pop rbp
	ret

function_main:
	push rbp
	mov rbp, rsp
	sub rsp, 16
	mov r10, 2
	push r10
	mov r10, 1
	push r10
	call function_max
	mov r10, rax
	push r10
	call function_printInt
	mov r10, rax
function_main_epilogue:
	mov rsp, rbp
	pop rbp
	ret


END