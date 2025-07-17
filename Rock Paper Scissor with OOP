#include <cstdlib>
#include <iostream>
using namespace std;

class Game {
private:
  int playerScore;
  int computerScore;
  int rounds;

  string getComputerChoice() {
    string choices[] = {"rock", "paper", "scissors"};
    int index = rand() % 3;
    return choices[index];
  }

  string convertCharToChoice(char c) {
    c = tolower(c);
    if (c == 'r')
      return "rock";
    if (c == 'p')
      return "paper";
    if (c == 's')
      return "scissors";
    return "invalid";
  }

  string determineWinner(string player, string computer) {
    if (player == computer)
      return "tie";
    if ((player == "rock" && computer == "scissors") ||
        (player == "paper" && computer == "rock") ||
        (player == "scissors" && computer == "paper"))
      return "player";
    return "computer";
  }

  void printRoundResult(string winner) {
    if (winner == "tie") {
      cout << "It's a tie!" << endl;
    } else if (winner == "player") {
      playerScore++;
      cout << "You win this round!" << endl;
    } else {
      computerScore++;
      cout << "Computer wins this round!" << endl;
    }
  }

public:
  Game() {
    playerScore = 0;
    computerScore = 0;
    rounds = 0;
  }

  void start() {
    cout << "How many rounds do you want to play? ";
    cin >> rounds;

    for (int i = 1; i <= rounds; ++i) {
      cout << "\n--- Round " << i << " ---\n";
      cout << "Enter your choice (r = rock, p = paper, s = scissors): ";

      char input;
      cin >> input;
      string playerChoice = convertCharToChoice(input);

      while (playerChoice == "invalid") {
        cout << "Invalid input. Enter (r, p, or s): ";
        cin >> input;
        playerChoice = convertCharToChoice(input);
      }

      string computerChoice = getComputerChoice();
      cout << "Computer chose: " << computerChoice << endl;

      string winner = determineWinner(playerChoice, computerChoice);
      printRoundResult(winner);

      cout << "Score => You: " << playerScore
           << " | Computer: " << computerScore << endl;
    }

    showFinalResult();
  }

  void showFinalResult() {
    cout << "\n--- Game Over ---\n";
    cout << "Final Score - You: " << playerScore
         << " | Computer: " << computerScore << endl;

    if (playerScore > computerScore)
      cout << "You are the overall winner\n"
    else if (playerScore < computerScore)
      cout << "Computer wins overall. Better luck next time\n"
    else
      cout << " It's a tie overall.\n"
  }
};

int main() {
  srand(time(0));
  Game rockPaperScissors;
  rockPaperScissors.start();
  return 0;
}
