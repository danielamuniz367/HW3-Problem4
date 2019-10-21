#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int knapsackDP(int[], int[], int, int, vector<int>&);

int max(int, int);

int main()
{
	int T;          // no. of test cases
	int N;          // no. of items
	int P[100];     // prices of items
	int W[100];     // weights of items
	int F;          // no. of people in the family
	int M = 0;        // Maximum weight that can be carried

	vector<vector<int> > vec(100);
	ifstream inFile;
	ofstream outFile;
	
	inFile.open("shopping.txt");

	if (!inFile.is_open())
	{
		cout << "Error: cannot open file" << endl;
		return 1;
	}

	// open the output file
	outFile.open("results.txt");
	
	// read the number of test cases from the input file
	inFile >> T;
	
	// process T number of test cases
	for (int k = 0; k < T; k++)
	{
		for (int l = 0; l < vec.size(); l++)
			vec[l].clear();
		// read the number of items from the input file
		inFile >> N;

		// read the price and weight of each item
		// into respective arrays
		for (int i = 0; i < N; i++)
		{
			inFile >> P[i];
			inFile >> W[i];
		}

		int maxTPrice = 0;

		// read number of family members
		inFile >> F;

		// find maximum price of items that can be carried by
		// each family member and keep track the total of the
		// maximum prices

		for (int j = 0; j < F; j++)
		{
			// read the maximum weight that can be carried by a
			// current family member
			inFile >> M;
			// find maximum price of items that can be carried by
			// current family member and add it to maxPrice
			maxTPrice = maxTPrice + knapsackDP(W, P, N, M, vec[j]);
		}

		outFile << "Test Case " << k << endl;
		outFile << "Total Price " << maxTPrice << endl;
		outFile << "Member Items" << endl;

		// print the items each family member should take
		for (int t = 0; t < F; t++)
		{
			sort(vec[t].begin(), vec[t].end());
			outFile << t + 1 << ":";
			for (int s = 0; s < vec[t].size(); s++)
				outFile << vec[t][s] << " ";

			outFile << endl;
		}
	}

	// close the files
	inFile.close();
	outFile.close();

	return 0;
}

// returns the maximum price of items that can be carried

// by a person, who can carry maximum weight M

int knapsackDP(int W[], int P[], int N, int M, vector<int> &v)
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

	// stores the result of Knapsack
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
			// Since this weight is included its
			// value is deducted
			res = res - P[i - 1];
			w = w - W[i - 1];
		}
	}
	// K[N][M] represents the maximum price of items that can be carried by
	// the family member
	return K[N][M];
}

// returns maximum of two parameters that are received
int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;

}
