# Hangman_game
 
## 컴퓨터공학 포토폴리오 김지우

<img src = "https://user-images.githubusercontent.com/60593969/104802075-f603d000-5813-11eb-9cb1-9092c7824692.gif" width="700px">

위의 영상을 보면 사람 팔 한부분이 \가 나와야하는데 won단위표시로 나옵니다. window가 한글이라 그렇다고 합니다. 찾아본 바로는 수정할 방법이 없었습니다.

**간단한 C++ 연습용 게임 만들기**

## Code 설명

### 출력문 logic   
하나의 출력 wrapper function을 만들어 위, 아래 경계와, 양쪽여백을 한번에 control가능한 함수를 만들어 활용하였습니다.
```C
// 위, 아래 border는 기본으로 true입니다. 사용하지 않고싶다면 flase를 넘겨주면됩니다.
void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
    if (printTop) // 위쪽 경계를 만들고 싶다면, printTop = true 인해 조건문 안을 실행
    {
        cout << "+---------------------------------+" << endl; // 총 33글자
        cout << "|"; // 메세지 시작지점 
    }
    else { //  printTop = flase 인 경우 그냥 왠쪽 경계만 출력
        cout << "|";
    }
    bool front = true; // flag 초기화
    for (int i = message.length(); i < 33; i++) // 33은 위의 ----의 갯수 
    {
        if (front) // front라면 빈공간과 message 출력 
        {
            message = " " + message;
        }
        else { // back이라면 message먼저 출력후 빈공간
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str(); // message 출력
    if (printBottom)
    {
        cout << "|" << endl; // 오른쪽 경계면 출력 
        cout << "+---------------------------------+" << endl; // 하단부 경계 출력
    }
    else {
        cout << "|" << endl;
    }
}
```
**결 과**

<img src = "images/1.PrintMessage.png" width="400px">

###
