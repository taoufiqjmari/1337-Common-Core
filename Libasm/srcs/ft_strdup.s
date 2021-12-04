section .text
	global  _ft_strdup
	extern  _ft_strlen
	extern  _ft_strcpy
	extern  _malloc

_ft_strdup:					; char	*ft_strdup(const char *s1);
							;					rdi
	call	_ft_strlen		; call ft_strlen
	inc		rax				; increment rax for '\0'
	push	rdi				; save original string
	mov		rdi, rax		; set parameter for malloc
	call	_malloc			; call malloc
	cmp		rax, 0			; check if malloc failed
	je		_err			; if so, goto _err
	mov		rdi, rax		; set first parameter for ft_strcpy
	pop		rsi				; set second parameters for ft_strcpy
	call	_ft_strcpy		; call ft_strcpy
	ret						; return duplicated string

_err:
	ret						; return 0 in case malloc failed
