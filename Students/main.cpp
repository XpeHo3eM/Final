// Напишите класс на C++, который реализует простую систему управления базой данных студентов. 
// Каждый студент представлен структурой Student, содержащей следующие поля: 
// id (целочисленный идентификатор), 
// name (строка с именем студента),
// age (целочисленный возраст студента). 

// Ваш класс должен обеспечивать следующие возможности:
// - Добавление нового студента в базу данных. 
// - Удаление студента по идентификатору.
// - Получение информации о студенте по идентификатору. 
// - Используйте умный указатель std::shared_ptr для хранения и управления объектами студентов в контейнере внутри класса 
// (например, std::vector или std::map). 


#include <iostream>
#include <memory>
#include <unordered_map>


enum class Exception {
    STUDENT_IS_NULLPTR,
    STUDENT_NOT_FOUND,
    STUDENT_ID_IS_EXISTS
};


class Student {
public:
    Student() = default;
    Student(size_t id, std::string name, int age) 
    {
        if (id < 0) {
            id = 0;
        }

        if (name.empty()) {
            name = "UNKNOWN";
        }

        if (age <= 0) {
            age = 1;
        }

        id_ = id;
        name_ = name;
        age_ = age;
    }

    size_t getId() {
        return id_;
    }

    std::string getName() {
        return name_;
    }

    int getAge() {
        return age_;
    }


private:
    size_t id_ = 0;
    std::string name_ = "";
    int age_ = 0;
};


class StudentsDB {
public:
    void add(std::shared_ptr<Student> newStudent) {
        if (newStudent == nullptr) {
            throw Exception::STUDENT_IS_NULLPTR;
        }

        auto newStudentId = newStudent.get()->getId();

        if (db.find(newStudentId) != db.end()) {
            throw Exception::STUDENT_ID_IS_EXISTS;
        }

        db[newStudentId] = newStudent;
    }


    void remove(const size_t id) {
        db.erase(id);
    }


    std::shared_ptr<Student> find(size_t id) {
        if (auto it = db.find(id); it != db.end()) {
            return (*it).second;
        }
    }


    void showInfo(size_t id) {
        auto it = db.find(id);

        if (it == db.end()) {
            throw Exception::STUDENT_NOT_FOUND;
        }

        auto student = (*it).second.get();

        std::cout << "ID: " << student->getId() << std::endl;
        std::cout << "Name: " << student->getName() << std::endl;
        std::cout << "Age: " << student->getAge() << std::endl;
        std::cout << std::endl;
    }


private:
    std::unordered_map<size_t, std::shared_ptr<Student>> db;
};



int main() {

}