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

function_swap:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov rbx, QWORD PTR [rbp+16]
	mov QWORD PTR [rbp-8], rbx
	mov rbx, QWORD PTR [rbp+24]
	mov QWORD PTR [rbp-16], rbx
	mov rbx, QWORD ptr [rbp - 8]
	mov rbx, [rbx]
	mov r10, QWORD ptr [rbp - 16]
	mov r10, [r10]
	xor rbx, r10
	mov r10, QWORD ptr [rbp - 8]
	mov QWORD PTR [r10], rbx
	mov rbx, QWORD ptr [rbp - 8]
	mov rbx, [rbx]
	mov r10, QWORD ptr [rbp - 16]
	mov r10, [r10]
	xor rbx, r10
	mov r10, QWORD ptr [rbp - 16]
	mov QWORD PTR [r10], rbx
	mov rbx, QWORD ptr [rbp - 8]
	mov rbx, [rbx]
	mov r10, QWORD ptr [rbp - 16]
	mov r10, [r10]
	xor rbx, r10
	mov r10, QWORD ptr [rbp - 8]
	mov QWORD PTR [r10], rbx
	mov rbx, 0
	mov rax, rbx
	jmp function_swap_epilogue

function_swap_epilogue:
	mov rsp, rbp
	pop rbp
	ret

function_main:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov rbx, 2
	mov QWORD ptr [rbp - 8], rbx
	mov rbx, 7
	mov QWORD ptr [rbp - 16], rbx
	mov rbx, QWORD ptr [rbp - 8]
	push rbx
	call function_printInt
	mov rbx, rax
	mov rbx, QWORD ptr [rbp - 16]
	push rbx
	call function_printInt
	mov rbx, rax
	lea rbx, QWORD ptr [rbp - 16]
	push rbx
	lea rbx, QWORD ptr [rbp - 8]
	push rbx
	call function_swap
	mov rbx, rax
	mov rbx, QWORD ptr [rbp - 8]
	push rbx
	call function_printInt
	mov rbx, rax
	mov rbx, QWORD ptr [rbp - 16]
	push rbx
	call function_printInt
	mov rbx, rax
	mov rbx, 0
	mov rax, rbx
	jmp function_main_epilogue

function_main_epilogue:
	mov rsp, rbp
	pop rbp
	ret


END