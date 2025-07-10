#include <iostream>
using namespace std;

int main() {
    const int numQuestions = 4;
    string questions[numQuestions] = {
        "Which of the following is a correct way to declare an integer variable in C++?",
        "What is the output of: cout << 5 + 2 * 3;",
        "Which keyword is used to create a loop that repeats a specific number of times?",
        "Which operator is used to compare two values for equality in C++?"
    };

    string options[numQuestions][4] = {
        {"a) int x;", "b) integer x;", "c) num x;", "d) x: int;"},
        {"a) 21", "b) 11", "c) 17", "d) 25"},
        {"a) if", "b) while", "c) for", "d) switch"},
        {"a) =", "b) ==", "c) !=", "d) =>"}
    };

    char answers[numQuestions] = {'a', 'b', 'c', 'b'};

    int score = 0;
     cout << "Welcome to the C++ Quiz\n";
  cout << "------------------------\n";
  cout << "Answer the following questions:\n";
  cout << "-----------------------------\n";

    for (int i = 0; i < numQuestions; i++) {
        cout << "Question " << i + 1 << ": " << questions[i] << endl;
        for (int j = 0; j < 4; j++) {
            cout << options[i][j] << endl;
        }

        cout << "Enter your answer (a/b/c/d): ";
        char userAnswer;
        cin >> userAnswer;

        if (tolower(userAnswer) == answers[i]) {
            cout << "Correct\n";
            score++;
        } else {
            cout << "Wrong. The correct answer was " << answers[i] << ".\n";
        }

        cout << "-----------------------------\n";
    }

    cout << "Quiz Over! You scored " << score << " out of " << numQuestions << ".\n";

    return 0;
}
