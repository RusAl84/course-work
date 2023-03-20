#include <iostream>
#include "ConsloleInteraction.h"
#include "../FileInteraction/FileInteraction.h"
#include "../Table/Table.h"
#include "../Tools/Tools.h"
#include <string>
#include "../Handlers/Handlers.h"

using namespace std;

void ConsoleInteraction::GetValue(char value[], bool afterInt) {
	char inputValue[100];
	if (afterInt) { 
		getchar();
		strcpy_s(inputValue, "q");
	}
	
	while (!gets_s(inputValue)) {
		cout << "�������� ��������� ��������\n";
	}

	strcpy(value, inputValue);
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
        vector<string> studentColumnNames = { "�������", "���", "��������", "���� ��������", "��� �����������",
          "���������", "�������", "������", "����� �������� ������", "���" };
        vector<string> examColumnNames = { "����� ��������", "�������� ��������", "������" };
        vector<vector<string>> studentLines = Tools::StructToString(students);
        vector<vector<string>> subjects;
        vector<vector<string>> examRecords;

        Student newStudent = {};

        switch (command) {
        case 1:
            for (int i = 0; i < studentLines.size(); i++) {
                Table::DrawTable({ studentLines[i] }, studentColumnNames, "������� " + to_string(i + 1));
                Tools::StructToString(students[i].StudentSession, subjects);
                Table::DrawTable(subjects, examColumnNames, "������");
                subjects = {};
            }
            break;
        case 2:
            Handlers::AddStudentHandler();
            break;
        case 3:
            if (!students.size()) {
                cout << "� ���� ������ ��� ���������\n";
                break;
            }
            cout << "������� ����� �������� ������ ��������\n";
            do {
                //ConsoleInteraction::GetValue(recordBook, 1);
                cin >> recordBook;
                studentId = Tools::FindStudentByRecordBook(recordBook);
                if (!studentId) cout << "�������� � ����� ������� �������� ������ �� �������\n";
            } while (!studentId);
            cout << studentId - 1;
            cout << "������� ����� ����������� ���������\n" <<
                "1 - �������\n2 - ���\n3 - ��������\n4 - ����� ��������\n5 - ����� ���������\n6 - ��� ��������\n" <<
                "7 - ��� ����������� � ��������\n8 - ��������� (��������)\n9 - �������\n10 - ������\n11 - ����� �������� ������\n12 - ���\n13 - ������ � �������\n";
            do { ConsoleInteraction::GetValue(param); } while (param < 0 || param > 13);
            Handlers::EditStudentHandler(studentId - 1, students, param);
            studentId = -1;

            break;
        case 4:
            cout << "�������� ����� ��������, �������� ����� �������\n";
            for (int i = 0; i < students.size(); i++) {
                cout << i + 1 << " - " << students[i].RecordBook << endl;
            }

            do { ConsoleInteraction::GetValue(param); } while (param < 0 || param > students.size());
            FileInteraction::DeleteStudent(param - 1);
            break;
        }
	}
}