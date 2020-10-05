/* Hexdump main function, assembly language version */

	.section .text

	.globl main
	
main:
	pushq %rbp
	pushq	%r12 /* count */
	pushq	%r13 /* n */
	pushq	%r14 /* toInsert */
	pushq	%r15 /* loop count */
	subq $48, %rsp /* Alighment and making space for arrays */
	movq $0, %r12 
	movq $0, %r13
	movq %rsp, %rbp

	.LBegin:
		leaq 0(%rbp), %rdi
		call hex_read
		movq %rax, %r13
		testq %r13, %r13
		je .LAfter

		/* The first part of the output line (ie. "00000000: ") */
		leaq 17(%rbp), %rsi /* Converts the amount of times looped to a offset hex number*/
		movq %r12, %rdi
		call hex_format_offset
		addq $16, %rdi /* Adds a colon and space after the offset hex counter to form the first part of the output*/
		movq $58, 25(%rbp)
		movq $32, 26(%rbp)
		movq $0, 27(%rbp)
		leaq 17(%rbp), %rdi
		call hex_write_string

		/* The second part of the output line, which is the hex translation of the read input. */
		movq $0, %r15
		.LInner: 
			cmpq $16, %r15 /* While there are less than 16 elements printed, loop. */
			je .LOuter
	
			cmpq %r13, %r15 /* If there are no more hexes to print, jump to printing spaces. */
			jge .LSpaces

			/* Prints the hex character at index %r15 of the read input. */
			movq (%rbp, %r15), %rdi
			leaq 17(%rbp), %rsi
			call hex_format_byte_as_hex
			movb $32, 19(%rbp)
			movb $0, 20(%rbp)
			leaq 17(%rbp), %rdi
			call hex_write_string

			/* Modifies input to be a printable. */
			movb (%rbp, %r15), %dil
			call hex_to_printable
			movb %al, (%rbp, %r15)
			JMP .LAfterHexes

			.LSpaces: /* Adds spaces if there are no more hexes left to print. */
				movb $32, 17(%rbp)
				movb $32, 18(%rbp)
				movb $32, 19(%rbp)
				movb $0, 20(%rbp)
				leaq 17(%rbp), %rdi
				call hex_write_string

			.LAfterHexes:
				incq %r15
				JMP .LInner

		/* The third part of the output line, which is the 16 character input read and a newline character. */
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

	/* Reallignment and cleanup. */
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
