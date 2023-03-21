#include <iostream>
#include "../FileInteraction/FileInteraction.h"
#include "../Table/Table.h"
#include "../Tools/Tools.h"
#include "../Models/Student.h"
#include "Handlers.h"
#include <string>
#include "../ConsoleInteraction/ConsloleInteraction.h"

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

	int sessionParam;
	int sessionNumber;
	int prevSubjectsCount;
	int sessionEditNumber;
	int subjectEditNumber;
	int subjectEditParam;
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
		ConsoleInteraction::GetValue(studentsList[studentId].Patronymic, 1);
		break;
	case 4:
		cout << "������� ����� �������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].BirthData.Day);
		break;
	case 5:
		cout << "������� ����� �������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].BirthData.Month);
		break;
	case 6:
		cout << "������� ��� �������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].BirthData.Year);
		break;
	case 7:
		cout << "������� ��� ����������� � �������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].AdmissionYear);
		break;
	case 8:
		cout << "������� ��������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Institute);
		break;
	case 9:
		cout << "������� ������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Department);
		break;
	case 10:
		cout << "������� ������ ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Group);
		break;
	case 11:
		cout << "������� ����� �������� ������ ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].RecordBook);
		break;
	case 12:
		cout << "������� ��� �������� (1 - �������, 0 - �������)\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Institute);
		break;
	case 13:
		cout << "�������, ��� ����� �������� � �������\n";
		cout << "1 - �������� ������\n2 - �������� ������\n";
		do {
			ConsoleInteraction::GetValue(sessionParam);
			if (sessionParam != 1 && sessionParam != 2) cout << "����� ������ ���� 1, ���� 2\n";
		} while (sessionParam != 1 && sessionParam != 2);
		switch (sessionParam)
		{
		case 1:
			if (studentsList[studentId].SessionCount == 9) {
				cout << "��� ������� ������������ ���������� ������ (9)\n";
				break;
			}
			sessionNumber = studentsList[studentId].SessionCount++;
			studentsList[studentId].StudentSession[sessionNumber].Semester = sessionNumber + 1;
			cout << "������� ���������� ��������� � ������ (�������� 10)\n";
			ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionNumber].SubjectsCount);
			for (int i = 0; i < studentsList[studentId].StudentSession[sessionNumber].SubjectsCount; i++) {
				cout << "������� �������� " << i + 1 << "-�� �������� � ������\n";
				ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionNumber].Subjects[i].Name, 1);
				cout << "������� ������ �� " << i + 1 << "-� ������� � ������\n";
				ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionNumber].Subjects[i].Mark);
			}
			break;
		case 2:
			//TODO: draw sessions table
			cout << "������� ����� ������, ������ ������� ����� ��������\n";
			ConsoleInteraction::GetValue(sessionEditNumber);
			cout << "1 - �������� �������\n2 - �������� ������ �� ��������� ��������\n";
			do { 
				ConsoleInteraction::GetValue(subjectEditNumber);
				if (subjectEditNumber != 1 && subjectEditNumber != 2) cout << "����� ������ ���� 1, ���� 2\n";
			} while (subjectEditNumber != 1 && subjectEditNumber != 2);

			prevSubjectsCount = studentsList[studentId].StudentSession[sessionEditNumber - 1].SubjectsCount;

			switch (subjectEditNumber)
			{
			case 1:
				if (prevSubjectsCount == 10) {
					cout << "��� ������� ������������ ���������� ��������� � ������ (10)\n";
					break;
				}
				cout << "������� �������� ��������\n";
				ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[prevSubjectsCount].Name, 1);
				cout << "������� ������ �� �������\n";
				ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[prevSubjectsCount].Mark);
				studentsList[studentId].StudentSession[sessionEditNumber - 1].SubjectsCount++;
				break;
			case 2:
				//TODO: draw subjects table
				cout << "������� ����� ��������, ������ � ������� ����� ��������\n";
				ConsoleInteraction::GetValue(subjectEditNumber);
				cout << "1 - �������� ��������\n2 - �������� ������\n";
				ConsoleInteraction::GetValue(subjectEditParam);
				switch (subjectEditParam)
				{
				case 1:
					cout << "������� �������� �������� ��� ������� " << subjectEditNumber << endl;
					ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[subjectEditNumber - 1].Name, 1);
					break;
				case 2:
					cout << "������� ������ �� ������� " << studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[subjectEditNumber - 1].Name;
					ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[subjectEditNumber - 1].Mark);
					break;
				}
				break;
			}
			break;
		}
		break;
	}

	FileInteraction::EditStudent(studentsList);
}

