#include <iostream>
#include "ConsloleInteraction.h"
#include "../FileInteraction/FileInteraction.h"
#include "../Table/Table.h"
#include "../Tools/Tools.h"
#include <string>

using namespace std;

int ConsoleInteraction::GetValue() {
	int value;
	while (!(cin >> value))
	{
		cin.clear(); 
		cin.ignore(1000, '\n');
		cout << "�������� �������� ���������\n";
	}
	return value;
}

string ConsoleInteraction::editStudentHandler(int studentId, string value, int param) {
	string message = "";
	switch (param) {
	case 1:
		cout << "hui";
		FileInteraction::EditStudent(studentId, value, param - 1);
		cout << "Abobaaaaaaaaaaa";
		break;
	case (3, 4, 5):
		break;
	case 6:
		break;
	case 11:
		break;
	case 12:
		break;
	case 13: // Session
		break;
	default:
		return message;
	}
}

void ConsoleInteraction::Start() {
	int command;
	int param;
	int studentId = -1;
	char recordBook[10];
	string value;
	string message;
	while (true) {
		cout << "��������� �������:\n1 - �������� ������ ���������\n2 - �������� ������ ��������\n" <<
			"3 - ������������� ��������\n4 - ������� ��������\n";
		command = ConsoleInteraction::GetValue();

		vector<Student> students = FileInteraction::ReadData();
		vector<string> studentColumnNames = {"�������", "���", "��������", "���� ��������", "��� �����������", 
			"���������", "�������", "������", "����� �������� ������", "���"};
		vector<vector<string>> studentLines = Tools::StructToString(students);
		string studentTitle = "�������";
		switch (command) {
		case 1:
			for (auto line : studentLines) {
				Table::DrawTable({ line }, studentColumnNames, studentTitle);
			}
			break;
		case 2:
			break;
		case 3:
			//while (studentId < 0) {
			//	cout << "������� ����� �������� ������ ��������\n";
			//	cin >> recordBook;
			//	studentId = FileInteraction::FindStudentByRecordBook(recordBook) - 1;
			//};
			//cout << "������� ����� ����������� ���������\n" <<
			//	"1 - �������\n2 - ���\n3 - ��������\n4 - ����� ��������\n5 - ����� ���������\n6 - ��� ��������\n" <<
			//	"7 - ��� ����������� � ��������\n8 - ��������� (��������)\n9 - �������\n10 - ������\n11 - ����� �������� ������\n12 - ���\n";
			//
			//param = ConsoleInteraction::GetValue();
			//cout << "������� �������� ��� ���������\n";
			//cin >> value;
			//cout << studentId << endl << value << endl << param << endl;
			//message = ConsoleInteraction::editStudentHandler(studentId, value, param);
			//if (message.length()) {
			//	// �����������, �������� ��� ���
			//	cout << message;
			//}
			//cout << "������ ������� ��������\n";
			break;
		case 4:
			break;
		}
	}
}