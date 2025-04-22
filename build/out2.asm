.data

.code
extern ExitProcess : proc

function_main:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov rbx, QWORD ptr [rbp+16]
	mov QWORD ptr [rbp-8], rbx
	movzx rbx, BYTE ptr [rbp+24]
	mov BYTE ptr [rbp-16], bl
	mov rbx, QWORD ptr [rbp - 8]
	dec QWORD ptr [rbp - 8]
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
