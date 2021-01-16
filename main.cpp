#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;
// 행맨에서 위아래 경계는 필요가 없다, 좌우 경계만 있으면 된다.
void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
    if (printTop)
    {
        cout << "+---------------------------------+" << endl;
        cout << "|"; // 메세지 시작지점 
    }
    else {
        cout << "|";
    }
    bool front = true;
    for (int i = message.length(); i < 33; i++) // 33은 위의 ----의 갯수 
    {
        if (front) // front라면 빈공간과 message 출력 
        {
            message = " " + message;
        }
        else { // back
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();
    if (printBottom)
    {
        cout << "|" << endl; // 메세지 시작지점 
        cout << "+---------------------------------+" << endl;
    }
    else {
        cout << "|" << endl;
    }
}

void DrawHangman(int guessCount = 0)
{
    if (guessCount >= 1)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 2)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 3)
        PrintMessage("O", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 4) // 딱 4일때만, 몸체는 / -> /| -> /|\ 순으로 그려야 해서 
        PrintMessage("/  ", false, false); // else는 없음 빈공간은 출력하고싶지 않음

    if (guessCount == 5) // 딱 5 일때만 
        PrintMessage("/| ", false, false); // else는 없음 빈공간은 출력하고싶지 않음

    if (guessCount >= 6) // 6아상부터는 몸체 다 보여줌 
        PrintMessage("/|\\", false, false); // escape문자 조심 
    else
        PrintMessage("", false, false);

    if (guessCount >= 7)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 8)
        PrintMessage("/", false, false);

    if (guessCount >= 9) // 9아상부터는 몸체 다 보여줌 
        PrintMessage("/\\", false, false); // escape문자 조심 
    else
        PrintMessage("", false, false);

}

void PrintLetters(string input, char from, char to)
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos) // 만약 input이 current character를 갖고있다면
        { // 찾지못한 character
            s += i;
            s += " ";
        }
        else {
            s += "  "; // 이미찾은 character는 빈공간으로 출력 
        }
    }
    PrintMessage(s, false, false);
}

void PrintAvailableLetters(string taken) // 출력 wrapper함수 
{
    PrintMessage("Available Letters");
    PrintLetters(taken, 'A', 'M');
    PrintLetters(taken, 'N', 'Z');
}

bool PrintWordAndCheckWin(string word, string guessed) // guess아님  guessed 맞음 
{
    bool won = true;
    string s;
    for (int i(0); i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        { // 찾지 못했다면 
            won = false;
            s += "_ "; // 틀린 character는 보여주지 않고 placeholder로 출력 
        }
        else {
            s += word[i]; // 맞춘 character는 출력 
            s += " ";
        }
    }
    PrintMessage(s, false);

    return won;
}

string LoadRandomWord(string path) // words.txt안의 렌덤문자 선택
{
    int linecount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open()) // reader 열기
    {
        while (std::getline(reader, word))
        {// 한줄씩 읽어들여야함
            v.push_back(word); // 단어를 vector로 
        }
        int randomLine = rand() % v.size(); //0부터 라인수까지의 수 반환

        word = v.at(randomLine);
        reader.close(); // reader 닫기 
    }
    return word;
}

int TriesLeft(string word, string guessed) // try한 횟수 
{
    int error = 0;
    for (int i(0); i < guessed.length(); i++)
    {
        if (word.find(guessed[i]) == string::npos)
        {
            error++;
        }
    }
    return error;
}

int main(void)
{
    srand(time(0)); // seed값 시간으로 설정
    string guesses;
    string wordToGuess;

    wordToGuess = LoadRandomWord("words.txt");
    int tries = 0;
    bool win = false;
    do {
        system("cls"); // clear screen
        PrintMessage("HANG_MAN");
        DrawHangman(tries); // 사람그려주는 
        PrintAvailableLetters(guesses);
        PrintMessage("Guess the word");
        win = PrintWordAndCheckWin(wordToGuess, guesses);

        if (win)
            break;

        char x;
        cout << ">"; cin >> x;
        if (guesses.find(x) == string::npos)
        { // 해당 character가 없다면 
            guesses += x;
        }

        tries = TriesLeft(wordToGuess, guesses);

    } while (tries < 10);

    if (win)
        PrintMessage("YOU WIN!");
    else
        PrintMessage("GAME OVER");

    system("pause");

    getchar();

    return 0;
}

/*
+---------------------------------+
|             HANG MAN            |
+---------------------------------+
|               |                 |
|               |                 |
|               O                 |
|              /|\                |
|               |                 |
|              / \                |
|         +----------+            |
|         |          |            |
+---------------------------------+
|        Available letters        |
+---------------------------------+
|     A B C D E F G H I J K L M   |
|     N O P Q R S T U V W X Y Z   |
+---------------------------------+
|         Guess the word          |
+---------------------------------+
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |
+---------------------------------+
>
*/