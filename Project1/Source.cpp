#include<iostream>
struct student {
	string studentName;
	int score;
	char grade;
};
void readStudent()
{
	cout << "Enter Name";
	cin >> student.studentName;
	cout << "Enter Score";
	cin >> student.score; 
}
void assignGrade(int score)
{
	if (score >= 90)
	{
		student.grade = 'A';
	}
	else if((score >= 80 )&&(score< 90))
	{
		student.grade = 'B';
	}
	else if ((score >= 70) && (score< 80))
	{
		student.grade = 'C';
	}
	else if ((score >= 60) && (score< 70))
	{
		student.grade = 'D';
	}
	else
	{
		student.grade = 'F';
	}
}
void print()
{
	cout << student.studentName << ednl;
	cout << Score << __________ << Grade << endl;
	cout << student.score << __________ << student.grade << endl;
}
int main()
{
	readStudent();
	assignGrade(student.score);
	print();

	system("pause");
	return 0;
}