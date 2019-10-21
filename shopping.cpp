/*shopping.cpp*/

#include<iostream>

#include<fstream>

using namespace std;

int knapsackDP(int[], int[], int, int);

int max(int, int);

int main()

{

     int T;          // no. of test cases

     int N;          // no. of items

     int P[100];     // prices of items

     int W[100];     // weights of items

     int F;          // no. of people in the family

     int M = 0;        // Maximum weight that can be carried

     ifstream inFile;

     ofstream outFile;

     // open input file

     inFile.open("shopping.txt");

     // check whether the input file is opend or not

     if (!inFile.is_open())

     {

          cout << "can't open the file" << endl;

          return 1;

     }

     // open the output file

     outFile.open("shopping.out");

     // check whehter the output file is opened or not

     if (!outFile.is_open())

     {

          cout << "can't open the file" << endl;

          return 1;

     }

     // read the number of test cases from the input file

     inFile >> T;

     // process T number of test cases

     for (int k = 0; k<T; k++)

     {

          // read the number of items from the input file

          inFile >> N;

          // read the price and weight of each item

          // into respective arrays

          for (int i = 0; i<N; i++)

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

          for (int j = 0; j<F; j++)

          {

              // read the maximum weight that can be carried by a

              // current family member

              inFile >> M;

              // find maximum price of items that can be carried by

              // current family member and add it to maxPrice

              maxTPrice = maxTPrice + knapsackDP(W, P, N, M);

          }

          // Write the maximum total price to output file

          outFile << maxTPrice << endl;

          // Write the maximum total price to console

          cout << maxTPrice << endl;

     }

     // close the files

     inFile.close();

     outFile.close();

     return 0;

}

// returns the maximum price of items that can be carried

// by a person, who can carry maximum weight M

int knapsackDP(int W[], int P[], int N, int M)

{

     int K[N + 1][M + 1];

     // Build table K[][]

     for (int i = 0; i <= N; i++)

     {

          for (int w = 0; w <= M; w++)

          {

              if (i == 0 || w == 0)

                   K[i][w] = 0;

              else if (W[i - 1] <= w)

                   K[i][w] = max(P[i - 1] + K[i - 1][w - W[i - 1]], K[i - 1][w]);

              else

                   K[i][w] = K[i - 1][w];

          }

     }

     // K[N][M] represents the maximum price of items that can be carried by

     // the family member

     return K[N][M];

}

// returns maximum of two parameters that are recieved

int max(int a, int b)

{

     if (a > b)

          return a;

     else

          return b;

}
