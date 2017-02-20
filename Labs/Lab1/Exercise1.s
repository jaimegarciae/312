	.file	"Exercise1.c"
	.section	.rodata
	.align 8
.LC2:
	.string	"The largest number in the universe is %f\n"
	.text
	.globl	fpWeirdness
	.type	fpWeirdness, @function
fpWeirdness:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	movss	.LC1(%rip), %xmm0
	movss	%xmm0, -4(%rbp)
	jmp	.L2
.L3:
	movss	-8(%rbp), %xmm1
	movss	.LC1(%rip), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-8(%rbp), %xmm1
	movss	.LC1(%rip), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
.L2:
	movss	-4(%rbp), %xmm0
	ucomiss	-8(%rbp), %xmm0
	ja	.L3
	cvtss2sd	-8(%rbp), %xmm0
	movl	$.LC2, %edi
	movl	$1, %eax
	call	printf
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	fpWeirdness, .-fpWeirdness
	.section	.rodata
	.align 8
.LC3:
	.string	"The largest integer in the universe is %d\n"
	.text
	.globl	intWeirdness
	.type	intWeirdness, @function
intWeirdness:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$1, -4(%rbp)
	jmp	.L5
.L6:
	addl	$1, -4(%rbp)
.L5:
	cmpl	$0, -4(%rbp)
	jg	.L6
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	intWeirdness, .-intWeirdness
	.section	.rodata
	.align 8
.LC7:
	.string	"it takes %d tenths to equal a whole\n"
	.text
	.globl	fractionalWeirdness
	.type	fractionalWeirdness, @function
fractionalWeirdness:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movsd	.LC4(%rip), %xmm0
	movsd	%xmm0, -8(%rbp)
	movl	$0, -20(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	jmp	.L8
.L9:
	movsd	-16(%rbp), %xmm0
	addsd	-8(%rbp), %xmm0
	movsd	%xmm0, -16(%rbp)
	addl	$1, -20(%rbp)
.L8:
	movsd	.LC6(%rip), %xmm0
	ucomisd	-16(%rbp), %xmm0
	jnb	.L9
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	fractionalWeirdness, .-fractionalWeirdness
	.section	.rodata
	.align 8
.LC8:
	.string	"all done, hit ctrl-c to stop this program"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	fpWeirdness
	call	intWeirdness
	call	fractionalWeirdness
	movl	$.LC8, %edi
	call	puts
.L11:
	jmp	.L11
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC1:
	.long	1065353216
	.align 8
.LC4:
	.long	2576980378
	.long	1069128089
	.align 8
.LC6:
	.long	0
	.long	1072693248
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
