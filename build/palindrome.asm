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

function_reverse:
	push rbp
	mov rbp, rsp
	sub rsp, 48
	mov rbx, QWORD PTR [rbp+16]
	mov QWORD PTR [rbp-8], rbx
	mov rbx, 0
	mov QWORD ptr [rbp - 16], rbx
L0:
	mov rbx, QWORD ptr [rbp - 8]
	mov r10, 0
	cmp rbx, r10
	setne al
	movzx rbx, al
	cmp rbx, 0
	jz L1
	mov r10, QWORD ptr [rbp - 8]
	mov r11, 10
	mov rax, r10
	cqo
	idiv r11
	mov r10, rax
	mov QWORD ptr [rbp - 24], r10
	mov r10, QWORD ptr [rbp - 8]
	mov r11, QWORD ptr [rbp - 24]
	mov r12, 10
	imul r11, r12
	sub r10, r11
	mov QWORD ptr [rbp - 32], r10
	mov r10, QWORD ptr [rbp - 16]
	mov r11, 10
	imul r10, r11
	mov QWORD ptr [rbp - 16], r10
	mov r10, QWORD ptr [rbp - 16]
	mov r11, QWORD ptr [rbp - 32]
	add r10, r11
	mov QWORD ptr [rbp - 16], r10
	mov r10, QWORD ptr [rbp - 24]
	mov QWORD ptr [rbp - 8], r10
	jmp L0
L1:
	mov r10, QWORD ptr [rbp - 16]
	mov rax, r10
	jmp function_reverse_epilogue

function_reverse_epilogue:
	mov rsp, rbp
	pop rbp
	ret

function_isPalindrome:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov r10, QWORD PTR [rbp+16]
	mov QWORD PTR [rbp-8], r10
	mov r10, QWORD ptr [rbp - 8]
	push r10
	call function_reverse
	mov r10, rax
	mov QWORD ptr [rbp - 16], r10
	mov r10, QWORD ptr [rbp - 8]
	mov r11, QWORD ptr [rbp - 16]
	cmp r10, r11
	sete al
	movzx r10, al
	mov rax, r10
	jmp function_isPalindrome_epilogue

function_isPalindrome_epilogue:
	mov rsp, rbp
	pop rbp
	ret

function_main:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov r10, 1221
	mov QWORD ptr [rbp - 8], r10
	mov r10, QWORD ptr [rbp - 8]
	push r10
	call function_reverse
	mov r10, rax
	mov QWORD ptr [rbp - 16], r10
	mov r10, QWORD ptr [rbp - 16]
	push r10
	call function_printInt
	mov r10, rax
	mov r10, QWORD ptr [rbp - 8]
	push r10
	call function_isPalindrome
	mov r10, rax
	push r10
	call function_printInt
	mov r10, rax
	mov r10, 0
	mov rax, r10
	jmp function_main_epilogue

function_main_epilogue:
	mov rsp, rbp
	pop rbp
	ret


END