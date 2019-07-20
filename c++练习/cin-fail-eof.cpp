#include<iostream>
#include<cstdlib>
int main()
{
    using namespace std;
    int input;
    int sum=0;
    while(cin >> input){
        sum+=input;
    }
    cout <<"sum = "<<sum <<endl;
    if(cin.fail() && !cin.eof()) //failbit==1
    {
        cin.clear();
        while(cin.get()!='\n'){
            continue;
        }
    }
/*     {
        cin.clear();
        while(!isspace(cin.get())){
            continue; 
        }
    } */
    //以上这种方法其实也可以
    else
    {
        cout << "eofbit == 1\n";
        exit(1);
    }
    cin >> input;
    cout << input << endl;
    return 0;
}