# Libasm

```
- Assembly yourself!
```
```
Subject
	https://github.com/taoufiqjmari/1337-Common-Core/blob/main/Libasm/en.subject.pdf
```
```
Objectives
- The aim of this project is to get familiar with assembly language.
```
```
Learning outcomes
- Assembly
- Kernel and Low-Level
- Registers
```
```
Project prerequisites
- The nasm command (Netwide Assembler)
- The make command (Makefile)
- Git [optional]
```
```
How to use:
1 - Download parent folder of the project or clone it using git
	$> git clone https://github.com/taoufiqjmari/1337-Common-Core.git

2 - On Terminal, go to project directory
	$> cd Libasm

3 - Make the executable
	$> make

5 - Compile the main.c and libasm.a
	$> gcc main.c libasm.a -o libasm

6 - Run
	$> ./libasm
```
<br />

## Notes

### Registers

```
; 64-bit [QWORD]
R0  R1  R2  R3  R4  R5  R6  R7  R8  R9  R10  R11  R12  R13  R14  R15
RAX RCX RDX RBX RSP RBP RSI RDI

; 32-bit [DWORD]
R0D R1D R2D R3D R4D R5D R6D R7D R8D R9D R10D R11D R12D R13D R14D R15D
EAX ECX EDX EBX ESP EBP ESI EDI

; 16-bit [WORD]
R0W R1W R2W R3W R4W R5W R6W R7W R8W R9W R10W R11W R12W R13W R14W R15W
AX  CX  DX  BX  SP  BP  SI  DI

; 8-bit [BYTE]
R0B R1B R2B R3B R4B R5B R6B R7B R8B R9B R10B R11B R12B R13B R14B R15B
AL  CL  DL  BL  SPL BPL SIL DIL

; 128-bit (used for floating point operations mostly)
XMM0 ... XMM15
```

## Operations

```
; Save register
push	REG
pop		REG

; Set register value
mov		REG, VALUE	; DEST = VALUE

; Common operations
add		DEST, VALUE	; DEST = DEST + VALUE
sub		-			; DEST = DEST - VALUE
inc		REG			; REG++
dec		-			; REG--
and		DEST, REG	; DEST = DEST & REG
xor		-			; DEST = DEST ^ REG
xor		REG, REG	; = mov	REG, 0
mul		REG			; REG = REG * RAX
div		REG			; REG = REG / RAX

; Dereferenced value
		[REG]		; = *REG

; Compare
cmp	REG, VALUE		; Set flags used by jmp variants

; Label
label:
		jmp	label	; next jumps depends on compare flags from cmp
		je	-		; is equal
		jne	-		; is not equal
		jl	-		; < VALUE
		jle	-		; <= VALUE
		jz	-		; = 0
		jnz	-		; != 0
		jg	-		; > VALUE
		jge	-		; >= VALUE
```

## Functions

```
; Function call
call	FUNCTION

; Parameters registers
RDI RSI RDX RCX R8 R9

; Register to preserve
RBP RBX R12 R13 R14 R15	; You **MUST** push/pop them if you use them

; Return register
RAX

; syscall
mov		rax, CODE	; Then RDI, RSI etc.. for params
					; Add 0x2000000 to the syscall number, see table below
syscall
```

## Ressources

### General

* [tutorialspoint.com](https://www.tutorialspoint.com/assembly_programming/index.htm)
* [RIP Tutorial](https://riptutorial.com/x86)

### Subject notions

You must compile your assembly code with nasm.<br />You must write 64 bits ASM.
```
man nasm
/-f
nasm -hf | grep "macho64"
```

You can’t do inline ASM
```
Inline assembly (typically introduced by the asm keyword) gives the ability to embed assembly language source code within a C program.
In computer programming, an inline assembler is a feature of some compilers that allows low-level code written in assembly language to be embedded within a program, among code that otherwise has been compiled from a higher-level language such as C or Ada.
```

you must do ’.s’ files
* [.s vs .asm](https://stackoverflow.com/questions/34098596/assembly-files-difference-between-a-s-asm)

Beware of the "calling convention"
```
In this tutorial, you’ll look at registers the CPU uses and explore and modify parameters passed into function calls. You’ll also learn about common Apple computer architectures and how their registers are used within a function. This is known as an architecture’s calling convention.
```

Syscalls
```
System calls are the interface between user programs and the Linux kernel. They are used to let the kernel perform various system tasks, such as file access, process management and networking.
```

### Syntax

* [AT&T](https://riptutorial.com/x86/example/7935/at-t-assembler---as)

### Registers

* [Registers](https://riptutorial.com/assembly/example/22706/x64-registers)
* [Registers](https://www.cs.uaf.edu/2017/fall/cs301/lecture/09_11_registers.html)
