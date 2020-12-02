#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Student {
  string name;
  double grade_point_average;
  Student(string _name, double point)
      : name(_name), grade_point_average(point){};
};

const static function<bool(const Student&, const Student&)> CompGPA =
    [](const Student& a, const Student& b) {
      if (a.grade_point_average != b.grade_point_average) {
        return a.grade_point_average > b.grade_point_average;
      }
      return a.name > b.name;
    };

bool SearchStudent(
    const vector<Student>& students, const Student& target,
    const function<bool(const Student&, const Student&)>& comp_GPA) {
  return binary_search(students.begin(), students.end(), target, comp_GPA);
}

int main() {
  vector<Student> students = {Student("A", 9), Student("C", 8), Student("B", 8),
                              Student("D", 5)};
  Student studentA = Student("B", 8);
  cout << std::boolalpha << SearchStudent(students, studentA, CompGPA);
  return 0;
}