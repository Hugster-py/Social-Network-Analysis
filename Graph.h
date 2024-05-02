#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

using namespace std;

class account{
 
 private:
    string name;
    vector<string> following;
    vector<string> followers;
    int outDegree;
    int inDegree;

    
 public:
    account(){ name="null"; }
    account(string name){ this->name = name;}
    void SetName(string name){ this->name = name;}
    void SetFollower(string follower){ followers.push_back(follower);}
    void SetFollowing(string following){ this->following.push_back(following);}
    vector<string> GetFollower(){ return followers;}
    vector<string> GetFollowing(){ return following;}
    string GetName(){return name;}
    int GetOutDegree(){return outDegree;}
    int GetInDegree(){return inDegree;}
    void SetOutDegree(){ outDegree = following.size();}
    void SetInDegree(){ inDegree = followers.size();}
    bool operator<(const account& rhs);
    

};


#endif // GRAPH_H