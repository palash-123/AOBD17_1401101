// The code crrently predicts for the first 10 professions in the list in order to easily test the code.

#include <vector>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#define NO_OF_FILES 10 //Currently number of files has been set to 10 so one can easily test the code 
#define TEST_DATA_SIZE 5

using namespace std;

void getskills(vector<string>& files, vector<vector<string>>& skills, string& root_dir);
void getTestData(vector<vector<string>>& test, string& testdata);
void suggestSkills(vector<string>& candidate, string& goal, vector<vector<string>>& skills, vector<string>& files);

int main()
{
	vector<string> files(39);
	string root_dir = "skills/";
	files[0] = "Automation Test Engineer.txt";
	files[1] = "Computer Systems Manager.txt";
	files[2] = "Customer Support Administrator.txt";
	files[3] = "Customer Support Specialist.txt";
	files[4] = "Database Administrator.txt";
	files[5] = "Data Center Support Specialist.txt";
	files[6] = "Data Quality Manager.txt";
	files[7] = "Desktop Support Manager.txt";
	files[8] = "Desktop Support Specialist.txt";
	files[9] = "Front End Developer.txt";
	//we can add more files here after cleaning the data using the data cleaning code
	//
	//
	//
	vector<vector<string>> skills(39);
	
	//form skill clusters according to each career path
	getskills(files, skills, root_dir);
	
	//load test data into test vector
	string testdata = "test/testdata.txt";
	vector<vector<string>> test(TEST_DATA_SIZE);
	getTestData(test, testdata);
	
	//get user career goal and recommend skills based on that
	srand(time(NULL));
	for (int i = 0; i < TEST_DATA_SIZE; i++)
	{
		string goal;
		cout << "\nUser " << i + 1 << " enter career goal : ";
		getline(cin, goal);
		suggestSkills(test[i], goal, skills, files);
		cout << "\n";
	}
	
    return 0;
}

void suggestSkills(vector<string>& candidate, string& goal, vector<vector<string>>& skills, vector<string>& files)
{
	int count = 5;
	string file_name = goal + ".txt";
	for (int i = 0; i < NO_OF_FILES; i++)
	{
		if (files[i] == file_name)
		{
			while (count > 0)
			{
				int check = 1, j = rand() % (skills[i].size());
				for (int k = 0; k < candidate.size(); k++)
				{
					if (!skills[i][j].compare(candidate[k]))
					{
						check = 0;
					}
				}
				if (check == 1)
				{
					cout << skills[i][j] << ", ";
					count--;
				}
			}
			break;
		}
	}
}


void getTestData(vector<vector<string>>& test, string& testdata)
{
	ifstream testfile(testdata);
    string temp, line;
	if (testfile.is_open())
	{
        int j = 0;
        while (getline(testfile, line))
        {
			for (int i = 0; i <= line.length(); i++)
			{
		        if (line[i] == ',' || i == line.length())
	            {
                    test[j].push_back(temp);
					temp.clear();
					if (line[i + 1] == ' ')
					{
				        i++;
			        }
		            continue;
	            }
                temp.push_back(line[i]);
			}
		    j++;
		}
	    testfile.close();
    }
    else
    {
		cout << "Unable to open file " << testdata << "\n";
	}
}

void getskills(vector<string>& files, vector<vector<string>>& skills, string& root_dir)
{
	ifstream skillsfile;
	for (int j = 0; j < NO_OF_FILES; j++)
	{
		skillsfile.open(root_dir + files[j]);
		string temp, line;
		if (skillsfile.is_open())
		{
			while (getline(skillsfile, line))
			{
				for (int i = 0; i <= line.length(); i++)
				{
					if (line[i] == ',' || i == line.length())
					{
						skills[j].push_back(temp);
						temp.clear();
						if (line[i + 1] == ' ')
						{
							i++;
						}
						continue;
					}
					temp.push_back(line[i]);
				}
			}
			skillsfile.close();
		}
		else
		{
			cout << "Unable to open file " << files[j] << "\n";
		}
	}
}

