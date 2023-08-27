#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
using namespace std;

class Display //Class 1
{
protected :
	string name;
    char ph[10];
    int age;
public :
    void printMessageCenter(const char *message);
    void headMessage(const char *message);
    void welcomeMessage();
    void drawLine(int n, char symbol);
    void rules();
    void getname();
};

class player : public Display //Class 2
{
protected :
	static int deposite_m;
    int guess_num;
    int betting_m;

public :
    void set_deposite_m();
    void bettingamount();
    virtual void guess(){};
    virtual int random(){};
    virtual void win(){};
    void loss();
    
    friend void start_game(player *p);
};

class rand_1 : public player //Class 3
{
public : 
	int random()
{
    srand(time(0));
    return 1 + rand() % 10;
}
	void guess()
{
    int num;
    do
    {
        cout << "\n\n\tGuess your number to bet between 1 to 10 :";
        cin >> guess_num;
        if (guess_num <= 0 || guess_num > 10)
            cout << "\n\n\tPlease check the number!! should be between 1 to 10\n"
                 << "\n\tRe-enter the number\n ";
    } while (guess_num <= 0 || guess_num > 10);
}
	void win()
	{
	    int random_num, rem_am;
	    rem_am = deposite_m - betting_m;
	    cout << "\n\n\tGood Luck !! you won" << endl;
	    betting_m = betting_m * 10;
	    cout << "\n\n\tYour winning amount is : " << betting_m << endl;
	    deposite_m = rem_am + betting_m;
	    cout << "\n\n\tYour total money in your Wallet : " << deposite_m << endl;
	}	
};

class rand_2 : public player //Class 4
{
public :
	int random()
{
    srand(time(0));
    return 1 + rand() % 100;
}
	void guess()
{
    int num;
    do
    {
        cout << "\n\n\tGuess your number to bet between 1 to 100 :";
        cin >> guess_num;
        if (guess_num <= 0 || guess_num > 100)
            cout << "\n\n\tPlease check the number!! should be between 1 to 100\n"
                 << "\n\tRe-enter the number\n ";
    } while (guess_num <= 0 || guess_num > 100);
}
	void win()
	{
	    int random_num, rem_am;
	    rem_am = deposite_m - betting_m;
	    cout << "\n\n\tGood Luck !! you won" << endl;
	    betting_m = betting_m * 20;
	    cout << "\n\n\tYour winning amount is : " << betting_m << endl;
	    deposite_m = rem_am + betting_m;
	    cout << "\n\n\tYour total money in your Wallet : " << deposite_m << endl;
	}
};

void player::set_deposite_m()
{
	headMessage("SET INITIAL DEPOSIT AMOUNT");
    do
    {
        cout << "\n\n\tEnter deposite amount to play game : $";
        cin >> deposite_m;
        if (deposite_m < 0)
        {
            cout << "\n\n\tPlease Enter valid amount to play the game !!";
        }

    } while (deposite_m < 0);
}

void player::bettingamount()
{
    headMessage("SET BET AMOUNT");
    do
    {

        cout << "\n\n\tEnter amount money to bet : $";
        cin >> betting_m;

        if (betting_m > deposite_m)
        {
            cout << "\n\n\tYour wallet money is : $" << deposite_m;
            cout << "\n\n\tYour betting amount is greater than your current balance\n\n";
        }

    } while (betting_m > deposite_m);
}

void player::loss()
{

    cout << "\n\n\tBad luck this time !! you lost " << endl;
    cout << "\n\n\tCorrect number was : " << random() << endl;
    deposite_m = deposite_m - betting_m;
    cout << "\n\n\tYour remaining amount is : " << deposite_m << endl;
    cout << "\n\n";
}

void start_game(player *p) 
{
	char choice;
	rand_1 r1;
	rand_2 r2;
    int random_num, rem_am;
    char ch;
    do
    {
    	p->headMessage("SELECT AN OPTION");
    	cout<<"\n\n\tT/t : Guess number between 1 to 10";
    	cout<<"\n\tH/h : Guess number between 1 to 100";
    	again : cout<<"\n\n\tEnter your choice (H/T) :";
    	cin>>choice;
    	switch(choice)
    	{
    		case 't' :	
    		case 'T' : p= &r1; 
			break;
			case 'h' :
			case 'H' : p= &r2;
			break;
			default  : cout<<"\n\n\tEnter correct choice.......";
					   goto again;	
    		
    	}
		
        p->bettingamount();
        p->guess();
        
        random_num = p->random();

        (random_num == p->guess_num) ? p->win() : p->loss();

        if (p->deposite_m == 0)
        {
            break;
        }

        cout << "\n\n\t--->Do you want to play aganin(y/n) :  ";
        cin >> ch;
        cout << "\n\n";
    } while (ch == 'y');
    cout << "\n\n\n\t";
    p->drawLine(70, '=');
    cout << "\n\n\tThanks for playing game. Your balance amount is $" << p->deposite_m << "\n\n\t";
    p->drawLine(70, '=');
    
} 
//definition of static data member
int player::deposite_m;

int main()
{
    player p;
    p.welcomeMessage();
    p.rules();
	p.getname();
    p.set_deposite_m();	
    start_game(&p);
    
}

void Display::getname()
{
	headMessage("PLAYER DETAILS");
	cout<<"\n\n\tEnter your name : ";
	cin>>name;
	cout<<"\n\n\tEnter your age :";
	cin>>age;
	cout<<"\n\n\tEnter your phone number :";
	cin>>ph;
}

void Display::drawLine(int n, char symbol)
{
    for (int i = 0; i < n; i++)
        cout << symbol;
    cout << "\n";
}

void Display::rules()
{
    headMessage("RULES OF THE GAME");
    cout << "\n\n\n\t";
    drawLine(80, '-');
    cout<<"\tCASE 1:\n";
    cout << "\t\t1. Choose any number between 1 to 10\n";
    cout << "\t\t   If you win you will get 10 times of money you bet\n";
    cout<<"\tCASE 2:\n";
    cout << "\t\t2. Choose any number between 1 to 100\n";
    cout << "\t\t   If you win you will get 20 times of money you bet\n";
    cout << "\n\t\t3. If you bet on wrong number you will lose your betting amount\n\n\t";
    drawLine(80, '-');
}
// Align the message
void Display::printMessageCenter(const char *message)
{
    int len = 0;
    int pos = 0;
    // calculate how many space need to print
    len = (76 - strlen(message)) / 2;
    cout << "\t\t\t";
    for (pos = 0; pos < len; pos++)
    {
        // print space
        cout << " ";
    }
    // print message
    cout << message;
}
// Head message
void Display::headMessage(const char *message)
{
    //system("cls");
    cout<<"\n\n\n";
    cout << "\t\t\t###########################################################################";
    cout << "\n\t\t\t############                                                   ############";
    cout << "\n\t\t\t############             Casino Game Project in C++            ############";
    cout << "\n\t\t\t############                                                   ############";
    cout << "\n\t\t\t###########################################################################";
    cout << "\n\t\t\t----------------------------------------------------------------------------\n";
    printMessageCenter(message);
    cout << "\n\t\t\t----------------------------------------------------------------------------";
}
// Display message
void Display::welcomeMessage()
{

    cout << "\n\n\n\n\n";
    cout << "\n\t\t\t";
	drawLine(75, '*');
    cout << "\n\t\t\t               =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout << "\n\t\t\t               =                                           =";
    cout << "\n\t\t\t               =                    WELCOME                =";
    cout << "\n\t\t\t               =                      TO                   =";
    cout << "\n\t\t\t               =                  CASINO GAME              =";
    cout << "\n\t\t\t               =                                           =";
    cout << "\n\t\t\t               =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    cout << "\n\t\t\t";
	drawLine(75, '*');
    cout << "\n\n\n\t\t\t Enter any key to continue.....";
    getchar();
}
