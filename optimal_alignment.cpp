#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;


// Define the size of the DP
const int size_c = 10000;
int dp[size_c][size_c] ;


int Sd;
string A,B;

//define the size of the score matrix
const int size_score_c = 4;
int score[size_score_c][size_score_c];
inline int nuc2idx (char nuc);

//To print out the paths
void out(vector<pair<char,char> > patha){
    string r, s;
    for(vector<pair<char,char> >::size_type i = 0; i<patha.size();++i){
        r += patha[i].first;
        s += patha[i].second;
    }
    cout<<r<<endl;
    cout<<s<<endl;
    cout<<endl;
}

// initialize the dp matrix
void init_dp(){
    for(int i = 0; i < size_c; ++i){
        for(int j = 0; j < size_c; ++j){
            dp[i][j] = -10000;
        }
    }
}

//calculate the dp matrix
void do_dp(){
  // Initialize dp matrix (first row)
  dp[A.size()][B.size()] = 0;
  for(int j = (int)B.size()-1; j>= 0; j--){
    dp[A.size()][j] = dp[A.size()][j+1] +Sd;
  }
  for (int i = (int)A.size()-1; i>= 0; i--){
    //"Phi" case
    dp[i][B.size()] = dp[i+1][B.size()] +Sd;
    for(int j = (int)B.size()-1; j>= 0; j--){
      //Diagonal
      dp[i][j] = max(dp[i][j], dp[i+1][j+1] + score[nuc2idx(A[i])][nuc2idx(B[j])]);
      //veritical
      dp[i][j] = max(dp[i][j], dp[i+1][j] + Sd);
      //Horizontal
      dp[i][j] = max(dp[i][j], dp[i][j+1] +Sd);
    }
  }
}

//backtracing function
void dfs_(int i, int j ,vector<pair<char,char> > path){
    // Reached terminal
    if (i == A.size() && j == B.size()){
        //Output answer
        out(path);
        return;
    }
    //Try vertical
    if(i<A.size() && dp[i+1][j] +Sd == dp[i][j]){
        vector<pair<char,char> > tmp = path;
        tmp.push_back(make_pair(A[i],'_'));
        dfs_(i+1, j,tmp); //also, try record answer here
    }
    // Try diagonal
    if(i<A.size() && j < B.size() && dp[i+1][j+1] +score[nuc2idx(A[i])][nuc2idx(B[j])] == dp[i][j]){
        vector<pair<char,char> > tmp = path;
        tmp.push_back(make_pair(A[i],B[j]));
        dfs_(i+1,j+1,tmp); //also, try record answer here
    }
    // Try horizontal
    if(j<B.size() && dp[i][j+1] +Sd == dp[i][j]){
        vector<pair<char,char> > tmp = path;
        tmp.push_back(make_pair('_',B[j]));
        dfs_(i,j+1,tmp); //also, try recrod answer here
    }
}

char idx2nuc[] = "ACGT";
inline int nuc2idx (char nuc){
  switch (nuc) {
    case 'A': return 0;
    case 'C': return 1;
    case 'G': return 2;
    case 'T': return 3;
  }
  return -1;
}

//initialize the score matrix in each case
void init_score(int match, int si,int ver){
    int A = 0,C = 1,G = 2,T =3;
    score[A][A] = match;
    score[C][C] = match;
    score[G][G] = match;
    score[T][T] = match;

    score[A][G] = si;
    score[G][A] = si;
    score[C][T] = si;
    score[T][C] = si;

    score[A][C] = ver;
    score[C][A] = ver;
    score[A][T] = ver;
    score[T][A] = ver;

    score[C][G] = ver;
    score[G][C] = ver;
    score[G][T] = ver;
    score[T][G] = ver;
}

//main function 
int main() {
    init_dp();
    int match, transi, tranver;
    cin >> match;
    cin >> transi;
    cin >> tranver;
    cin >> Sd;
    cin >> A;
    cin >> B;

    init_score(match, transi, tranver);

    do_dp();
    cout<<dp[0][0]<<endl;
    cout<<endl;
    vector<pair<char,char> > path;
    dfs_(0,0,path);


	return 0;
}
