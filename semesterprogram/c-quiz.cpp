#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>

namespace {
	const int s_questionScore = 10;  // Points rewarded for each correct answer.
	const int s_lowPassingGrade = 70;	
	const int s_numQuestions = 10; 
	const char* s_winMessage = "Correct!\n";
	const char* s_loseMessage = "Incorrect, the correct answer was ";
	const char* s_quizFailed = "Sorry, you failed... Better luck next time.";
	const char* s_promptAnswer = "What is your answer?\n";
}

class Question {
public:
	void AskTheQuestions();
	bool Run(std::ifstream& fin);
	bool QuizGame(std::ifstream& fin);
	bool ask();
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

void LoadData(std::istream& is, std::vector<Question>& questions);
void Shuffle(std::vector<Question>& questions);

int main()
{
	Question Game;

	Game.Run(std::ifstream("quiz_data.txt"));

	return 0;
}

void Question::AskTheQuestions()
{
	for (int i = 0; i < s_numQuestions; ++i)
	{
		questions[i].ask();
	}
}

bool Question::Run(std::ifstream& fin)
{
	if (QuizGame(fin)) {
		AskTheQuestions();
		return true;
	}
	else
	{
		return false;
	}

}
bool Question::QuizGame(std::ifstream& fin)
{
	if (fin.is_open())
	{
		LoadData(fin, questions);
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

void LoadData(std::istream& is, std::vector<Question>& questions)
{
	Question q;
	while (is >> q)
		questions.push_back(q);
}

bool Question::ask()
{
	std::cout << "\n";
	std::cout << question_text << "\n";
	std::cout << "a. " << answer_1 << "\n";
	std::cout << "b. " << answer_2 << "\n";
	std::cout << "c. " << answer_3 << "\n";
	std::cout << "d. " << answer_4 << "\n";

	//Ask user for their answer.
	char guess = ' ';
	std::cout << s_promptAnswer;
	std::cin >> guess;

	if (guess == correct_answer) {
		std::cout << s_winMessage;
		return true;
		std::cin.get();
		std::cin.get();
	}
	else
	{
		std::cout << s_loseMessage << correct_answer << ".\n";
		return false;
		std::cin.get();
		std::cin.get();
	}
}

void Shuffle(std::vector<Question>& questions)
{
	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::shuffle(questions.begin(), questions.end(), randomGenerator);
}
