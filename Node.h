#pragma once
#include<vector>
#include<iostream>

const int goal[3][3] = { {1,2,3},
							   {4,5,6},
							   {7,8,0} };

struct Node
{
	int data[3][3] = { {0,0,0},{0,0,0},{0,0,0} };
	int coord_x = 0; //the x coordinate of blank spot
	int coord_y = 0; //the y coordinate of blank spot
	int gScore = 0;
	int hScore = 0;
	int start_x = 0; //the x coordinate of blank spot from initial node
	int start_y = 0; //the y coordinate of blank spot from initial node


	Node() {}

	Node(int arr[3][3])
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				data[i][j] = arr[i][j];
				if (arr[i][j] == 0)
				{
					coord_x = j;
					coord_y = i;
					start_x = j;
					start_y = i;
				}
			}
		}
	}

	//print this* node
	void printNode()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				std::cout << data[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	//takes in op as the operation indicator and perform the correspoding action
	Node* action(int op)
	{
		switch (op)
		{
		case 0:
			return down();
			break;
		case 1:
			return right();
			return up();
			break;
		case 2:
			return left();
			break;
		case 3:
			return up();
			break;
		}
	}

	//check if this* is the same as the input node 
	bool isSame(Node* node)
	{
		for (unsigned i = 0; i < 3; i++)
		{
			for (unsigned j = 0; j < 3; j++)
			{
				if (this->data[i][j] != node->data[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	//copy input node's data members to this* node
	void copyNode(Node* node)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				data[i][j] = node->data[i][j];
				coord_x = node->coord_x;
				coord_y = node->coord_y;
				start_x = node->start_x;
				start_y = node->start_y;
				gScore = node->gScore;
				hScore = node->hScore;
			}
		}
	}

	//calculate the g(n) value
	void calGScore()
	{
		gScore = abs(start_x - coord_x) + abs(start_y - coord_y);
	}

	//calculate the h(n) value for A* with misplaced tile
	void calHScore()
	{
		int val = 0;
		for (unsigned i = 0; i < 3; i++)
		{
			for (unsigned j = 0; j < 3; j++)
			{
				if (data[i][j] != goal[i][j] && data[i][j] != 0)
				{
					val++;
				}
			}
		}

		hScore = val;
	}

	//calculate the h(n) value for A* with Manhattan distance
	void calHScore_M()
	{
		int x[9] = { 2,0,1,2,0,1,2,0,1 };
		int y[9] = { 2,0,0,0,1,1,1,2,2 };
		int val = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (data[i][j] != goal[i][j] && data[i][j] != 0)
				{

					val += abs(i - y[data[i][j]]) + abs(j - x[data[i][j]]);
				}
			}
		}

		hScore = val;
	}

	//swap the tile above the blank tile with the blank title
	Node* up()
	{
		if (coord_y - 1 >= 0)
		{
			Node* newNode = new Node();
			newNode->copyNode(this);
			int temp = newNode->data[coord_y - 1][coord_x];
			newNode->data[coord_y - 1][coord_x] = newNode->data[coord_y][coord_x];
			newNode->data[coord_y][coord_x] = temp;
			newNode->coord_y -= 1;
			newNode->gScore++;
			return newNode;
		}
		return 0;
	}

	//swap the tile below the blank tile with the blank title
	Node* down()
	{
		if (coord_y + 1 < 3)
		{
			Node* newNode = new Node();
			newNode->copyNode(this);
			int temp = newNode->data[coord_y + 1][coord_x];
			newNode->data[coord_y + 1][coord_x] = newNode->data[coord_y][coord_x];
			newNode->data[coord_y][coord_x] = temp;
			newNode->coord_y += 1;
			newNode->gScore++;
			return newNode;
		}
		return 0;
	}

	//swap the tile left to the blank tile with the blank title
	Node* left()
	{
		if (coord_x - 1 >= 0)
		{
			Node* newNode = new Node();
			newNode->copyNode(this);
			int temp = newNode->data[coord_y][coord_x - 1];
			newNode->data[coord_y][coord_x - 1] = newNode->data[coord_y][coord_x];
			newNode->data[coord_y][coord_x] = temp;
			newNode->coord_x -= 1;
			newNode->gScore++;
			return newNode;
		}
		return 0;
	}

	//swap the tile right to the blank tile with the blank title
	Node* right()
	{
		if (coord_x + 1 < 3)
		{
			Node* newNode = new Node();
			newNode->copyNode(this);
			int temp = newNode->data[coord_y][coord_x + 1];
			newNode->data[coord_y][coord_x + 1] = newNode->data[coord_y][coord_x];
			newNode->data[coord_y][coord_x] = temp;
			newNode->coord_x += 1;
			newNode->gScore++;
			return newNode;
		}
		return 0;
	}

};
