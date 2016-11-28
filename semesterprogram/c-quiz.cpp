// c-quiz.cpp : This is a program for a quiz game which assess's the user's knowledge of C++.
// Questions are from JE Programming Logic and Design 8th edition, and http://www.cprogramming.com/quiz/?sb=14px
// This program will utilize skills learned in the Fall 2016 Semester in COSC 1315 and outside of class.
// Written by: Joshua Torres

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace {
	const int s_questionScore = 4;  // Points rewarded for each correct answer.
	const int s_failingGrade = 69;
}

class Question {
public:
	int askQuestion(int num = -1);
	friend std::istream& operator >> (std::istream& is, Question& ques);

private:
	std::string Question_Text;
	std::string answer_1;
	std::string answer_2;
	std::string answer_3;
	std::string answer_4;
	char correct_answer;
};

void load(std::istream& is, std::vector<Question>& questions);
void load_sstream(std::istringstream & ss);

int main()
{
	/*Program Title designed with an ASCII art generator.
	Link: http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20 */
	std::cout << R"(
 _    _      _                            _          _   _            _____              _____       _     
| |  | |    | |                          | |        | | | |          /  __ \ _     _    |  _  |     (_)    
| |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___   | |_| |__   ___  | /  \/| |_ _| |_  | | | |_   _ _ ____
| |/\| |/ _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \  | __| '_ \ / _ \ | |  |_   _|_   _| | | | | | | | |_  /
\  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | |_| | | |  __/ | \__/\|_|   |_|   \ \/' / |_| | |/ / 
 \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/   \__|_| |_|\___|  \____/             \_/\_\\__,_|_/___|

----------------------------------------------By: Joshua Torres---------------------------------------------
    )" << "\n";

	std::cout << "Press enter to start...\n";
	std::cin.get();

	std::ifstream fin("quiz_data.txt"); //Load questions from .txt file

	std::vector<Question> questions;
	load(fin, questions);

	std::cout << "Number of questions = " << questions.size() << '\n';

	int total = 0; //Total score.

	for (size_t i = 0; i<questions.size(); ++i)
	{
		total += questions[i].askQuestion(i + 1);
		std::cout << "Total score = " << total << '\n';
	}

	// Pass or fail quiz message. 
	if (total > s_failingGrade) {
		std::cout << R"(

__  __               ____                           ____
\ \/ /___  __  __   / __ \____ ______________  ____/ / /
 \  / __ \/ / / /  / /_/ / __ `/ ___/ ___/ _ \/ __  / / 
 / / /_/ / /_/ /  / ____/ /_/ (__  |__  )  __/ /_/ /_/  
/_/\____/\__,_/  /_/    \__,_/____/____/\___/\__,_(_)   

    )" << "\n";
		std::cout << "\n";
		std::cin.get();
		std::cin.ignore();
		return 0;
	}
	else
	{
		std::cout << "You failed... Sorry, better luck next time.\n\n";
	}
	std::cin.get();
	std::cin.ignore();
	return 0;
}

std::istream& operator >> (std::istream& is, Question& ques)
{
	std::string line;
	while (getline(is, line))
	{
		if (line.size() == 0)
			continue;
		break;
	}
	ques.Question_Text = line;
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
		std::cout << num << ". ";
	std::cout << Question_Text << "\n";
	std::cout << "a. " << answer_1 << "\n";
	std::cout << "b. " << answer_2 << "\n";
	std::cout << "c. " << answer_3 << "\n";
	std::cout << "d. " << answer_4 << "\n\n";

	char guess;
	//Ask user for their answer.
	std::cout << "What is your answer?\n";
	std::cin >> guess;

	if (guess == correct_answer) {
		std::cout << "Correct!\n\n";
		score = s_questionScore;
		std::cout << "Press enter to continue.\n";
		std::cin.get();
		std::cin.ignore();
	}
	else
	{
		std::cout << "Sorry, you're wrong... " << "The correct answer is " << correct_answer << ".\n\n";
		std::cout << "Press enter to continue." << "\n";
		std::cin.get();
		std::cin.ignore();
	}

	return score;

}


