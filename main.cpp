//include libraries that your code uses
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "Graph.h"
#include "Project4a.h"

using namespace std;

//compares the accound by name instead of by degree (as in the overloaded operator within  the class)
bool CompareAccountbyName(account& account1, account& account2){
    return account1.GetName()<account2.GetName();
}


///////////////// Before submitting your code
//1) uncomment this part since zyBooks use it.
int main(int argc, const char* argv[]) {
    if (argc != 2)
    {
        std::cout << "./project4 inputFile" << std::endl;
        return EXIT_FAILURE;
    }
    string inputFileName = argv[1];
    
///////////////////// uncomment above befofre submitting on zyBooks /////////////////
//2) Comment the next 2 lines below

// int main(void) {
//     string inputFileName = "input2.txt";    //Do NOT change the name "inputFileName" since used above
    
  vector<account> data;
  string stringTemp;
  string neighborTemp;
  string nameTemp;
  ifstream inFS;
  bool matchCheck1 = false;
  bool matchCheck2 = false;

  inFS.open(inputFileName);
  if (!inFS.is_open()) {
    cout << "Error opening file" << endl;
    return -1;
  }

    //reading in data 
  while (getline(inFS,stringTemp)) {
    matchCheck1 = false;
    matchCheck2 = false;
    //turning each character to lowercase
    for(int i=0; i<stringTemp.size();i++){
        stringTemp.at(i) = tolower(stringTemp.at(i));
    }
    istringstream inS(stringTemp);
    inS>>nameTemp>>neighborTemp;

    for (int i = 0; i < data.size(); i++) {
      if (data.at(i).GetName() == nameTemp) {
        matchCheck1 = true;
        data.at(i).SetFollower(neighborTemp);
      } else if (data.at(i).GetName() == neighborTemp) {
        data.at(i).SetFollowing(nameTemp);
        matchCheck2 = true;
      }
      if (matchCheck1 && matchCheck2) {
        break;
      }
    }
    //creating new members if they didn't exist
    if(!matchCheck1 || !matchCheck2){
    if (matchCheck1 == false) {
        account newAccount(nameTemp); 
        newAccount.SetFollower(neighborTemp);
        data.push_back(newAccount);
    }
    if (matchCheck2 == false) {
        account newAccount(neighborTemp); 
        newAccount.SetFollowing(nameTemp);
        data.push_back(newAccount);
    }
    }
  }
  inFS.close();
 
  //sets the InDegree of each account within data
  for(int i=0; i<data.size();i++){
      data.at(i).SetInDegree();
  }
  
    //sorts data by degree  from overloaded operator
   sort(data.begin(), data.end());
   
   //gets the data member with highest degree
   account root_account = data.at(data.size()-1);
   
   //gets the followers and the accounts of those followers
   vector<string> roots_followers = root_account.GetFollower();
   vector<account> followers_accounts;
  
   //sorts follower alphabetically
   sort(roots_followers.begin(), roots_followers.end());
   
   //populates the accounts of the followers
    for(int i=0; i<data.size();i++){
      for(int j=0; j<roots_followers.size();j++){
          if(data.at(i).GetName() == roots_followers.at(j)){
             followers_accounts.push_back(data.at(i));
          }
      }
    }
  
  
  //sorts the followers by their name instead of in degrees 
  sort(followers_accounts.begin(),followers_accounts.end(), CompareAccountbyName);
  
  //size of network
  int social_network_count = data.size();
  
  
  //print statements
  cout<<"The root user is "<<root_account.GetName()<<", with in-degree centrality of "<<root_account.GetInDegree()<<"."<<endl;
  cout<<"There are "<<social_network_count<<" users in the social network."<<endl;
  cout<<root_account.GetName()<<" (0)"<<endl;
  for(int i=0; i<followers_accounts.size();i++){
      //prints account name
      cout<<followers_accounts.at(i).GetName()<<" (1)"<<endl;
      //prints account followers alphabetically
      vector<string> followers_followers = followers_accounts.at(i).GetFollower();
      sort(followers_followers.begin(),followers_followers.end());
      for(int j=0;j<followers_followers.size();j++){
          cout<<followers_followers.at(j)<<" (2)"<<endl;
      }
  }

 
   
   return 0;   
}


