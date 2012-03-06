#include <vector>
#include <iostream>
using namespace std;

int main(){

 int la4[][3][2] = {{{0, -1}, {1, -1}, {2, -1}}};
 int lb4[][3][2] = {{{1,  2}, {0,  2}, {0,  1}}};

  cout<<la4[0][0][0]<<endl;
  cout<<la4[0][0][1]<<endl;
  cout<<la4[0][1][0]<<endl;
  cout<<la4[0][1][1]<<endl;
  cout<<la4[0][2][0]<<endl;
  cout<<la4[0][2][1]<<endl;

  cout<<"***"<<endl;
  cout<<lb4[0][0][0]<<endl;
  cout<<lb4[0][0][1]<<endl;
  cout<<lb4[0][1][0]<<endl;
  cout<<lb4[0][1][1]<<endl;
  cout<<lb4[0][2][0]<<endl;
  cout<<lb4[0][2][1]<<endl;

  cout<<"***"<<endl;
  vector<int> t;
  t.push_back(0);
  t.push_back(1);
  t.push_back(2);

  for(std::vector<int>::iterator ia=t.begin();ia!=t.end();++ia){
    cout<<"begin= " << (*(t.begin())) << " end="<< (*(t.end())) << " a= "<< *ia << endl;
  }
}
