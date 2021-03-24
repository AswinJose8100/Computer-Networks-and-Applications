#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main (){

  string datain;
  ifstream fin;
  string filename;
  char MAX_NODE[27] = { };  
  int initArray[50][50]; 
  int distance[50];
  
  
  cout << "Please type in your input file" << endl;
  
  cin >> filename;
  cout << "\n";
  
  fin.open (filename);
  getline (fin, datain);
  int N = datain[2] - '0';  // - '0' to give me a digit value and not char
  int count = 0;
  
// We should first initialize our init array by setting all the unreachable nodes with distance - 1 


  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
	{
	  initArray[i][j] = -1;
	}
    }
  getline (fin, datain);
  
  int strlen = datain.length ();
  
  for (int i = 0; i < strlen; i += 2)
    {
      MAX_NODE[count] = datain[i];
      count++;
    }
    
  int temp = 0;
  
  while (getline (fin, datain))
    {
      int input_dis = datain[4] - '0';
      
      distance[temp] = input_dis;
      
      temp++;
    }
//Assign all the distance in the distance array to corresponding nodes
  int temp_counter = 0;
  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
	{
	  if (i == j)
	    {
	      initArray[i][j] = 0;        //Dist from same node is 0
	    }
	  if (initArray[i][j] == -1)
	    { 
	      int temp1[50];
	      for (int x = 0; x < temp; x++)
		{
		  temp1[x] = distance[x];
		}
	      initArray[i][j] = initArray[j][i] = temp1[temp_counter];
	      temp_counter++;
	   
		}
    }}

//crete dist array for sharing distance info
  int dist[50][50][50];
  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
	{
	  for (int k = 0; k < N; k++)
	    {
	     if ((initArray[i][j] > -1) && (initArray[j][k] > -1))
    {
      dist[i][j][k] = initArray[j][k] + initArray[i][j];
    }
  else
    {
      dist[i][j][k] = -1;
   		 }
	    }
	}
    }

// FINDING SHORTEST PATH FROM NODE A TO NODE B AND STORE IT IN ARRAY RESULT
  int result[50][50];
  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
	{
	  result[i][j] = initArray[j][i];
	  for (int k = 0; k < N; k++)
	    {
	      if ((result[i][j] > dist[i][k][j]) || (result[i][j] == -1))
		{
		  if (dist[i][k][j] > -1)
		    {
		      result[i][j] = dist[i][k][j];
		    }
		}
	    }
	  if (result[i][j] == -1)
	    {
	      for (int k = 0; k < N; k++)
		{
		  if (result[i][k] != -1)
		    if (result[k][j] != -1)
		    {
		      if ((result[i][j] == -1) || ((result[i][j] != -1) && (result[i][j] > result[i][k] + result[k][j])))
			{
			  if (result[i][k] + result[k][j] > -1)
			    {
			      result[i][j] = result[i][k] + result[k][j];
			    }
			}
		    }
		}
	    }
	}
    }


cout << "\n";
cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
cout << "\n";

cout << "Distance Vector Tables:"<<endl;
int rounds = 0;
for (int i=0;i<N;i++)
	{	rounds+=1;
		cout<<"\n"<<MAX_NODE[i]<<" Table ";
		cout<<"\nNode \tDist ";
		
	for(int j=0;j<N;j++)
		{
			cout<<"\n"<<MAX_NODE[j]<<"\t"<<result[i][j]<<"\t";
		}
	}
	cout<<"\n"<<endl;
	cout<<"Number of rounds:"<<rounds<<endl;
	cout<<"\n"<<endl;
	
	
}