#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int shoppingKnapsack(int[], int[], int, int, vector<int>&);
int max(int, int);

int main()
{
	int T;          // test cases
	int N;          // number of items
	int P[100];     // prices of items
	int W[100];     // weights of items
	int F;          // number of people in the family
	int M = 0;      // Max weight that can be carried

	vector<vector<int>> vec(100);
	ifstream inFile;
	ofstream outFile;
	
	inFile.open("shopping.txt");

	if (!inFile.is_open())
	{
		cout << "Error: cannot open file" << endl;
		return 1;
	}

	outFile.open("results.txt");
	
	inFile >> T;
	
	for (int k = 0; k < T; k++)
	{
		for (int l = 0; l < vec.size(); l++)
			vec[l].clear();
		
		inFile >> N;

		for (int i = 0; i < N; i++)
		{
			inFile >> P[i];
			inFile >> W[i];
		}

		int maxPrice = 0;

		inFile >> F;

		// find max price of items that can be carried by each family member
		// and keep track the total of the max prices
		for (int j = 0; j < F; j++)
		{
			// read the maximum weight that can be carried by a
			// current family member
			inFile >> M;
			// find maximum price of items that can be carried by
			// current family member and add it to maxPrice
			maxPrice = maxPrice + shoppingKnapsack(W, P, N, M, vec[j]);
		}

		outFile << "Test Case " << k + 1 << endl;
		outFile << "Total Price " << maxPrice << endl;
		outFile << "Member Items" << endl;

		// print the items each family member should take
		for (int t = 0; t < F; t++)
		{
			sort(vec[t].begin(), vec[t].end());
			outFile << "    " << t + 1 << ":";
			for (int s = 0; s < vec[t].size(); s++)
				outFile << vec[t][s] << " ";

			outFile << endl;
		}
	}

	inFile.close();
	outFile.close();

	return 0;
}

// returns the max price of items that can be carried
// by a person, who can carry max weight M
int shoppingKnapsack(int W[], int P[], int N, int M, vector<int> &v)
{
	int K[N + 1][M + 1];
	
	// Build table K[][]
	for (int i = 0; i <= N; i++)
	{
		for (int w = 0; w <= M; w++)
		{
			if (i == 0 || w == 0)
			{
				K[i][w] = 0;
			} else if (W[i - 1] <= w)
			{
				K[i][w] = max(P[i - 1] + K[i - 1][w - W[i - 1]], K[i - 1][w]);
			} else
				K[i][w] = K[i - 1][w];
		}
	}

	// stores Knapsack results
	int res = K[N][M];
	int w = M;

	for (int i = N; i > 0 && res > 0; i--)
	{
		if (res == K[i - 1][w])
			continue;
		else
		{
			// This item is included.
			v.push_back(i);
			
			// Since this weight is included its value is deducted
			res = res - P[i - 1];
			w = w - W[i - 1];
		}
	}
	
	// K[N][M] represents the max price of items that can be carried by
	// the family member
	return K[N][M];
}

// returns max of two received parameters
int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}
