#include <iostream>
void Task1()
{
	int a, b, c, d, x;
	int values[5] = { 0, 0, 0, 0, 0 }; // масив для збереження у(х)

	a = -6; b = 4; c = 8; d = 2;
	__asm {
		mov eax, [values]
		push eax // заштовхуємо у стек адресу початку масиву
		mov cx, 5 // кількість проходів циклу 
	start: // початок циклу
		mov ax, 3 // для обчислення x = 3 - сх 
		sub ax, cx // отримуємо поточне значення х
		cwde // розширюємо ax до eax
		mov ebx, eax // записуємо x в ebx
		mov eax, a // стала а
		cmp ebx, 1 // порівнюємо х з одиницею
		jl less_ // якщо х менше 1, переходимо до мітки less
		je equals // якщо х дорівнює 1, переходимо до equals

		imul eax // a^2
		sub eax, ebx // a^2-x
		cdq // розширюємо a^2-x до четвірного слова
		mov ebx, c // стала c
		idiv ebx // (a^2-x)/c
		jmp result // переходимо до мітки result
	less_:
		mov edx, 2
		imul edx // a*2
		imul ebx // a*2*x
		add eax, 5 // a*2*x+5
		jmp result // переходимо до мітки result
	equals:
		mov ebx, b // стала b
		sub eax, ebx // a-b
		cdq // розширюємо a-b до четвірного слова
		mov ebx, d // стала d
		idiv ebx // (a-b)/d
		jmp result // переходимо до мітки result
	result:
		pop ebx // виштовхуємо зі стеку адресу масиву
		mov[values + ebx], eax // записуємо результат за поточною адресою
		add ebx, 4 // зсуваємо вказівник масиву
		push ebx // заштовхуємо в стек нову адресу
		loop start // кінець циклу
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
		push eax				// заштовхуємо у стек адресу початку масиву
		mov cx, 5				// кількість проходів циклу 
	start:
		mov ax, 3				// для обчислення x = 3 - сх 
		sub ax, cx				// отримуємо поточне значення х
		cwde					// розширюємо ax до eax
		mov ebx, eax			// записуємо x в ebx
		mov eax, a				// стала а
		cmp ebx, 1				// порівнюємо х з одиницею
		jl isLess				// якщо х менше 1, переходимо до мітки isLess
		jge greatEqual			// якщо х дорівнює або більше 1, переходимо до greatEqual
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
		mul edx					// mul виконує беззнакове множення регістра edx на eax
		jmp result
	result:
		pop ebx					// виштовхуємо зі стеку адресу масиву
		mov[values + ebx], eax	// записуємо результат за поточною адресою
		add ebx, 4				// зсуваємо вказівник масиву
		push ebx				// заштовхуємо в стек нову адресу
		loop start				// кінець циклу
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
		push eax				// заштовхуємо у стек адресу початку масиву
		mov cx, 5				// кількість проходів циклу 
	start1:
		mov ax, 3				// для обчислення x = 3 - сх 
		sub ax, cx				// отримуємо поточне значення х
		cmp cx, 0
			je end_
		cwde					// розширюємо ax до eax
		mov ebx, eax			// записуємо x в ebx
		mov eax, a				// стала а
		cmp ebx, eax			// порівнюємо х з a
		je Equals				// якщо х дорівнює a, переходимо до мітки Equals
		jne nonEqual			// якщо х не дорівнює а, переходимо до nonEqual
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
		/* div <операнд>
		Виконує беззнакове ділення регістрів EDX : EAX(RDX : RAX) на операнд.
		Результат ділення зберігається в EAX(RAX), а остача в EDX(RDX).*/
		cdq
		pop ebx
		mov secOperand, eax
		mov eax, [values + ebx]
		div secOperand
		mov[values + ebx], edx
		add ebx, 4				// зсуваємо вказівник масиву
		push ebx				// заштовхуємо в стек нову адресу
		loop start1				// кінець циклу
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
