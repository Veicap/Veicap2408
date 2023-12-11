#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "printTable.h"
const std::string FILE_NAME = "group.txt";

struct ProjectSubmission {
    int projectNumber;
    std::string submissionDate;
    std::string statement;
};
struct Group {
    int groupNumber;
    std::string nameOfGroup;
    std::vector<std::string> nameOfStudentList;
    std::vector<ProjectSubmission*> submissions;
};
struct Project {
    int projectNumber;
    std::string shortDescriptionOfProject;
    int dayOfDeadLine;
    int monthOfDeadLine;
    int yearOfDeadLine;
    std::string deadline;
};
struct HandleData {
    // Option 1:
    std::vector<Group*> listOfGroup;
   
   // Read file text group.txt
    void ReadFile() {
        std::ifstream groupFile(FILE_NAME);
        if (!groupFile.is_open()) {
            std::cerr << "Error opening file: " << FILE_NAME << std::endl;
            return;
        }

        std::string groupInformation;
        Group* group = new Group();
        // Read file
        while (std::getline(groupFile, groupInformation)) {
            if (groupInformation.find("Group") != std::string::npos) {
                if (group->groupNumber != NULL) {
                    listOfGroup.push_back(group);
                }
                group = new Group(); // Create new group;
               
                int pos = groupInformation.find(" ") + 1;
                int groupNumber = std::stoi(groupInformation.erase(0, pos));
                group->groupNumber = groupNumber;
            }
            else {
                group->nameOfStudentList.push_back(groupInformation);
            }
        }
        if (group->groupNumber != NULL) {
            listOfGroup.push_back(group);
        }

        groupFile.close();
    }
    // Input information and push data into vector listOfGroup
    void InputInformation() {
        Group* group = new Group();
        std::vector<std::string> nameOfStudentEnteredList;
        int numberOfGroupAdd = 0;
        std::cout << "(!)Class already have " << listOfGroup.size() << " groups." << "\n";
        // Enter number of group need to add until greater than 0
        while (numberOfGroupAdd <= 0) {
            std::cout << "(-)Enter number of groups in the class you want to add: "; std::cin >> numberOfGroupAdd;
            std::cout << "-------------------------------------------------------------\n";
            if (numberOfGroupAdd <= 0) {
                std::cout << "(!) You need to enter the number of added groups greater than 0 . Please re-enter\n";
            }
        }
        int numberOfGroups = numberOfGroupAdd + listOfGroup.size();
        for (int i = listOfGroup.size(); i < numberOfGroups; i++) {
            group->groupNumber = i + 1;
            int numberOfStudentInAGroup = 0;
            std::cout << "Enter information of group " << i + 1 << "\n";
            while (numberOfStudentInAGroup <= 0) {
                std::cout << "(-)Enter number of students: "; std::cin >> numberOfStudentInAGroup;
                if (numberOfStudentInAGroup <= 0) {
                    std::cout << "(!) You need to enter the number of added students greater than 0. Please re-enter\n";
                }
            }
            std::cin.ignore();
            for (int j = 0; j < numberOfStudentInAGroup; j++) {
                std::string nameOfStudent = "";
                bool isDuplicate = false;
                // enter number of student until not duplicate
                do {
                    isDuplicate = false;
                    std::cout << "(-)Enter name of student number " << j + 1 << ": ";
                    std::getline(std::cin, nameOfStudent);
                    for (auto group : listOfGroup) {
                        for (auto& nameOfStudentInList : group->nameOfStudentList) {
                            if (nameOfStudentInList == nameOfStudent) {
                                isDuplicate = true;
                                std::cout << "(!)Student already have in another group. Please re-enter\n";
                                break;
                            }
                        }
                        if (isDuplicate) {
                            break;
                        }

                    }
                    for (auto& nameOfStudentEntered : nameOfStudentEnteredList) {
                        if (nameOfStudentEntered == nameOfStudent) {
                            isDuplicate = true;
                            std::cout << "(!)Student already have in another group. Please re-enter\n";
                        }
                    }
                    if (!isDuplicate) {
                        group->nameOfStudentList.push_back(nameOfStudent);
                        nameOfStudentEnteredList.push_back(nameOfStudent);
                    }
                } while (isDuplicate);
            }
            std::cout << "-------------------------------------------------\n";
            listOfGroup.push_back(group);
            group = new Group();
            nameOfStudentEnteredList.clear();
        }
    }
    void SaveInformation() {
        std::ofstream groupFile(FILE_NAME);
        if (!groupFile.is_open()) {
            std::cerr << "Error opening file for writing: " << FILE_NAME << std::endl;
            return;
        }

        for (auto group : listOfGroup) {
            groupFile << "Group " + group->groupNumber << "\n";
            for (auto& nameOfStudent : group->nameOfStudentList) {
                groupFile << nameOfStudent << "\n";
            }
        }
    }
    void DisplayDataAllGroup() {
        printBorderOfTableGroup();
        printTopicOfTableGroup();
        printBorderOfTableGroup();

        int orderOfGroup = 1;

        for (auto group : listOfGroup) {
            int orderOfStudentInGroup = 1;
            for (auto& nameOfStudent : group->nameOfStudentList) {

                if (orderOfStudentInGroup == 1) {
                    printRowOfTableGroup(orderOfGroup, nameOfStudent);
                }
                else {
                    printRowOfTableGroup(nameOfStudent);
                }
                orderOfStudentInGroup++;
            }
            printBorderOfTableGroup();
            orderOfGroup++;

        }
    }
    void DisplayDataSingleGroup() {
        int groupNumber;
        std::string nameOfGroup;
        std::cout << "Enter number of group: ";
        std::cin >> groupNumber;
        printBorderOfTableGroup();
        printTopicOfTableGroup();
        printBorderOfTableGroup();
        int orderOfGroup = 1;
        for (auto group : listOfGroup) {
            int orderOfStudentInGroup = 1;
            if (group->groupNumber == groupNumber) {
                for (auto& nameOfStudent : group->nameOfStudentList) {

                    if (orderOfStudentInGroup == 1) {
                        printRowOfTableGroup(orderOfGroup, nameOfStudent);
                    }
                    else {
                        printRowOfTableGroup(nameOfStudent);
                    }
                    orderOfStudentInGroup++;
                }
                printBorderOfTableGroup();
            }
            orderOfGroup++;
        }
    }

    //Option 2
    std::vector<Project*> projects;
    void InputProjectInformation() {
        int dayIndex, monthIndex, yearIndex;
        if (projects.empty()) {
            Project* project = new Project();
            int numberOfProject;
            std::cout << "Enter number of project: "; std::cin >> numberOfProject;
            for (int i = 1; i <= numberOfProject; i++) {
                std::cin.ignore();
                std::cout << "(*) Enter information of Project " << i << "\n";
                project->projectNumber = i;
                std::cout << "(+) Enter a short description about project: ";
                std::getline(std::cin, project->shortDescriptionOfProject);
                std::cout << "(-) Enter a submission deadline of project\n";
                std::cout << "(+) Enter day of deadLine: "; std::cin >> dayIndex; project->dayOfDeadLine = dayIndex;
                std::cout << "(+) Enter month of deadLine: "; std::cin >> monthIndex; project->monthOfDeadLine = monthIndex;
                std::cout << "(+) Enter year of deadLine: "; std::cin >> yearIndex; project->yearOfDeadLine = yearIndex;
                project->deadline = std::to_string(yearIndex) + std::to_string(monthIndex) + std::to_string(dayIndex);
                addProject(project);
                project = new Project();
            }
        }
    }
    void displayProjects() const {
        if (projects.empty()) {
            std::cout << "No projects available.\n";
            return;
        }

        std::cout << "Project Information:\n";
        for (const auto project : projects) {
            std::cout << "Project: " << project->projectNumber << "\n";
            std::cout << "Description of project: " << project->shortDescriptionOfProject << "\n";
            std::cout << "Submission Deadline of project: " << project->dayOfDeadLine << "/" << project->monthOfDeadLine << "/" << project->yearOfDeadLine << "\n";
        }
    }
    void addProject(Project* project) {
        projects.push_back(project);
    }
    //Option 3
    void SubmitProject() {
        int groupIndex, projectIndex, dayIndex, monthIndex, yearIndex;
      
        std::cout << "Enter group number for project submission: ";
        std::cin >> groupIndex;

        if (groupIndex < 1 || groupIndex > listOfGroup.size()) {
            std::cout << "Invalid group number. Please try again.\n";          
            return;
        }
        
        std::cout << "Enter project number: ";
        std::cin >> projectIndex;

        if (projectIndex < 1 || projectIndex > projects.size()) {
            std::cout << "Invalid project number. Please try again.\n";
            return;
        }
        std::cout << "Enter submission date (day month year): ";
        std::cin >> dayIndex; 
        std::cin >> monthIndex;
        std::cin >> yearIndex;

        ProjectSubmission* submission = nullptr;

        
        for (auto& existingSubmission : listOfGroup[groupIndex - 1]->submissions) {
            if (existingSubmission->projectNumber == projectIndex) {
                submission = existingSubmission;
                break;
            }
        }

        if (!submission) {
            submission = new ProjectSubmission;
            submission->projectNumber = projectIndex;
            listOfGroup[groupIndex - 1]->submissions.push_back(submission);
        }
        submission->submissionDate = std::to_string(yearIndex) + std::to_string(monthIndex) + std::to_string(dayIndex);

        std::cout << "Project submitted successfully!\n";
    }
    // Option 4
    std::vector<ProjectSubmission*> submissions;
    std::string stateOnTime = "On Time";
    std::string stateLate = "Late";
    std::string stateNotSubmit = "Not submited yet";
    void SetStatement() {
        for (const auto& group : listOfGroup) {
            // Initialize submission status as "Not yet submitted";
            for (const auto& project : projects) {
                bool submitted = false;
                for (auto& submission : group->submissions) {
                    if (project->projectNumber == submission->projectNumber) {
                        if (submission->submissionDate.empty()) {
                            submission->statement = stateNotSubmit;
                        }
                        else if (submission->submissionDate <= project->deadline) {
                            submission->statement = stateOnTime;
                        }                     
                        else if (submission->submissionDate >= project->deadline) {
                            submission->statement = stateLate;
                        }
                        
                        submitted = true;
                        break;
                    }
                    
                }
                if (!submitted) {
                    ProjectSubmission *submission = new ProjectSubmission();
                    submission->projectNumber = project->projectNumber;
                    submission->statement = stateNotSubmit;
                    group->submissions.push_back(submission);
                }
            }
            
        }
    }
    void displaySubmissionStatus() {
        std::string optionOf4;
        std::cout << "(1) Display submission status by project\n"
            << "(2) Display submission status by group\n";
        std::cout << "Enter your option: ";
        std::getline(std::cin, optionOf4);

        if (optionOf4 == "1") {
            int project_number;
            std::cout << "Enter the project number: ";
            std::cin >> project_number;
            std::cin.ignore();
            // Display table header
            printBorderForOption4();
            std::cout << "\t" << std::setfill(' ')
                << "|" << std::setw(9) << "Group"
                << "|" << std::setw(19) << "\tStatement" << column_char << "\n";
            printBorderForOption4();

            for (const auto& group : listOfGroup) {
                // Initialize submission status as "Not yet submitted"
                for (const auto& submission : group->submissions) {
                    // Check if the group has a submission for the specified project
                    if (submission->projectNumber == project_number) {
                       
                        std::cout << "\t" << std::setfill(' ')
                            << "|" << std::setw(9) << group->groupNumber
                            << "|" << std::setw(23) << submission->statement << column_char << "\n";
                        printBorderForOption4();
                        break;
                    }
                }
            }
        }
        else if (optionOf4 == "2") {
            int group_Number;
            std::cout << "Enter group number: ";
            std::cin >> group_Number;
            // Display table header
            printBorderForOption4();
            std::cout << "\t" << std::setfill(' ')
                << "|" << std::setw(9) << "Group"
                << "|" << std::setw(19) << "\tStatement" << column_char << "\n";
            printBorderForOption4();
            for (const auto& project : projects) {
                
                for (const auto& submission : listOfGroup[group_Number - 1]->submissions) {
                    if (submission->projectNumber == project->projectNumber) {
                        
                        std::cout << "\t" << std::setfill(' ')
                            << "|" << std::setw(9) << project->projectNumber
                            << "|" << std::setw(23) << submission->statement << column_char << "\n";
                        printBorderForOption4();
                        break;
                    }
                }
            }

        }

    }
    // Option 5

    // Option 6
};
int main()
{
    HandleData* handleData = new HandleData();
    handleData->ReadFile();
    std::string option;
    while (true) {
        std::cout << "(1) Append and save group information\n";
        std::cout << "(2) Project dealine declaration\n";
        std::cout << "(3) Submit Project\n";
        std::cout << "(4) Display statistics\n";
        std::cout << "Enter your option: ";
        std::getline(std::cin, option);
        if (option == "1") {
            std::string optionOf1 = "";
            std::cout << "(1) Input information of groups\n"
                << "(2) Display information\n"
                << "(3) Save groups information\n";
            std::cout << "Enter your option: ";
            std::getline(std::cin, optionOf1);
            if (optionOf1 == "1") {
                handleData->InputInformation();
            }
            else if (optionOf1 == "2") {
                std::string optionOf1_2 = "";
                std::cout << "(1) Display information for all group\n"
                    << "(2) Display information for specific group\n";
                std::cout << "Enter your option: "; std::getline(std::cin, optionOf1_2);
                if (optionOf1_2 == "1") {
                    handleData->DisplayDataAllGroup();
                }
                else if (optionOf1_2 == "2") {
                    handleData->DisplayDataSingleGroup();
                }
            }
            else if (optionOf1 == "3") {
                handleData->SaveInformation();
            }
        }
        else if (option == "2") {
            std::string optionOf2;
            std::cout << "(1) Input Projects Information\n"
                << "(2) Display Information of Groups\n";
            std::cout << "Enter your option: ";
            std::getline(std::cin, optionOf2);
            if (optionOf2 == "1") {
                handleData->InputProjectInformation();
                std::cin.ignore();
            }
            else if (optionOf2 == "2") {
                handleData->displayProjects();
            }
        }
        else if (option == "3") {

            handleData->SubmitProject();
            handleData->SetStatement();
            std::cin.ignore();
        }
        else if (option == "4") {
            handleData->displaySubmissionStatus();
            std::cin.ignore();
        }
        std::cout << "(*)Press enter to back to menu...";
        //std::cin.ignore();
        std::getline(std::cin, option);
        system("cls");
    }



    delete handleData;
}