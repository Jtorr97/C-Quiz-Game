//--------------------------------------------------------
//
//c-quiz.cpp
//
//--------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>

namespace {
	int s_totalScore = 0;
}

class Question {
public:
	void AskTheQuestions();
	void PrintResults();
	bool Run(std::ifstream& fin);
	bool InitializeQuizGame(std::ifstream& fin);
	int askQuestion(int num = -1);
	friend std::istream& operator >> (std::istream& is, Question& ques);


private:
	std::vector<Question> questions;
	std::string question_text;
	std::string answer_1;
	std::string answer_2;
	std::string answer_3;
	std::string answer_4;
	char correct_answer;
};

void PrintTxtMsg(std::ifstream txtfile);
void LoadData(std::istream& is, std::vector<Question>& questions);
void Shuffle(std::vector<Question>& questions);
bool AskToPlayAgain();

int main()
{
	Question Quiz;
	
	bool playAgain = false;
	do {
		Quiz.Run(std::ifstream("quiz_data.txt"));
		playAgain = AskToPlayAgain();
	} while (playAgain);

	return 0;
}

bool Question::InitializeQuizGame(std::ifstream& quiz_data)
{
	if (quiz_data.is_open())
	{
		LoadData(quiz_data, questions);
		Shuffle(questions);
		return true;
	}
	else
	{
		std::cout << "Error: File not found!\n";
		return false;
	}
	std::cin.get();
}

void LoadData(std::istream& is, std::vector<Question>& questions)
{
	Question q;
	while (is >> q)
		questions.push_back(q);
}

void Shuffle(std::vector<Question>& questions)
{
	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::shuffle(questions.begin(), questions.end(), randomGenerator);
}

bool Question::Run(std::ifstream& quiz_data)
{
	if (InitializeQuizGame(quiz_data)) {
		PrintTxtMsg(std::ifstream("welcome.txt"));
		AskTheQuestions();
		PrintResults();
		return true;
	}
	else
	{
		return false;
	}

}

void Question::AskTheQuestions()
{
	const int s_numQuestions = 10;
	for (int i = 0; i < s_numQuestions; ++i)
	{
		questions[i].askQuestion(i + 1);
	}
}

void Question::PrintResults()
{
	const int s_failingGrade = 50;
	if (s_totalScore >= s_failingGrade) {
		std::cout << "Your total score is " << s_totalScore << " out of 100!\n";
		PrintTxtMsg(std::ifstream("quiz_passed.txt"));
	}
	else
	{
		std::cout << "Your total score is " << s_totalScore << " out of 100...\n";
		std::cout << "Sorry, you failed the quiz. Better luck next time.\n";
	}
}

std::istream& operator >> (std::istream& is, Question& ques)
{
	std::string line;
	while (std::getline(is, line))
	{
		if (line.size() == 0)
			continue;
		break;
	}
	ques.question_text = line;
	getline(is, ques.answer_1);
	getline(is, ques.answer_2);
	getline(is, ques.answer_3);
	getline(is, ques.answer_4);
	is >> ques.correct_answer;
	return is;
}

int TrackScore()
{
	const int s_questionScore = 10;  // Points rewarded for each correct answer.
	s_totalScore += s_questionScore;
	return s_totalScore;
}

int Question::askQuestion(int num)
{
	std::cout << "\n";
	if (num > 0)
		std::cout << num << ".) ";
	std::cout << question_text << "\n\n";
	std::cout << "a. " << answer_1 << "\n";
	std::cout << "b. " << answer_2 << "\n";
	std::cout << "c. " << answer_3 << "\n";
	std::cout << "d. " << answer_4 << "\n\n";

	//Ask user for their answer.
	char guess = ' ';
	std::cout << "What is your answer?\n";
	std::cin >> guess;

	if (guess == correct_answer) {
		std::cout << "Correct!\n";
		TrackScore();
		std::cin.get();
		std::cin.get();
	}
	else
	{
		std::cout << "Incorrect, the correct answer was " << correct_answer << ".\n";
		std::cin.get();
		std::cin.get();
	}
	return num;
}

bool AskToPlayAgain()
{
	std::cout << "Do you wanna play again? \n";
	std::string Response = " ";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintTxtMsg(std::ifstream txt_art)
{
	std::string line;
	std::ifstream txtfile();
	if (txt_art.is_open())
	{
		while (getline(txt_art, line))
		{
			std::cout << line << '\n';
		}
		txt_art.close();
	}
	else std::cout << "Unable to open file. :(";
}

