#include <iostream>
#include <string>

using namespace std;

int main()
{
  string proceed;
  string hilo;
  cout << "What would you like me to say???" << endl;
  getline(cin, hilo);
  cout << "Okay fine I will say that..." << endl;
  cout << "Press enter... " << endl;
  getline(cin, proceed);
  cout << hilo << endl;
  return 0;
}
