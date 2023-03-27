#include <string>
#include <iostream>

using namespace std;

struct ConsoleInteraction {

	static void Start();

	template<typename T>
	static void GetValue(T& value) {
		while (!(cin >> value) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
;			cout << "�������� �������� ���������\n";
		}
	}

    static void GetValue(char value[], bool afterInt = false) {
        char inputValue[100];

        if (afterInt) {
            getchar();
        }

        while (!gets_s(inputValue, 100)) {
            cout << "�������� ��������� ��������\n";
        }

        strcpy(value, inputValue);
    }

};