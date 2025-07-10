#include <iostream>
using namespace std;

class Question {
private:
  string text;
  string options[4];
  char correctOption;
public:
  Question(string t, string o1, string o2, string o3, string o4, char correct) {
    text = t;
    options[0] = o1;
    options[1] = o2;
    options[2] = o3;
    options[3] = o4;
    correctOption = correct;
  }

  bool ask() {
    cout << text << endl;
    for (int i = 0; i < 4; i++) {
      cout << options[i] << endl;
    }
    cout << "Enter your answer (a/b/c/d): ";
    char userAnswer;
    cin >> userAnswer;

    if (tolower(userAnswer) == correctOption) {
      cout << "Correct\n";
      return true;
    } else {
      cout << "Wrong. The correct answer was " << correctOption << ".\n";
      return false;
    }
  }
};

int main() {
  cout << "Welcome to the C++ Quiz\n";
  cout << "------------------------\n";
  cout << "Answer the following questions:\n";
  cout << "-----------------------------\n";
  const int numQuestions = 4;
  Question quiz[numQuestions] = {
      Question("Which of the following is a correct way to declare an integer "
               "variable in C++?",
               "a) int x;", "b) integer x;", "c) num x;", "d) x: int;", 'a'),

      Question("What is the output of: cout << 5 + 2 * 3;", "a) 21", "b) 11",
               "c) 17", "d) 25", 'b'),

      Question("Which keyword is used to create a loop that repeats a specific "
               "number of times?",
               "a) if", "b) while", "c) for", "d) switch", 'c'),

      Question(
          "Which operator is used to compare two values for equality in C++?",
          "a) =", "b) ==", "c) !=", "d) =>", 'b')};

  int score = 0;
  for (int i = 0; i < 4; i++) {
    if (quiz[i].ask()) {
      score++;
    }
    cout << "-----------------------------\n";
  }
  cout << "Quiz Over! You scored " << score << " out of " << numQuestions
       << ".\n";
  return 0;
}
