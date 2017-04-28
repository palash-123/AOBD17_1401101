// The code currently predicts for the first 10 professions in the list in order to easily test the code.

#include <vector>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#define NO_OF_FILES 10  //Currently only 10 files are present so one can easily check as greater number of files increase the time complexity
#define TEST_DATA_SIZE 5

using namespace std;

void getskills(vector<string>& files, vector<vector<string>>& skills, string& root_dir);
void getTestData(vector<vector<string>>& test, string& testdata);
bool sortDecreasing(int i, int j);
string suggestCareer(vector<string>& candidate, vector<vector<string>>& skills, vector<string>& files);

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
	//we can add more files here after further cleaning the data using the data cleaning code
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
	
	//suggest career paths for each candidate in test data
	for (int i = 0; i < TEST_DATA_SIZE; i++)
	{
		string career = suggestCareer(test[i], skills, files);
		for (int j = 0; j < 4; j++)
		{
			career.pop_back();
		}
		cout << career << "\n";
	}
	
    return 0;
}

bool sortDecreasing(int i, int j)
{
	return i > j;
}

string suggestCareer(vector<string>& candidate, vector<vector<string>>& skills, vector<string>& files)
{
	vector<int> support(39,0);
	for (int i = 0; i < candidate.size(); i++)
	{
		for (int j = 0; j < NO_OF_FILES; j++)
		{
			for (int k = 0; k < skills[j].size(); k++)
			{
				if (!candidate[i].compare(skills[j][k]))
				{
					support[j]++;
				}
			}
		}
	}
	vector<int> support_copy = support;
	sort(support_copy.begin(), support_copy.end(), sortDecreasing);
	for (int i = 0; i < NO_OF_FILES; i++)
	{
		if (support[i] == support_copy[0])
		{
			return files[i];
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

