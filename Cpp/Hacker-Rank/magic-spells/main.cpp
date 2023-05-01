#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {
    
  /* Enter your code here */
    Fireball *fire = nullptr;
    Frostbite *fros = nullptr;
    Thunderstorm *thunder = nullptr;
    Waterbolt *water = nullptr;
    Spell *jour = nullptr;
    if(fire = dynamic_cast<Fireball*>(spell); fire != nullptr) {
        fire->revealFirepower();
    } else if(fros = dynamic_cast<Frostbite*>(spell); fros != nullptr) {
        fros->revealFrostpower();
    } else if(thunder = dynamic_cast<Thunderstorm*>(spell); thunder != nullptr) {
        thunder->revealThunderpower();
    } else if(water = dynamic_cast<Waterbolt*>(spell); water != nullptr) {
        water->revealWaterpower();
    } else if(jour = dynamic_cast<Spell*>(spell); jour != nullptr) {
        int spell_pos;
        int jour_pos;
        int previous_jour_pos = 0;
        string sSpell = jour->revealScrollName();
        string sJournal = SpellJournal::journal;
        string retVal = "";
        int m = sSpell.length();
        int n = sJournal.length();
        int Arr[m + 1][n + 1];
        for(int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                Arr[i][j] = 0;
            }
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (sSpell[i - 1] == sJournal[j - 1]) {
                    Arr[i][j] = Arr[i - 1][j - 1] + 1;
                } else {
                    Arr[i][j] = max(Arr[i - 1][j], Arr[i][j -1]);
                }
            }
        }
        std::cout << Arr[m][n] << std::endl;
    }
}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
