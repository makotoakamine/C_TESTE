	.file	"hello.c"
	.section	.rodata
.LC0:
	.string	" [%d] = %d \n"
.LC1:
	.string	"------------------------"
.LC2:
	.string	" [%d] = %f \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	$0, -96(%rbp)
	movq	$0, -88(%rbp)
	movq	$0, -80(%rbp)
	movq	$0, -72(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -16(%rbp)
	movl	$1000000, -100(%rbp)
	movl	$0, %edi
	call	time
	movq	%rax, %rdi
	movl	$0, %eax
	call	srand
	movl	$0, -104(%rbp)
	jmp	.L2
.L3:
	movl	$0, %eax
	call	rand
	movl	%eax, %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movslq	%edx, %rax
	movl	-96(%rbp,%rax,4), %eax
	leal	1(%rax), %ecx
	movslq	%edx, %rax
	movl	%ecx, -96(%rbp,%rax,4)
	addl	$1, -104(%rbp)
.L2:
	movl	-104(%rbp), %eax
	cmpl	-100(%rbp), %eax
	jb	.L3
	movl	$0, -104(%rbp)
	jmp	.L4
.L5:
	movl	-104(%rbp), %eax
	movl	-96(%rbp,%rax,4), %eax
	movl	-104(%rbp), %edx
	leal	1(%rdx), %ecx
	movl	%eax, %edx
	movl	%ecx, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -104(%rbp)
.L4:
	cmpl	$9, -104(%rbp)
	jbe	.L5
	movl	$.LC1, %edi
	call	puts
	movl	$0, -104(%rbp)
	jmp	.L6
.L11:
	movl	-104(%rbp), %eax
	movl	-96(%rbp,%rax,4), %eax
	movl	%eax, %eax
	testq	%rax, %rax
	js	.L7
	cvtsi2ssq	%rax, %xmm0
	jmp	.L8
.L7:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2ssq	%rdx, %xmm0
	addss	%xmm0, %xmm0
.L8:
	movl	-100(%rbp), %eax
	testq	%rax, %rax
	js	.L9
	cvtsi2ssq	%rax, %xmm1
	jmp	.L10
.L9:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2ssq	%rdx, %xmm1
	addss	%xmm1, %xmm1
.L10:
	divss	%xmm1, %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	movl	-104(%rbp), %eax
	addl	$1, %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$1, %eax
	call	printf
	addl	$1, -104(%rbp)
.L6:
	cmpl	$9, -104(%rbp)
	jbe	.L11
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
