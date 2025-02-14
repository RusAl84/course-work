#include <iostream>
#include "../FileInteraction/FileInteraction.h"
#include "../Table/Table.h"
#include "../Tools/Tools.h"
#include "Handlers.h"
#include "../ConsoleInteraction/ConsloleInteraction.h"

#define string List<char>

void Handlers::DrawStudentsHandler(List<Student> students) {

    if (!students.size()) {
        cout << "� ���� ������ ��� ���������\n";
        return;
    }

    List<string > studentColumnNames = {"�������", "���", "��������", "���� ��������", "��� �����������", "���������",
                                        "�������", "������", "����� �������� ������", "���"};
    List<string > examColumnNames = {"����� ��������", "�������� ��������", "������"};

    List<List<string>> studentLines = Tools::StructToString(students);
    List<List<string>> subjects;

    for (int i = 0; i < studentLines.size(); i++) {
        Table::DrawTable({studentLines[i]}, studentColumnNames, "������� " + to_string(i + 1));
        subjects = Tools::StructToString(students[i]);
        Table::DrawTable(subjects, examColumnNames, "������");
    }
}

void Handlers::AddStudentHandler() {
    Student newStudent = {};
    int gender;
    bool alreadyExists;

    cout << "������� ������� ��������\n";
    ConsoleInteraction::GetValue(newStudent.Surname, true);

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
    ConsoleInteraction::GetValue(newStudent.Institute, true);

    cout << "������� ������� ��������\n";
    ConsoleInteraction::GetValue(newStudent.Department);

    cout << "������� ������ ��������\n";
    ConsoleInteraction::GetValue(newStudent.Group);

    do {
        cout << "������� ����� �������� ������ ��������\n";
        ConsoleInteraction::GetValue(newStudent.RecordBook);
        alreadyExists = Tools::FindStudentByRecordBook(newStudent.RecordBook);
        if (alreadyExists) cout << "������� � ����� ������� �������� ������ ��� ����������\n";
    } while (alreadyExists);

    do {
        cout << "������� ��� ��������\n0 - �������\n1 - �������\n2 - ���������� ��������\n";

        ConsoleInteraction::GetValue(gender);
        switch (gender) {
            case 0:
            case 1:
                newStudent.Gender = gender;
                break;
            case 2:
                cout << "������� ����� 2 :)\n";
                break;
        }
    } while (gender > 1 || gender < 0);

    do {
        cout << "������� ���������� ������� ������ (�������� 9)\n";
        ConsoleInteraction::GetValue(newStudent.SessionCount);
    } while (newStudent.SessionCount > 9 || newStudent.SessionCount < 0);

    for (int i = 0; i < newStudent.SessionCount; i++) {
        newStudent.StudentSession[i].Semester = i + 1;
        cout << "������� ���������� ��������� � ������ " << i + 1 << " (�������� 10)\n";
        ConsoleInteraction::GetValue(newStudent.StudentSession[i].SubjectsCount);
        for (int j = 0; j < newStudent.StudentSession[i].SubjectsCount; j++) {
            cout << "������� �������� " << j + 1 << "-�� �������� � " << i + 1 << "-� ������\n";
            ConsoleInteraction::GetValue(newStudent.StudentSession[i].Subjects[j].Name, true);
            cout << "������� ������ �� " << j + 1 << "-� ������� � " << i + 1 << "-� ������\n";
            ConsoleInteraction::GetValue(newStudent.StudentSession[i].Subjects[j].Mark);
        }
    }
    FileInteraction::AddStudent({newStudent});
}

void Handlers::EditStudentHandler() {
    int value;

    List<Student> studentsList = FileInteraction::ReadData();

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
        if (studentId < 0 || studentId > studentsList.size())
            cout << "����� ������� ����� �� 1 �� " << studentsList.size() << endl;
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
            ConsoleInteraction::GetValue(studentsList[studentId].Surname, true);
            break;
        case 2:
            cout << "������� ����� ��� ��������\n";
            ConsoleInteraction::GetValue(studentsList[studentId].Name, true);
            break;
        case 3:
            cout << "������� ����� �������� ��������\n";
            ConsoleInteraction::GetValue(studentsList[studentId].Patronymic, true);
            break;
        case 4:
            cout << "������� ����� �������� ��������\n";
            studentsList[studentId].BirthData.SetDay(ConsoleInteraction::GetValue(value));
            break;
        case 5:
            cout << "������� ����� �������� ��������\n";
            studentsList[studentId].BirthData.SetMonth(ConsoleInteraction::GetValue(value));
            break;
        case 6:
            cout << "������� ��� �������� ��������\n";
            studentsList[studentId].BirthData.SetYear(ConsoleInteraction::GetValue(value));
            break;
        case 7:
            cout << "������� ��� ����������� � �������� ��������\n";
            studentsList[studentId].SetAdmissionYear(ConsoleInteraction::GetValue(value));
            break;
        case 8:
            cout << "������� ��������� ��������\n";
            ConsoleInteraction::GetValue(studentsList[studentId].Institute, true);
            break;
        case 9:
            cout << "������� ������� ��������\n";
            ConsoleInteraction::GetValue(studentsList[studentId].Department, true);
            break;
        case 10:
            cout << "������� ������ ��������\n";
            ConsoleInteraction::GetValue(studentsList[studentId].Group, true);
            break;
        case 11:
            cout << "������� ����� �������� ������ ��������\n";
            ConsoleInteraction::GetValue(studentsList[studentId].RecordBook, true);
            break;
        case 12:
            do {
                cout << "������� ��� ��������\n0 - �������\n1 - �������\n2 - ���������� ��������\n";

                ConsoleInteraction::GetValue(gender);
                cout << gender << endl;
                switch (gender) {
                    case 0:
                    case 1:
                        studentsList[studentId].SetGender(gender);
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

            switch (sessionParam) {
                case 0:
                    break;
                case 1:
                    do {
                        cout << "������� ���������� ����� ������ (��������: " << 9 - prevSessionsCount << ")\n";
                        ConsoleInteraction::GetValue(newSessionsCount);
                    } while (prevSessionsCount + newSessionsCount > 9);

                    for (int i = 0; i < newSessionsCount; i++) {

                        sessionNumber = studentsList[studentId].GetSessionCount() + 1;
                        studentsList[studentId].SetSessionCount(sessionNumber);
                        studentsList[studentId].StudentSession[sessionNumber].SetSemester(sessionNumber + 1);

                        do {
                            cout << "������� ���������� ��������� � ������ (�������� 10)\n\n0 - � ������� ����\n";
                            studentsList[studentId].StudentSession[sessionNumber].SetSubjectsCount(
                                    ConsoleInteraction::GetValue(value));
                        } while (studentsList[studentId].StudentSession[sessionNumber].SubjectsCount > 10 ||
                                 studentsList[studentId].StudentSession[sessionNumber].SubjectsCount < 0);

                        for (int j = 0; j < studentsList[studentId].StudentSession[sessionNumber].SubjectsCount; j++) {
                            cout << "������� �������� " << j + 1 << "-�� �������� � ������\n";
                            ConsoleInteraction::GetValue(
                                    studentsList[studentId].StudentSession[sessionNumber].Subjects[j].Name, true);

                            cout << "������� ������ �� " << j + 1 << "-� ������� � ������\n";
                            do {
                                studentsList[studentId].StudentSession[sessionNumber].Subjects[j].SetMark(
                                        ConsoleInteraction::GetValue(value));
                            } while (studentsList[studentId].StudentSession[sessionNumber].Subjects[j].GetMark());
                        }
                    }
                    break;
                case 2:
                    if (prevSessionsCount > 1) {
                        do {
                            cout << "������� ����� ������, ������ ������� ����� �������� (�� 1 �� " << prevSessionsCount
                                 << ")\n";
                            ConsoleInteraction::GetValue(sessionEditNumber);
                        } while (sessionEditNumber > prevSessionsCount || sessionEditNumber <= 0);
                    }
                    cout
                            << "1 - �������� �������(�)\n2 - �������� ������ �� ��������� ��������\n\n0 - � ������� ����\n";
                    do {
                        ConsoleInteraction::GetValue(subjectEditParam);
                        if (subjectEditParam != 1 && subjectEditParam != 2) cout << "����� ������ ���� 1, ���� 2\n";
                    } while (subjectEditParam != 1 && subjectEditParam != 2);

                    prevSubjectsCount = studentsList[studentId].StudentSession[sessionEditNumber - 1].SubjectsCount;

                    switch (subjectEditParam) {
                        case 0:
                            break;
                        case 1:
                            do {
                                cout << "������� ���������� ����� ��������� (��������: " << 10 - prevSubjectsCount
                                     << ")\n";
                                ConsoleInteraction::GetValue(newSubjectsCount);
                            } while (prevSubjectsCount + newSubjectsCount > 10);

                            for (int i = 0; i < newSubjectsCount; i++) {
                                cout << "������� �������� ��������\n";
                                ConsoleInteraction::GetValue(
                                        studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[
                                                prevSubjectsCount + i].Name, true);
                                cout << "������� ������ �� �������\n";
                                studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[
                                        prevSubjectsCount + i].SetMark(ConsoleInteraction::GetValue(value));
                                studentsList[studentId].StudentSession[sessionEditNumber - 1].SetSubjectsCount(
                                        studentsList[studentId].StudentSession[sessionEditNumber -
                                                                               1].GetSubjectsCount() + 1);
                            }

                            break;
                        case 2:
                            cout << "�������� �������� � " << sessionEditNumber << "-�� ��������:\n";
                            for(int i = 0; i < studentsList[studentId].StudentSession[sessionEditNumber - 1].GetSubjectsCount(); i++) {
                                cout << i + 1 << " - " << studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[i].Name << endl;
                            }
                            if (prevSubjectsCount >= 1) {
                                do {
                                    cout << "������� ����� ��������, ������ �������� ����� ��������\n";
                                    ConsoleInteraction::GetValue(subjectEditNumber);
                                } while (subjectEditNumber > prevSubjectsCount || subjectEditNumber <= 0);
                            }

                            cout << "1 - �������� ��������\n2 - �������� ������\n\n0 - � ������� ����\n";
                            ConsoleInteraction::GetValue(subjectEditParam);
                            switch (subjectEditParam) {
                                case 0:
                                    break;
                                case 1:
                                    cout << "������� �������� �������� ��� ������� " << subjectEditNumber << endl;
                                    ConsoleInteraction::GetValue(
                                            studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[
                                                    subjectEditNumber - 1].Name, true);
                                    break;
                                case 2:
                                    cout << "������� ������ �� ������� "
                                         << studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[
                                                 subjectEditNumber - 1].Name << endl;
                                    studentsList[studentId].StudentSession[sessionEditNumber - 1].Subjects[
                                            subjectEditNumber - 1].SetMark(ConsoleInteraction::GetValue(value));
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

    List<Student> students = FileInteraction::ReadData();

    int studentId;

    cout << "�������� ����� ��������, �������� ����� �������\n";
    for (int i = 0; i < students.size(); i++) {
        cout << i + 1 << " - " << students[i].RecordBook << endl;
    }
    cout << "\n0 - � ������� ����\n";
    do {
        ConsoleInteraction::GetValue(studentId);
        if (!studentId) return;
        if (studentId < 0 || studentId > students.size())
            cout << "����� ������� ����� �� 1 �� " << students.size() << endl;
    } while (studentId < 0 || studentId > students.size());
    FileInteraction::DeleteStudent(studentId - 1);
}

void Handlers::SortStudentsHandler() {
    bool gender;

    List<Student> students = FileInteraction::ReadData();
    List<Student> goodStudents;
    List<Student> perfectStudents;

    cout << "������� ��� ��������\n0 - �������\n1 - �������\n";

    ConsoleInteraction::GetValue(gender);


    Student::SortByGenderAndMarks(gender, students, perfectStudents, goodStudents);

    cout << (goodStudents.size() ? "\n�������� � �������� 3, 4 � 5:\n" : "��������� � �������� 3, 4 � 5 ���\n");
    Handlers::DrawStudentsHandler(goodStudents);

    cout << (perfectStudents.size() ? "\n�������� � �������� 4 � 5:\n" : "��������� � �������� 4 � 5 ���\n");
    Handlers::DrawStudentsHandler(perfectStudents);
}