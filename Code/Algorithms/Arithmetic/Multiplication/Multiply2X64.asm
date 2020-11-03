.CODE

Mul2X64 PROC EXPORT
	
	clc									; clear the carry bit so a zero gets put in on the first rotate
	xor rax, rax
rotate:
	rcl qword ptr [rdx+8*rax], 1
	inc rax
	loop rotate

	sbb rax, rax						; put the carry into rax
	ret

Mul2X64 ENDP
END
