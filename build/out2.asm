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
	mov rbx, 5
	mov r10, 5
	add rbx, r10
	mov r10, 4
	add rbx, r10
	mov QWORD ptr [rbp - 17], rbx
	mov r10, QWORD ptr [rbp - 8]
	mov rbx, r10
	inc r10
	mov QWORD ptr [rbp - 8], r10
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
