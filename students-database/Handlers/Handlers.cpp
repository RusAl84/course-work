#include <iostream>
#include "../FileInteraction/FileInteraction.h"
#include "../Table/Table.h"
#include "../Tools/Tools.h"
#include "../Models/Student.h"
#include "Handlers.h"
#include <string>
#include "../ConsoleInteraction/ConsloleInteraction.cpp"

void Handlers::AddStudentHandler() {
	Student newStudent = {};

	cout << "������� ������� ��������\n";
	ConsoleInteraction::GetValue(newStudent.Surname, 1);

	cout << "������� ��� ��������\n";
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
	ConsoleInteraction::GetValue(newStudent.Institute, 1);

	cout << "������� ������� ��������\n";
	ConsoleInteraction::GetValue(newStudent.Department);

	cout << "������� ������ ��������\n";
	ConsoleInteraction::GetValue(newStudent.Group);

	cout << "������� ����� �������� ������ ��������\n";
	ConsoleInteraction::GetValue(newStudent.RecordBook);

	cout << "������� ��� �������� (�����, �������� �� 0 - �������, 0 - �������)\n";
	ConsoleInteraction::GetValue(newStudent.Gender);

	cout << "������� ���������� ������� ������ (�������� 9)\n";
	ConsoleInteraction::GetValue(newStudent.SessionCount);

	for (int i = 0; i < newStudent.SessionCount; i++) {
		newStudent.StudentSession[i].Semester = i + 1;
		cout << "������� ���������� ��������� � ������ " << i + 1 << " (�������� 10)\n";
		ConsoleInteraction::GetValue(newStudent.StudentSession[i].SubjectsCount);
		for (int j = 0; j < newStudent.StudentSession[i].SubjectsCount; j++) {
			cout << "������� �������� " << j + 1 << "-�� �������� � " << i + 1 << "-� ������\n";
			ConsoleInteraction::GetValue(newStudent.StudentSession[i].Subjects[j].Name, 1);
			cout << "������� ������ �� " << j + 1 << "-� ������� � " << i + 1 << "-� ������\n";
			ConsoleInteraction::GetValue(newStudent.StudentSession[i].Subjects[j].Mark);
		}
	}
	FileInteraction::AddStudent({ newStudent });
	ConsoleInteraction::GetValue(newStudent.Surname);
}

void Handlers::EditStudentHandler(int studentId, vector<Student> studentsList, int param) {
	vector<Student> students = FileInteraction::ReadData();


	if (!param) return;

	switch (param) {
	case 1:
		cout << "������� ����� ������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Surname, 1);
		break;
	case 2:
		cout << "������� ����� ��� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Name);
		break;
	case 3:
		cout << "������� ����� �������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Patronymic);
		break;
	case 4:
		cout << "������� ����� ����� �������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].BirthData.Day);
		break;
	case 5:
		cout << "������� ����� ����� �������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].BirthData.Month);
		break;
	case 6:
		cout << "������� ����� ��� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].BirthData.Year);
		break;
	case 7:
		cout << "������� ����� ��� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Name);
		break;
	case 8:
		cout << "������� ����� ��� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Name);
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	case 13: // Session
		break;
	}

	FileInteraction::EditStudent(studentsList);
}

