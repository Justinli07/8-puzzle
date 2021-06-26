#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Node.h"

using namespace std;

void default_puzzle_solver();
void custom_puzzle_solver();
void splitStr(string input, int data[3][3], int row);
void uniform_cost_search(int input[3][3]);
void aStar_MT_search(int input[3][3]);
void aStar_MD_search(int input[3][3]);
bool isGoal(Node* node);
bool isDuplicate(Node* node, vector<Node*> list);
void copyArr(int arr0[3][3], int arr1[3][3]);


 int goal_state[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
 int trivial[3][3]	= { {1,2,3},{4,5,6},{7,8,0} };
 int superEasy[3][3] = { {1,2,3},{4,5,6},{7,0,8} };
 int easy[3][3]	= { {1,2,0},{4,5,3},{7,8,6} };
 int doable[3][3] = { {0,1,2},{4,5,3},{7,8,6} };
 int hard[3][3] = { {8,7,1},{6,0,2},{5,4,3} };
 int impossible[3][3] = { {1,2,3},{4,5,6},{8,7,0} };



int main()
{
	int option;
	bool again;
	string str;
	cout << "Welcome to Justin's 8-puzzle solver.\n";

	do
	{
		again = false;
		cout << "Type '1' to use a dafault puzzle, or '2' enter your own puzzle.\n";
		cin >> option;
		switch (option)
		{
		case 1:
			default_puzzle_solver();
			break;
		case 2:
			custom_puzzle_solver();
			break;
		default:
			cout << "Error: wrong input. Program terminated" << endl;
		}

		cout << "Again? (Y/N)\n";
		cin >> str;
		if (str == "y" || str == "Y")
		{
			again = true;
		}
	} while (again);

}

void default_puzzle_solver()
{
	int op;
	int input[3][3];
	cout << "You wish to use the default puzzle." << endl;
	cout << "Please selecte the difficulty for init node.\n"
		<< "1.Trivial\n"
		<< "2.SuperEasy\n"
		<< "3.Easy\n"
		<< "4.Doable\n"
		<< "5.Hard\n"
		<< "6.Impossible\n";
	cin >> op;

	switch (op)
	{
	case 1:
		copyArr(input,trivial);
		break;
	case 2:
		copyArr(input, superEasy);
		break;
	case 3:
		copyArr(input, easy);
		break;
	case 4:
		copyArr(input, doable);
		break;
	case 5:
		copyArr(input, hard);
		break;
	case 6:
		copyArr(input, impossible);
		break;
	default:
		cout << "Wrong input!\n";
		break;
	}

	cout << "Enter your choice of algorithm\n"
		<< "1. Uniform Cost Search.\n"
		<< "2. A* with the Misplaced Tile heuristic.\n"
		<< "3. A* with the Manhattan distance heuristic.\n";

	cin >> op;

	switch (op)
	{
	case 1:
		uniform_cost_search(input);
		break;
	case 2:
		aStar_MT_search(input);
		break;
	case 3:
		aStar_MD_search(input);
		break;
	}


	return;
}

void custom_puzzle_solver()
{
	string firstRow, secondRow, thirdRow;
	int op;
	int input[3][3];
	cout << "Enter your puzzle, use a zero to represent blank.\n";
	cout << "Enter the first row, use space or tabs between numbers: ";
	cin.ignore();

	getline(cin, firstRow);
	cout << "Enter the second row, use space or tabs between numbers: ";
	getline(cin, secondRow);
	cout << "Enter the third row, use space or tabs between numbers: ";
	getline(cin,thirdRow);

	//read the input node
	splitStr(firstRow, input, 0);
	splitStr(secondRow, input, 1);
	splitStr(thirdRow, input, 2);

	cout << "Enter your choice of algorithm\n"
		<< "1. Uniform Cost Search.\n"
		<< "2. A* with the Misplaced Tile heuristic.\n"
		<< "3. A* with the Manhattan distance heuristic.\n";

	cin >> op;

	switch (op)
	{
	case 1:
		uniform_cost_search(input);
		break;
	case 2:
		aStar_MT_search(input);
		break;
	case 3:
		aStar_MD_search(input);
		break;
	}

}

//split the string input stream to integers, and store them to corresponding puzzle;
void splitStr(string input, int data[3][3], int row)
{
	int index = 0;
	input = input + ' ';
	string word = "";
	int front = 0;

	//get rid of the empty space at the beginning of the input string
	if (input.size() > 0)
	{
		while (input[front] == ' ')
		{
			front++;
		}
		input = input.substr(front, input.size() - front);
	}

	//get rid of the space between words of the input string
	for (auto x : input)
	{
		unsigned i = 1;
		if ((x == ' ' || x == '\t') && index < 3)
		{
			data[row][index] = stoi(word);
			word = "";
			index++;
		}
		else
		{
			word = word + x;
		}
	}
	return;
}

void uniform_cost_search(int input[3][3])
{

	Node* cur = new Node(input);
	vector<Node*> vlist; //a list that contain all the visited node
	vlist.push_back(cur);
	list<Node*> queue;  //a queue that contain all the nodes to be visited
	bool isDone = false;
	int maxNode = 0;
	int maxQ = 0;

	cout << "Expanding the start node: \n";
	cur->printNode();

	do
	{
		if (isGoal(cur)) //if it reach the goal state, return
		{
			cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
			cur->printNode();
			cout << "Reached the goal state!!!\n";
			isDone = true;
			cout << "Number of nodes expanded: " << maxNode << endl;
			cout << "Maximum queue size: " << maxQ << endl;
			return;
		}

		for (int i = 0; i < 4; i++)
		{
		
			Node* temp = cur->action(i);
			if (temp != 0 && !isDuplicate(temp, vlist))
			{
				vlist.push_back(temp);
				queue.push_back(temp);
				maxNode++;
			}
		}

		cur = queue.front();
		cout << "Expanding this node: \n";
		cur->printNode();
		cout << "Queue size: " << queue.size() << endl;
		cout << "#Nodes " << vlist.size() << endl;
		if (maxQ < queue.size())
		{
			maxQ = queue.size();
		}
		queue.pop_front();

	} while (!queue.empty());
	
	if (!isDone)
	{
		cout << "No solution!!!\n";
	}

	cout << "Number of nodes expanded: " << maxNode << endl;
	cout << "Maximum queue size: " << maxQ << endl;
}

void aStar_MT_search(int input[3][3])
{
	Node* cur = new Node(input);
	vector<Node*> vlist; //a list that contain all the visited node
	vlist.push_back(cur);
	vector<Node*> queue;  //a queue that contain all the nodes to be visited
	bool isDone = false;
	int maxNode = 0;
	int maxQ = 0;

	cout << "Expanding the start node: \n";
	cur->printNode();

	do
	{
		if (isGoal(cur)) //if it reach the goal state, return
		{
			cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
			cur->printNode();
			cout << "Reached the goal state!!!\n";
			isDone = true;
			cout << "Number of nodes expanded: " << maxNode << endl;
			cout << "Maximum queue size: " << maxQ << endl;
			return;
		}

		for (int i = 0; i < 4; i++)
		{

			Node* temp = cur->action(i);
			if (temp != 0 && !isDuplicate(temp, vlist))
			{
				temp->calHScore();
				vlist.push_back(temp);
				queue.push_back(temp);
				maxNode++;
			}
		}

		
		Node* min = queue[0];
		int index = 0;
		int minf = min->gScore + min->hScore;
		for (int j = 0; j < queue.size(); j++)
		{
			int fScore = queue[j]->gScore + queue[j]->hScore;
			if (fScore < minf)
			{
				min = queue[j];
				minf = fScore;
				index = j;
			}
		}
		cur = min;
		cout << "Expanding this node with g(n)= " << cur->gScore << " h(n)= " << cur->hScore << endl;;
		cur->printNode();
		cout << "Queue size: " << queue.size() << endl;
		cout << "#Nodes " << vlist.size() << endl;
		if (maxQ < queue.size())
		{
			maxQ = queue.size();
		}
		queue.erase(queue.begin() + index);

	} while (!queue.empty());

	if (!isDone)
	{
		cout << "No solution!!!\n";
	}

	cout << "Number of nodes expanded: " << maxNode << endl;
	cout << "Maximum queue size: " << maxQ << endl;
}

void aStar_MD_search(int input[3][3])
{
	Node* cur = new Node(input);
	vector<Node*> vlist; //a list that contain all the visited node
	vlist.push_back(cur);
	vector<Node*> queue;  //a queue that contain all the nodes to be visited
	bool isDone = false;
	int maxNode = 0;
	int maxQ = 0;

	cout << "Expanding the start node: \n";
	cur->printNode();

	do
	{
		if (isGoal(cur)) //if it reach the goal state, return
		{
			cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
			cur->printNode();
			cout << "Reached the goal state!!!\n";
			isDone = true;
			cout << "Number of nodes expanded: " << maxNode << endl;
			cout << "Maximum queue size: " << maxQ << endl;
			return;
		}

		for (int i = 0; i < 4; i++)
		{

			Node* temp = cur->action(i);
			if (temp != 0 && !isDuplicate(temp, vlist))
			{
				temp->calHScore_M(); //calculate the Manhattan distance
				vlist.push_back(temp);
				queue.push_back(temp);
				maxNode++;
			}
		}


		Node* min = queue[0];
		int index = 0;
		int minf = min->gScore + min->hScore;
		for (int j = 0; j < queue.size(); j++)
		{
			int fScore = queue[j]->gScore + queue[j]->hScore;
			if (fScore < minf)
			{
				min = queue[j];
				minf = fScore;
				index = j;
			}
		}
		cur = min;
		cout << "Expanding this node with g(n)= " << cur->gScore << " h(n)= " << cur->hScore << endl;;
		cur->printNode();
		cout << "Queue size: " << queue.size() << endl;
		cout << "#Nodes " << vlist.size() << endl;
		if (maxQ < queue.size())
		{
			maxQ = queue.size();
		}
		queue.erase(queue.begin() + index);

	} while (!queue.empty());

	if (!isDone)
	{
		cout << "No solution!!!\n";
	}

	cout << "Number of nodes expanded: " << maxNode << endl;
	cout << "Maximum queue size: " << maxQ << endl;
}

//check the input node, see if it is equal to goal state
bool isGoal(Node* node)
{
	for (unsigned i = 0; i < 3; i++)
	{
		for (unsigned j = 0; j < 3; j++)
		{
			if (node->data[i][j] != goal_state[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

//check for duplicate node 
bool isDuplicate(Node* node, vector<Node*> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (node->isSame(list[i]))
		{
			return true;
		}
	}
	return false;
}

//copy arr1 to arr0
void copyArr(int arr0[3][3], int arr1[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			arr0[i][j] = arr1[i][j];
}


