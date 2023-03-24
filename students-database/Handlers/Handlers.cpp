#include <iostream>
#include "../FileInteraction/FileInteraction.h"
#include "../Table/Table.h"
#include "../Tools/Tools.h"
#include "../Models/Student.h"
#include "Handlers.h"
#include "../Models/Student.h"
#include <string>
#include "../ConsoleInteraction/ConsloleInteraction.h"
#include <Windows.h>

void Handlers::DrawStudentsHandler(vector<Student> students) {

	HCRYPTPROV hProv;
	HCRYPTKEY hSessionKey;

	CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);

	CryptGenKey(hProv, CALG_RC4, CRYPT_EXPORTABLE, &hSessionKey);
	
	char str[] = "TestTest";

	DWORD count = strlen(str);

	CryptEncrypt(hSessionKey, 0, true, 0, (BYTE*)str, &count, strlen(str));
	cout << str << endl;

	CryptDecrypt(hSessionKey, 0, true, 0, (BYTE*)str, &count);
	cout << str;
	vector<string> studentColumnNames = { "�������", "���", "��������", "���� ��������", "��� �����������",
	  "���������", "�������", "������", "����� �������� ������", "���" };
	vector<string> examColumnNames = { "����� ��������", "�������� ��������", "������" };
	vector<vector<string>> studentLines = Tools::StructToString(students);
	vector<vector<string>> subjects;

	for (int i = 0; i < studentLines.size(); i++) {
		Table::DrawTable({ studentLines[i] }, studentColumnNames, "������� " + to_string(i + 1));
		Tools::StructToString(students[i], subjects);
		Table::DrawTable(subjects, examColumnNames, "������");
		subjects = {};
	}
}

void Handlers::AddStudentHandler() {

	Student newStudent = {};
	int gender;

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

	do {
		cout << "������� ��� ��������\n0 - �������\n1 - �������\n2 - ���������� ��������\n";

		ConsoleInteraction::GetValue(gender);
		switch (gender) {

		case 0: case 1:
			newStudent.Gender = gender;
			break;
		case 2:
			cout << "������� ����� 2 :)\n";
			break;
		}
	} while (gender > 1 || gender < 0);

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
}

void Handlers::EditStudentHandler() {

	vector<Student> studentsList = FileInteraction::ReadData();

	int studentId = -1;
	int param;
	int sessionParam;
	int sessionNumber;
	int prevSubjectsCount;
	int newSubjectsCount;
	int newSessionsCount;
	int sessionEditNumber = 1;
	int subjectEditNumber = 1;
	int subjectEditParam;
	int gender;
	int prevSessionsCount;

	if (!studentsList.size()) {
		cout << "� ���� ������ ��� ���������\n";
		return;
	}
	cout << "������� ����� ��������, ������ �������� ����� ��������\n";
	for (int i = 0; i < studentsList.size(); i++) {
		cout << i + 1 << " - " << studentsList[i].RecordBook << endl;
	}
	cout << "\n0 - � ������� ����\n";

	do {
		ConsoleInteraction::GetValue(studentId);
		if (!studentId) return;
		if (studentId < 0 || studentId > studentsList.size()) cout << "����� ������� ����� �� 1 �� " << studentsList.size() << endl;
	} while (studentId < 0 || studentId > studentsList.size());

	studentId -= 1;

	cout << "������� ����� ����������� ���������\n" <<
		"1 - �������\n2 - ���\n3 - ��������\n4 - ����� ��������\n5 - ����� ���������\n6 - ��� ��������\n" <<
		"7 - ��� ����������� � ��������\n8 - ��������� (��������)\n9 - �������\n10 - ������\n" << 
		"11 - ����� �������� ������\n12 - ���\n13 - ������ � �������\n\n0 - � ������� ����\n";
	do {
		ConsoleInteraction::GetValue(param);
		if (param < 0 || param > 13) cout << "����� ������ �������� �� 0 �� 13\n";
	} while (param < 0 || param > 13);

	switch (param) {
	case 0:
		break;
	case 1:
		cout << "������� ����� ������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Surname, 1);
		break;
	case 2:
		cout << "������� ����� ��� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Name, 1);
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
		ConsoleInteraction::GetValue(studentsList[studentId].Institute, 1);
		break;
	case 9:
		cout << "������� ������� ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Department, 1);
		break;
	case 10:
		cout << "������� ������ ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].Group, 1);
		break;
	case 11:
		cout << "������� ����� �������� ������ ��������\n";
		ConsoleInteraction::GetValue(studentsList[studentId].RecordBook, 1);
		break;
	case 12:
		do {
			cout << "������� ��� ��������\n0 - �������\n1 - �������\n2 - ���������� ��������\n";

			ConsoleInteraction::GetValue(gender);
			cout << gender << endl;
			switch (gender) {
				cout << gender << endl;
			case 0: case 1:
				studentsList[studentId].Gender = gender;
				cout << studentsList[studentId].Gender << endl << gender << endl;
				break;
			case 2:
				cout << "������� ����� 2 :)\n";
				break;
			} 
		} while (gender > 1 || gender < 0);


		break;
	case 13:
		cout << "�������, ��� ����� �������� � �������\n";
		cout << "1 - �������� ������\n2 - �������� ������\n\n0 - � ������� ����\n";
		do {
			ConsoleInteraction::GetValue(sessionParam);
			if (sessionParam != 1 && sessionParam != 2) cout << "����� ������ ����� �� 0 �� 2\n";
		} while (sessionParam != 1 && sessionParam != 2);

		prevSessionsCount = studentsList[studentId].SessionCount;

		switch (sessionParam)
		{
		case 0:
			break;
		case 1:
			do {
				cout << "������� ���������� ����� ������ (��������: " << 9 - prevSessionsCount << ")\n";
				ConsoleInteraction::GetValue(newSessionsCount);
			} while (prevSessionsCount + newSessionsCount > 9);

			for (int i = 0; i < newSessionsCount; i++) {

				sessionNumber = studentsList[studentId].SessionCount++;
				studentsList[studentId].StudentSession[sessionNumber].Semester = sessionNumber + 1;

				do {
					cout << "������� ���������� ��������� � ������ (�������� 10)\n\n0 - � ������� ����\n";
					ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionNumber].SubjectsCount);
				} while (studentsList[studentId].StudentSession[sessionNumber].SubjectsCount > 10 ||
					studentsList[studentId].StudentSession[sessionNumber].SubjectsCount < 0);

				for (int i = 0; i < studentsList[studentId].StudentSession[sessionNumber].SubjectsCount; i++) {
					cout << "������� �������� " << i + 1 << "-�� �������� � ������\n";
					ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionNumber].Subjects[i].Name, 1);

					cout << "������� ������ �� " << i + 1 << "-� ������� � ������\n";
					ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionNumber].Subjects[i].Mark);
				}
			}
			break;
		case 2:
			if (prevSessionsCount > 1) {
				do {
					cout << "������� ����� ������, ������ ������� ����� �������� (�� 1 �� " << prevSessionsCount << ")\n";
					ConsoleInteraction::GetValue(sessionEditNumber);
			} while (sessionEditNumber > prevSessionsCount || sessionEditNumber <= 0);
			}
			cout << "1 - �������� �������(�)\n2 - �������� ������ �� ��������� ��������\n\n0 - � ������� ����\n";
			do { 
				ConsoleInteraction::GetValue(subjectEditParam);
				if (subjectEditParam != 1 && subjectEditParam != 2) cout << "����� ������ ���� 1, ���� 2\n";
			} while (subjectEditParam != 1 && subjectEditParam != 2);

			prevSubjectsCount = studentsList[studentId].StudentSession[sessionEditNumber - 1].SubjectsCount;

			switch (subjectEditParam)
			{
			case 0:
				break;
			case 1:
				do {
					cout << "������� ���������� ����� ��������� (��������: " << 10 - prevSubjectsCount << ")\n";
					ConsoleInteraction::GetValue(newSubjectsCount);
				} while (prevSubjectsCount + newSubjectsCount > 10);

				for (int i = 0; i < newSubjectsCount; i++) {
					cout << "������� �������� ��������\n";
					ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[prevSubjectsCount + i].Name, 1);
					cout << "������� ������ �� �������\n";
					ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[prevSubjectsCount + i].Mark);
					studentsList[studentId].StudentSession[sessionEditNumber - 1].SubjectsCount++;
				}
				
				break;
			case 2:
				//TODO: draw subjects table
				if (prevSubjectsCount > 1) {
					do {
						cout << "������� ����� ��������, ������ �������� ����� ��������\n";
						ConsoleInteraction::GetValue(subjectEditNumber);
					} while (subjectEditNumber > prevSubjectsCount || subjectEditNumber < 0);
				}
				
				cout << "1 - �������� ��������\n2 - �������� ������\n\n0 - � ������� ����\n";
				ConsoleInteraction::GetValue(subjectEditParam);
				switch (subjectEditParam)
				{
				case 0:
					break;
				case 1:
					cout << "������� �������� �������� ��� ������� " << subjectEditNumber << endl;
					ConsoleInteraction::GetValue(studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[subjectEditNumber - 1].Name, 1);
					break;
				case 2:
					cout << "������� ������ �� ������� " << studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[subjectEditNumber - 1].Name << endl;
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

void Handlers::DeleteStudentHandler() {

	vector<Student> students = FileInteraction::ReadData();

	int studentId;

	cout << "�������� ����� ��������, �������� ����� �������\n";
	for (int i = 0; i < students.size(); i++) {
		cout << i + 1 << " - " << students[i].RecordBook << endl;
	}
	cout << "\n0 - � ������� ����\n";
	do {
		ConsoleInteraction::GetValue(studentId);
		if (!studentId) return;
		if (studentId < 0 || studentId > students.size()) cout << "����� ������� ����� �� 1 �� " << students.size() << endl;
	} while (studentId < 0 || studentId > students.size());
	FileInteraction::DeleteStudent(studentId - 1);
}

void Handlers::SortStudentsHandler() {
	bool gender;

	vector<Student> students = FileInteraction::ReadData();
	vector<Student> goodStudents;
	vector<Student> perfectStudents;

	cout << "������� ��� ��������\n0 - �������\n1 - �������\n";
	do {
		ConsoleInteraction::GetValue(gender);
		if (gender < 0 || gender > 1) cout << "����� ������ ���� 0, ���� 1\n";
	} while (gender < 0 || gender > 1);
	
	Student::SortByGenderAndMarks(gender, students, perfectStudents, goodStudents);
	
	cout << "\n�������� � �������� 3, 4 � 5:\n";
	Handlers::DrawStudentsHandler(goodStudents);

	if (perfectStudents.size()) {
		cout << "\n�������� � �������� 4 � 5:\n";
		Handlers::DrawStudentsHandler(perfectStudents);
		return;
	}

	cout << "��������� � �������� 4 � 5 ���\n";
}