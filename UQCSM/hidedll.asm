;src https://gist.github.com/RIscRIpt/3545944c6a65870a733b

format MS COFF

public HideDLL as '_HideDLL'

include 'win32a.inc'

proc HideDLL c hDLL
	stdcall Search_LDR_Module, [hDLL]
	test eax, eax
	jz @f
		mov ebx, eax
		;Remove LDR Module from double linked list, where pNext is Flink and pPrev is Blink
		;*(1) Set next element (Flink) of previous element (Blink) equal to the next element (Flink) of current element
		;*(2) Set previous element (Blink) of next element (Flink) equal to the previous element (Blink) of current element
		;*(3) Blink and Flink points to the Flink of the same LIST Type, i.e. offset [eax] is NOT required!
		xor eax, eax
		;Repeat for 3 x LIST_ENTRY: InLoadOrderModuleList, InMemoryOrderModuleList, InInitializationOrderModuleList
		.loop:
			mov ecx, [ebx + eax + 0x00]			;Flink (Next element of current element)
			mov edx, [ebx + eax + 0x04]			;Blink (Previous element)
			mov [edx + 0x00], ecx				;Blink->Flink = Flink	*(1)
			mov [ecx + 0x04], edx				;Flink->Blink = Blink	*(2)	*(3)
			add eax, 8
			cmp eax, 8 * 3
			jb .loop
			cmp eax, 60 + 8
			je .loop_end
			mov eax, 60
			jmp .loop
		.loop_end:

		xor eax, eax
		;Clear LDR_MODULE.FullDllName (and BaseDllName as it only points to the part of FullDllName)
		mov ecx, [ebx + 0x24]					;FullDllName.Length
		mov edi, [ebx + 0x28]					;FullDllName.Buffer
		and ecx, 0x0000FFFF
		rep stosb
		@@:
	.done:
	ret
endp

proc Search_LDR_Module c module
	mov edx, [module]
	mov eax, [fs:0x30]			;Get PEB
	mov eax, [eax + 0x0C]		;PEB->PEB_LDR_DATA
	mov eax, [eax + 0x0C]		;PEB_LDR_DATA->InLoadOrderModuleList
	;Search our module:
	mov ecx, eax
	@@:
		mov eax, [eax]			;Our module cannot be first
		cmp [eax + 0x18], edx	;Compare base address of module
		je @f
		cmp eax, ecx			;Check if we've iterated thru the whole list (returned to beginning)
		jne @b
		xor eax, eax			;Nothing found
	@@:
	ret
endp
