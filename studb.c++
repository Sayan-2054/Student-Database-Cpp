#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

class Student {
public:
    std::string rollNumber;
    std::string name;
    int age;
    std::string course;

    Student(const std::string& roll, const std::string& n, int a, const std::string& c)
        : rollNumber(roll), name(n), age(a), course(c) {}

    void display() const {
        std::cout << std::setw(10) << rollNumber
                  << std::setw(20) << name
                  << std::setw(5) << age
                  << std::setw(15) << course << std::endl;
    }
};

class StudentDatabase {
private:
    std::vector<Student> students;
    std::string filename;

    void loadFromFile() {
        std::ifstream file(filename);
        if (file.is_open()) {
            students.clear(); // Clear existing data
            std::string roll, name, course;
            int age;
            while (file >> roll >> name >> age >> course) {
                students.emplace_back(roll, name, age, course);
            }
            file.close();
        }
    }

    void saveToFile() {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& student : students) {
                file << student.rollNumber << " "
                     << student.name << " "
                     << student.age << " "
                     << student.course << "\n";
            }
            file.close();
        }
    }

public:
    StudentDatabase(const std::string& file) : filename(file) {
        loadFromFile();
    }

    ~StudentDatabase() {
        saveToFile();
    }

    void addStudent(const Student& student) {
        students.push_back(student);
        saveToFile();
    }

    void displayAllStudents() const {
        std::cout << std::setw(10) << "Roll No."
                  << std::setw(20) << "Name"
                  << std::setw(5) << "Age"
                  << std::setw(15) << "Course" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
        for (const auto& student : students) {
            student.display();
        }
        std::cout << "---------------------------------------------" << std::endl;
    }
};

int main() {
    StudentDatabase studentDB("students.txt");

    char addMore;
    do {
        std::string roll, name, course;
        int age;

        std::cout << "Enter Roll Number: ";
        std::cin >> roll;

        std::cout << "Enter Name: ";
        std::cin.ignore(); 
        std::getline(std::cin, name);

        std::cout << "Enter Age: ";
        std::cin >> age;

        std::cout << "Enter Course: ";
        std::cin.ignore(); 
        std::getline(std::cin, course);

        Student newStudent(roll, name, age, course);
        studentDB.addStudent(newStudent);

        std::cout << "Do you want to add more students? (y/n): ";
        std::cin >> addMore;
    } while (addMore == 'y' || addMore == 'Y');

    std::cout << "\nAll Students:\n";
    studentDB.displayAllStudents();

    return 0;
}

