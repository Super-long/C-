#include<bits/stdc++.h>
using namespace std;

class GameCharacter;

int defaultHealth(const GameCharacter&){
    cout << "hello world";
}

class GameCharacter{
    public:
        using HealthFunc = function<int(const GameCharacter&)>;
        explicit GameCharacter(HealthFunc hcf = defaultHealth) : Healthcala(hcf), all(100) {}
        int Healthfunc() const{
            Healthcala(*this);
        }
        void ShowAll() const noexcept {
            cout << all << endl;
        }
    private:
        int all; 
        HealthFunc Healthcala;
};

class Game{
    public:
        int show(const GameCharacter&){
            cout << "Game\n";
        }
};

int main(){
    Game T;
    using std::placeholders::_1;
    GameCharacter H(::bind(&Game::show, T, _1)); //令人震撼 太完美了
    H.Healthfunc();
}