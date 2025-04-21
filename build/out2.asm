.data

.code
extern ExitProcess : proc

function_main:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov rbx, 1
	mov r10, 2
	add rbx, r10
	mov rax, rbx
	jmp function_main_epilogue:

function_main_epilogue:
	mov rsp, rbp
	pop rbp
	ret

main:
	call function_main
	mov ecx, eax
	call ExitProcess
END main
