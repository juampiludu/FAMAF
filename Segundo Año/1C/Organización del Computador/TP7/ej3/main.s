	.arch armv8-a
	.file	"main.c"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB0:
	.cfi_startproc
	# x0 = i
	# x1 = j
	# x2 = k
	# x3 = N
	# x9 = i==N
	# x10 = j==N
	sub x9, x0, x3		# x9 = x0 - x3
	cbz x9, .True		# if x9 == 0 then True
	sub x10, x1, x3		# x10 = x1 - x3
	cbz x9, .True		# if x9 == 0 then True
	add x0, x0, 1		# x0 = x0 + 1
	add x1, x1, 1		# x1 = x1 + 1
	b .end				# salto a end
	ret					# return x0
	.cfi_endproc
.True:
	add x2, x2, 1		# x2 = x2 + 1
.end:
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
