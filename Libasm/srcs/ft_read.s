section .text
	global _ft_read
	extern ___error

_ft_read:					; ssize_t	ft_read(int fildes, const void *buf, size_t nbytes);
							;					rdi			rsi				rdx
	mov rax, 0x2000003		; system call number (sys_read)
	syscall					; call kernel
	jc _err					; [jump if carry] if read failed, flag carries 1
	ret						; if not, return

_err:
	push	rax				; push errno to stack
	call	___error		; set rax to errno address
	pop		QWORD [rax]		; push errno to its address
	mov		rax, -1			; set return to -1
	ret						; return of function (rax)
