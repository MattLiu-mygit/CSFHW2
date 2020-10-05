/*
 * Assembly language implementation of hexdump functions
 * CSF Assignment 2
 * Matthew Liu
 * mliu78@jhu.edu
 */

	.section .rodata

	.section .text
		.globl hex_read
		.globl hex_write_string
		.globl hex_format_byte_as_hex
		.globl hex_to_printable
		.globl hex_format_offset	

	hex_read:
		addq $8, %rsp
		leaq 0(%rdi), %rsi	/*move buf array into corresponding register*/
		movq $0, %rdi				/*indicate stdin for sys_read*/
		movq $16, %rdx			/*reads 16 bytes*/
		movq $0, %rax				/*indicate read system call*/
		syscall
		movb $0, (%rax, %rsi)
		subq $8, %rsp
		ret

	hex_write_string:
		leaq 0(%rdi), %rsi	/*move buf array into corresponding register*/
		movq $1, %rdi				/*indicate stdout for sys_write*/
		movq $0, %rdx				/*writes until \0*/
		
		.LCounting:
			movb (%rsi, %rdx), %r8b
			testb %r8b, %r8b
			je .LCounted
			incq %rdx
			JMP .LCounting

		.LCounted:
			movq $1, %rax				/*indicate read system call*/
			syscall
			ret

/*
 * Format a long value as an offset string consisting of exactly 8
 * hex digits.  The formatted offset is stored in sbuf, which must
 * have enough room for a string of length 8.
 *
 * Parameters:
 *   rdi - The long from which we convert to the offset hex.
 *   rsi - The array to which we put the offset hex.
 */
	hex_format_offset:
		movq $7, %r8
		movq %rdi, %rax

		.LTop:
			cmpq $0, %r8
			jl .LOut
			movb $15, %r9b
			andb %al, %r9b 
			shrq $4, %rax
			cmpb $10, %r9b
			jl .Less_than_ten
			addb $87, %r9b
			JMP .LAfter

			.Less_than_ten:
				addb $48, %r9b

			.LAfter:
				movb %r9b, (%rsi, %r8)
				subq $1, %r8
				JMP .LTop

		.LOut:
		movb $0, 9(%rsi, %r8)
		ret

/*
 * Format a byte value (in the range 0-255) as string consisting
 * of two hex digits.  The string is stored in sbuf.
 *
 * Parameters:
 *   rdi - The long from which we convert to hex.
 *   rsi - The array to which we put the offset hex.
 */
	hex_format_byte_as_hex:
		movq %rdi, %rax
		movb $15, %r9b
		andb %al, %r9b 
		shrb $4, %al

		cmpb $0, %al
		jge .LTestOnes
		addb $16, %al

		.LTestOnes:
		cmpb $0, %r9b
		jge .LAllPositive
		addb $16, %r9b

		.LAllPositive:
		cmpb $10, %al
		jl .Less_than_tens
			addb $87, %al
			JMP .To_ones

		.Less_than_tens:
			addb $48, %al

		.To_ones:
			cmpb $10, %r9b
			jl .Less_than_ones
			addb $87, %r9b
			JMP .After

		.Less_than_ones:
			addb $48, %r9b

		.After:
			movb %al, 0(%rsi)
			movb %r9b, 1(%rsi)
			movb $0, 2(%rsi)
			ret

/*
 * Convert a byte value (in the range 0-255) to a printable character
 * value.  If byteval is already a printable character, it is returned
 * unmodified.  If byteval is not a printable character, then the
 * ASCII code for '.' should be returned.
 *
 * Parameters:
 *   rdi - The byte value.
 */
	hex_to_printable:
		cmpb $32, %dil
		jl .Not_char
		cmpb $126, %dil
		jg .Not_char
		movb %dil, %al
		ret

		.Not_char:
			movb $46, %al
			ret

/* vim:ft=gas:
 */
