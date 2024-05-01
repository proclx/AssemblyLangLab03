#include <iostream>
void Task1()
{
	int a, b, c, d, x;
	int values[5] = { 0, 0, 0, 0, 0 }; // ����� ��� ���������� �(�)

	a = -6; b = 4; c = 8; d = 2;
	__asm {
		mov eax, [values]
		push eax // ���������� � ���� ������ ������� ������
		mov cx, 5 // ������� ������� ����� 
	start: // ������� �����
		mov ax, 3 // ��� ���������� x = 3 - �� 
		sub ax, cx // �������� ������� �������� �
		cwde // ���������� ax �� eax
		mov ebx, eax // �������� x � ebx
		mov eax, a // ����� �
		cmp ebx, 1 // ��������� � � ��������
		jl less_ // ���� � ����� 1, ���������� �� ���� less
		je equals // ���� � ������� 1, ���������� �� equals

		imul eax // a^2
		sub eax, ebx // a^2-x
		cdq // ���������� a^2-x �� ��������� �����
		mov ebx, c // ����� c
		idiv ebx // (a^2-x)/c
		jmp result // ���������� �� ���� result
	less_:
		mov edx, 2
		imul edx // a*2
		imul ebx // a*2*x
		add eax, 5 // a*2*x+5
		jmp result // ���������� �� ���� result
	equals:
		mov ebx, b // ����� b
		sub eax, ebx // a-b
		cdq // ���������� a-b �� ��������� �����
		mov ebx, d // ����� d
		idiv ebx // (a-b)/d
		jmp result // ���������� �� ���� result
	result:
		pop ebx // ���������� � ����� ������ ������
		mov[values + ebx], eax // �������� ��������� �� �������� �������
		add ebx, 4 // ������� �������� ������
		push ebx // ���������� � ���� ���� ������
		loop start // ����� �����
		pop ebx
	}
	for (int i = 0; i < 5; i++) 
	{
		std::cout << values[i] << std::endl;
	}
	system("pause");
}

void Option15()
{
	int a = 7;
	int y1, y2;
	int values[5] = { 0, 0, 0, 0, 0 };
	// x1

	// x - ebx
	// a - eax

	__asm
	{
		mov eax, [values]
		push eax				// ���������� � ���� ������ ������� ������
		mov cx, 5				// ������� ������� ����� 
	start:
		mov ax, 3				// ��� ���������� x = 3 - �� 
		sub ax, cx				// �������� ������� �������� �
		cwde					// ���������� ax �� eax
		mov ebx, eax			// �������� x � ebx
		mov eax, a				// ����� �
		cmp ebx, 1				// ��������� � � ��������
		jl isLess				// ���� � ����� 1, ���������� �� ���� isLess
		jge greatEqual			// ���� � ������� ��� ����� 1, ���������� �� greatEqual
	isLess:
		// 8 + |x|
		cmp ebx, 0
		jl abs_x_is_less
			abs_x_is_less: 
				neg ebx
		mov eax, ebx
		add eax, 8
		jmp result
	greatEqual:
		// 2 * |a|
		mov edx, 2
		cmp eax, 0
		mul edx					// mul ������ ���������� �������� ������� edx �� eax
		jmp result
	result:
		pop ebx					// ���������� � ����� ������ ������
		mov[values + ebx], eax	// �������� ��������� �� �������� �������
		add ebx, 4				// ������� �������� ������
		push ebx				// ���������� � ���� ���� ������
		loop start				// ����� �����
		pop ebx
	}
	for (int i = 0; i < 5; i++)
	{
		std::cout << values[i] << std::endl;
	}
	int secOperand;
	__asm
	{
		mov eax, 0
		push eax				// ���������� � ���� ������ ������� ������
		mov cx, 5				// ������� ������� ����� 
	start1:
		mov ax, 3				// ��� ���������� x = 3 - �� 
		sub ax, cx				// �������� ������� �������� �
		cmp cx, 0
			je end_
		cwde					// ���������� ax �� eax
		mov ebx, eax			// �������� x � ebx
		mov eax, a				// ����� �
		cmp ebx, eax			// ��������� � � a
		je Equals				// ���� � ������� a, ���������� �� ���� Equals
		jne nonEqual			// ���� � �� ������� �, ���������� �� nonEqual
	Equals:
		// 3
		mov eax, 3
		jmp result1
	nonEqual:
		// a + 1
		mov eax, a
		add eax, 1
		jmp result1
	result1:
		/* div <�������>
		������ ���������� ������ ������� EDX : EAX(RDX : RAX) �� �������.
		��������� ������ ���������� � EAX(RAX), � ������ � EDX(RDX).*/
		cdq
		pop ebx
		mov secOperand, eax
		mov eax, [values + ebx]
		div secOperand
		mov[values + ebx], edx
		add ebx, 4				// ������� �������� ������
		push ebx				// ���������� � ���� ���� ������
		loop start1				// ����� �����
		pop ebx
	end_:
		pop ebx
	}
	for (int i = 0; i < 5; i++)
	{
		std::cout << values[i] << std::endl;
	}
	system("pause");
}

int main() 
{
	Task1();
	Option15();
	return 0;
}
