#include <iostream>
#include "ConsloleInteraction.h"
#include "../FileInteraction/FileInteraction.h"
#include "../Table/Table.h"
#include "../Tools/Tools.h"
#include <string>

using namespace std;

void ConsoleInteraction::GetValue(int& value) {
	while (!(cin >> value))
	{
		cin.clear(); 
		cin.ignore(1000, '\n');
		cout << "�������� �������� ���������\n";
	}
}

void ConsoleInteraction::GetValue() {
	
	char value[100];
	while (!(gets_s(value)))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "�������� �������� ���������\n";
	}
}

string ConsoleInteraction::editStudentHandler(int studentId, string value, int param) {
	string message = "";
	switch (param) {
	case 1:
		FileInteraction::EditStudent(studentId, value, param - 1);
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
		ConsoleInteraction::GetValue(command);

		vector<Student> students = FileInteraction::ReadData();
		vector<string> studentColumnNames = {"�������", "���", "��������", "���� ��������", "��� �����������", 
			"���������", "�������", "������", "����� �������� ������", "���"};
		vector<string> examColumnNames = { "����� ��������", "�������� ��������", "������" };
		vector<vector<string>> studentLines = Tools::StructToString(students);
		vector<vector<string>> subjects;
		vector<vector<string>> examRecords;

		Student newStudent = {};

		int sessionsCount;
		int currSubjectsCount;
		char sur[256];
		//gets_s(sur);
		
		switch (command) {
		case 1:
			for (int i = 0; i < studentLines.size(); i++) {
				Table::DrawTable({ studentLines[i]}, studentColumnNames, "������� " + to_string(i + 1));
				Tools::StructToString(students[i].StudentSession, subjects);
				Table::DrawTable(subjects, examColumnNames, "������");
				subjects = {};
			}
			break;
		case 2:
			cout << "Type val\n";
			gets_s(sur);
			strcpy_s(newStudent.Name, sur);
			//cout << "������� ������� ��������\n";

			//ConsoleInteraction::GetValue(sur);
			//strcpy(newStudent.Surname, sur);

			/*cout << "������� ��� ��������\n";
			ConsoleInteraction::GetValue(newStudent.Name);

			cout << "������� �������� ��������\n";
			ConsoleInteraction::GetValue(newStudent.Patronymic);

			cout << "������� ����� �������� ��������\n";
			ConsoleInteraction::GetValue(newStudent.BirthData.Day);

			cout << "������� ����� �������� �������� (�� 1 �� 12)\n";
			ConsoleInteraction::GetValue(newStudent.BirthData.Month);

			cout << "������� ��� �������� ��������\n";
			ConsoleInteraction::GetValue(newStudent.BirthData.Year);

			cout << "������� ��� ����������� � �������� ��������\n";
			ConsoleInteraction::GetValue(newStudent.AdmissionYear);

			cout << "������� ��������� ��������\n";
			ConsoleInteraction::GetValue(newStudent.Institute);

			cout << "������� ������� ��������\n";
			ConsoleInteraction::GetValue(newStudent.Department);

			cout << "������� ������ ��������\n";
			ConsoleInteraction::GetValue(newStudent.Group);

			cout << "������� ����� �������� ������ ��������\n";
			ConsoleInteraction::GetValue(newStudent.RecordBook);

			cout << "������� ��� �������� (�����, �������� �� 0 - �������, 0 - �������)\n";
			ConsoleInteraction::GetValue(newStudent.Gender);*/

			/*cout << "������� ���������� ������� ������ (�������� 9)\n";
			ConsoleInteraction::GetValue(sessionsCount);*/

			/*for (int i = 0; i < sessionsCount; i++) {
				newStudent.StudentSession[i].Semester = i + 1;
				cout << "������� ���������� ��������� � ������ " << i + 1 << " (�������� 10)\n";
				ConsoleInteraction::GetValue(currSubjectsCount);
				for (int j = 0; j < currSubjectsCount; j++) {
					cout << "������� �������� " << j + 1 << "-�� �������� � " << i + 1 << "-� ������\n";
					ConsoleInteraction::GetValue(newStudent.StudentSession[i].Subjects[j].Name);
					cout << "������� ������ �� " << j + 1 << "-� ������� � " << i + 1 << "-� ������\n";
					ConsoleInteraction::GetValue(newStudent.StudentSession[i].Subjects[j].Mark);*/
				//}
			//}
			FileInteraction::AddStudent({ newStudent });

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