.const
FACTOR_ real8 1.247
.code
;static void CombSort_(double* Array, unsigned long long n)
CombSort_ proc	
		vcvtsi2sd xmm6,xmm6, rdx
		vmovsd xmm7, [FACTOR_]
		vdivsd xmm3, xmm6, xmm7
		mov r10, 1
		vcvtsi2sd xmm6,xmm6, rdx

WhileGapFactorMoreThan1:
		vmovq r8, xmm3
		xor r9,r9
		mov r10, r8
		
		ArraySwapValues:

				vmovsd xmm4, real8 ptr[rcx + r9 * 8]
				vmovsd xmm5, real8 ptr[rcx + r10 * 8]
				
				inc r9
				inc r10
				cmp r10, rdx
				jge GapDecreasing

				vcomisd xmm4,xmm5
				jle ArraySwapValues
				dec r9
				dec r10
				vmovsd real8 ptr[rcx + r10 * 8], xmm4
				vmovsd real8 ptr[rcx + r9 * 8], xmm5
				inc r10
				inc r9
				jmp ArraySwapValues

		GapDecreasing:
			vdivsd xmm3, xmm3, xmm7
			
			vcomisd xmm3, xmm6
			jle GapFactorLessThan1Done
		  jmp WhileGapFactorMoreThan1

GapFactorLessThan1Done:
		ret

		CombSort_ endp
		end

