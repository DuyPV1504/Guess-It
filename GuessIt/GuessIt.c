#include	<iostream>
#include	<cstdlib>
using namespace	std;

void welcomeToGuessIt();            //Gioi thieu tro choi
void manyAttempt();                 //choi nhieu lan
int difficultyLevel();              //lua chon do kho cho game
void playGuessIt();                 //Bat dau tro choi
int generateRandomNumber();         //tao so ngau nhien
int getPlayerGuess();               //lay so nguoi choi
void printAnswer(int number, int randomNumber);         //in ket qua doan

int main()
{
    welcomeToGuessIt();
    manyAttempt();
    return 0;
}

void welcomeToGuessIt()
{
    cout << " Chao mung den voi game Doan So" << endl
         << "May tinh chon 1 so ngau nhien tu 1-100, hay doan so do!" << endl
         << "Moi lan choi ban co so lan doan nhat dinh, tro choi ket thuc khi doan dung hoac het luot" << endl << endl;
}

int difficultyLevel()
{
    int dokho;
    cout << "Vui long lua chon do kho cho game: " << endl
        << "Easy :  bam 1" << endl
        << "Medium : bam 2" << endl
        << "Hard :  bam 3 "<< endl
        << "Do kho ban muon choi la: ";
    cin >> dokho;
    if(dokho == 1)
    {
        cout << endl << "Muc do Easy, ban co 7 luot doan!" << endl;
        return 7;
    }
    else if(dokho == 2)
    {
        cout << endl << "Muc do Medium, ban co 5 luot doan." << endl;
        return 5;
    }
    else if(dokho == 3)
    {
        cout << endl << "Muc do Hard, ban co 3 luot doan." << endl;
        return 3;
    }
    else if(dokho == 0)
    {
        cout << endl << "Chuc mung ban mo khoa do kho Impossoble, ban co 1 luot doan." << endl;
        return 1;
    }
    else
    {
        int traloi;
        cout << "So ban chon khong hop le!" << endl << endl
            << "Tiep tuc choi bam 1, ket thuc bam phim bat ki " << endl;
        cin >> traloi;
        if(traloi == 1) {return difficultyLevel();}
        else exit(0);
    }
}

void manyAttempt()
{
    playGuessIt();
    int traloi;
    cout << "Choi lai choi bam 1, ket thuc bam 0" << endl;
    cin >> traloi;
    if (traloi == 1) {manyAttempt();}
    else if(traloi == 0) {cout << "Cam on ban da trai nghiem Doan So 1.5. Hen gap lai vao nhung tro choi khac! <3";}
    else {cout << "So ban chon khong hop le! Tro choi se tu dong ket thuc " << endl;}
}

void playGuessIt()
{
    int guessAttempt = 0;
    int randomNumber = generateRandomNumber();
    int number;
    int maxAttempt = difficultyLevel();

    do {
        guessAttempt++;
        number = getPlayerGuess();
        printAnswer(number, randomNumber);
    }
    while(number != randomNumber and guessAttempt < maxAttempt);
    if (number != randomNumber)
    {
         cout << endl << "Ban da het luot doan! So can tim la : " << randomNumber << endl << endl
              << endl << "...Game Over..." << endl << endl;
    }
    else cout << endl << "Ban doan dung sau " << guessAttempt << " lan." << endl << endl;
}

int generateRandomNumber()
{
    srand(time(0));
    return rand() % 100 + 1;
}

int getPlayerGuess()
{
    int playerNumber;
    cout << endl << "Nhap so ban doan trong khoang 1 den 100: ";
    cin >> playerNumber;
    return playerNumber;
}

void printAnswer(int number, int randomNumber)
{
    if (number < 1 or number > 100){
        cout << "So ban chon khong hop le, vui long chon so trong khoang 1-100" << endl << endl;
    }
    else if(number > randomNumber){
        cout << "So ban chon to hon so can doan." << endl;
    }
    else if(number < randomNumber) {
        cout << "So ban chon be hon so can doan." << endl;
    }
    else cout << "Chuc mung! Ban da doan dung." << endl;
}
