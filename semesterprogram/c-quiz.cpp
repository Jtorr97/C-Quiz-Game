// c-quiz.cpp : This is a program for a quiz game which assess's the user's knowledge of C++.
// Questions are from JE Programming Logic and Design 8th edition, and http://www.cprogramming.com/quiz/?sb=14px
// This program will utilize skills learned in the Fall 2016 Semester in COSC 1315 and outside of class.
// Written by: Joshua Torres.
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
	int askQuestion(int num = -1);
	friend std::istream& operator >> (std::istream& is, Question& ques);

private:
	std::string question_text;
	std::string answer_1;
	std::string answer_2;
	std::string answer_3;
	std::string answer_4;
	char correct_answer;
};

void InitializeStrings(std::ifstream myfile);
void QuizGame(std::ifstream fin);
void load(std::istream& is, std::vector<Question>& questions);
void Shuffle(std::vector<Question>& questions);

int main()
{
	InitializeStrings(std::ifstream ("welcome.txt"));
	QuizGame(std::ifstream ("quiz_data.txt")); 

	return 0;
}

void InitializeStrings(std::ifstream myfile)
{
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << line << '\n';
		}
		myfile.close();
		std::cin.get();
	}
	else
	{
		std::cout << "Error: File not found!\n";
	}
}

void QuizGame(std::ifstream fin)
{
	if (fin.is_open())
	{
		std::vector<Question> questions;
		load(fin, questions);
		Shuffle(questions);

		int total = 0; //Total score.

		for (size_t i = 0; i < s_numQuestions; ++i)
		{
			total += questions[i].askQuestion(i + 1);
		}

		if (total >= s_lowPassingGrade) {
			std::cout << "\n\n";
			std::cout << "You scored " << total << " out of 100!\n";
			InitializeStrings(std::ifstream("quiz_passed.txt"));
		}
		else
		{
			std::cout << "\n\n";
			std::cout << "You scored " << total << " out of 100...\n";
			std::cout << s_quizFailed;
		}
	}
	else
	{
		std::cout << "Error: File not found!\n";
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

void load(std::istream& is, std::vector<Question>& questions)
{
	Question q;
	while (is >> q)
		questions.push_back(q);
}

int Question::askQuestion(int num)
{
	int score = 0;
	std::cout << "\n";
	if (num > 0)
		std::cout << num << ".) ";
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
		score = s_questionScore;
		std::cin.get();
		std::cin.get();
	}
	else
	{
		std::cout << s_loseMessage << correct_answer << ".\n";
		std::cin.get();
		std::cin.get();
	}
	return score;
}

void Shuffle(std::vector<Question>& questions)
{
	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::shuffle(questions.begin(), questions.end(), randomGenerator);
}
