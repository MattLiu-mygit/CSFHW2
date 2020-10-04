/*
 * Assembly language implementation of hexdump functions
 * CSF Assignment 2
 * Matthew Liu
 * mliu78@jhu.edu
 */

	.section .rodata

	.section .text
		.globl hex_format_byte_as_hex
		.globl hex_to_printable
		.globl hex_format_offset

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
		movq $16, %r10
		divq %r10
		movb %dl, %r9b
		movb %al, %r8b
		cmpb $10, %r8b
		jl .Less_than_tens
			addb $87, %r8b
			JMP .To_ones
		.Less_than_tens:
			addb $48, %r8b
		.To_ones:
			cmpb $10, %r9b
			jl .Less_than_ones
			addb $87, %r9b
			JMP .After
		.Less_than_ones:
			addb $48, %r9b
		.After:
			movq $1, %rcx
			movb %r8b, (%rsi)
			movb %r9b, (%rsi, %rcx)
			movb $0, 1(%rsi, %rcx)
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
		cmpq $32, %rdi
		jl .Not_char
		cmpq $126, %rdi
		jg .Not_char
		movq %rdi, %rax
		ret
		.Not_char:
			movq $46, %rax
			ret

/* vim:ft=gas:
 */
