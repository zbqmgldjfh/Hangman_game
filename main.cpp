#include <iostream>
#include <string>

using namespace std;
// 행맨에서 위아래 경계는 필요가 없다, 좌우 경계만 있으면 된다.
void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
    if(printTop)
    {
        cout << "+---------------------------------+" << endl;
        cout << "|"; // 메세지 시작지점 
    }else{
        cout << "|";
    }
    bool front = true;
    for(int i = message.length(); i < 33; i++) // 33은 위의 ----의 갯수 
    {
        if(front) // front라면 빈공간과 message 출력 
        {
            message = " " + message;
        }else{ // back
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();
    if(printBottom)
    {
        cout << "|" << endl; // 메세지 시작지점 
        cout << "+---------------------------------+" << endl;
    }else{
        cout << "|" << endl;
    }
}

void DrawHangman(int guessCount = 0)
{
    if(guessCount >= 1)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);
    
    if(guessCount >= 2)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if(guessCount >= 3)
        PrintMessage("O", false, false);
    else
        PrintMessage("", false, false);
    
    if(guessCount == 4) // 딱 4일때만, 몸체는 / -> /| -> /|\ 순으로 그려야 해서 
        PrintMessage("/", false, false); // else는 없음 빈공간은 출력하고싶지 않음

    if(guessCount == 5) // 딱 5 일때만 
        PrintMessage("/|", false, false); // else는 없음 빈공간은 출력하고싶지 않음

    if(guessCount >= 6) // 6아상부터는 몸체 다 보여줌 
        PrintMessage("/|\\", false, false); // escape문자 조심 
    else
        PrintMessage("", false, false);

    if(guessCount >= 7)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if(guessCount == 8)
        PrintMessage("/", false, false);

    if(guessCount >= 9) // 9아상부터는 몸체 다 보여줌 
        PrintMessage("/\\", false, false); // escape문자 조심 
    else
        PrintMessage("", false, false);

}

void PrintLetters(string input, char from, char to)
{
    string s;
    for(char i = from; i <= to; i++)
    {
        if(input.find(i) == string::npos) // 만약 input이 current character를 갖고있다면
        { // 찾지못한 character
            s += i;
            s += " ";
        }else{
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
    for(int i(0); i < word.length(); i++)
    {
        if(guessed.find(word[i]) == string::npos)
        { // 찾지 못했다면 
            won = false;
            s += "_ "; // 틀린 character는 보여주지 않고 placeholder로 출력 
        }else{
            s += word[i]; // 맞춘 character는 출력 
            s += " ";
        }
    }
    PrintMessage(s, false);

    return won;
}

int main(void)
{
    string guesses = "JIWOO";
    PrintMessage("HANG MAN");
    DrawHangman(9);
    PrintAvailableLetters(guesses);
    PrintMessage("Guess the word");
    PrintWordAndCheckWin("JIWOOS", guesses);
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