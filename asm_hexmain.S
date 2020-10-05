/* Hexdump main function, assembly language version */

	.section .text

	.globl main
main:
	pushq %rbp
	pushq	%r12 /*count*/
	pushq	%r13 /*n*/
	pushq	%r14 /*toInsert*/
	pushq	%r15 /*loopvar*/
	subq $48, %rsp
	movq $0, %r12 
	movq $0, %r13
	movq %rsp, %rbp

	.LBegin:
		leaq 0(%rbp), %rdi
		call hex_read
		movq %rax, %r13
		testq %r13, %r13
		je .LAfter

		leaq 17(%rbp), %rsi /*location*/
		movq %r12, %rdi
		call hex_format_offset
		addq $16, %rdi
		movq $58, 25(%rbp)
		movq $32, 26(%rbp)
		movq $0, 27(%rbp)
		leaq 17(%rbp), %rdi
		call hex_write_string
		movq $0, %r15
		.LInner:/*for size of n, loop*/
			cmpq $16, %r15
			je .LOuter
			cmpq %r13, %r15
			jge .LSpaces/*loop thru the first 16 char*/

			movq (%rbp, %r15), %rdi
			leaq 17(%rbp), %rsi
			call hex_format_byte_as_hex
			movb $32, 19(%rbp)
			movb $0, 20(%rbp)
			leaq 17(%rbp), %rdi
			call hex_write_string

			movb (%rbp, %r15), %dil
			call hex_to_printable
			movb %al, (%rbp, %r15)
			JMP .LAfterHexes

			.LSpaces:
				movb $32, 17(%rbp)
				movb $32, 18(%rbp)
				movb $32, 19(%rbp)
				movb $0, 20(%rbp)
				leaq 17(%rbp), %rdi
				call hex_write_string

			.LAfterHexes:
				incq %r15
				JMP .LInner
		.LOuter:
			movq $32, 17(%rbp)
			leaq 17(%rbp), %rdi
			call hex_write_string
			leaq 0(%rbp), %rdi
			call hex_write_string
			movq $10, 17(%rbp)
			movq $0, 18(%rbp)
			leaq 17(%rbp), %rdi
			call hex_write_string

			addq $16, %r12
			JMP .LBegin

	.LAfter:
		addq $48, %rsp
		popq %r15
		popq %r14
		popq %r13
		popq %r12
		popq %rbp
		movq $0, %rax
		ret

/* vim:ft=gas:
 */
