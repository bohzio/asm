	.file	"generaFascia.c"
	.globl	loads
	.data
	.align 16
	.type	loads, @object
	.size	loads, 20
loads:
	.value	2000
	.value	300
	.value	1200
	.value	1000
	.value	2000
	.value	1800
	.value	240
	.value	400
	.value	200
	.value	400
	.text
	.globl	generaFascia
	.type	generaFascia, @function
generaFascia:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L4:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L3
	movl	-4(%rbp), %eax
	cltq
	movzwl	loads(%rax,%rax), %eax
	cwtl
	addl	%eax, -8(%rbp)
.L3:
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L4
	cmpl	$1500, -8(%rbp)
	jg	.L5
	movl	$0, %eax
	jmp	.L6
.L5:
	cmpl	$3000, -8(%rbp)
	jg	.L7
	movl	$1, %eax
	jmp	.L6
.L7:
	cmpl	$4500, -8(%rbp)
	jg	.L8
	movl	$2, %eax
	jmp	.L6
.L8:
	movl	$3, %eax
.L6:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	generaFascia, .-generaFascia
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
