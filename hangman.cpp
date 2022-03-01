#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

const int MAX_BAD_GUESSWORD = 7;

int getRandomInt(int l,int r)
{
    return (rand()%(r - l + 1) + l);
}
string getRandomWord(const vector < string > &wordList)
{
    int len = wordList.size();
    int index = getRandomInt(1,len);
    return wordList[index-1];
}

vector < string > InitWordList()
{
    vector < string > wordList;
    ifstream file ("hangmanWordList.txt", ios::in);
    if(file.is_open())
    {
        while(!file.eof())
        {
            string word;
            file >> word;
            wordList.push_back(word);
        }
    }
    file.close();
    return wordList;
}
string InitGuessWord(int len)
{
    string guessWord = "";
    for(int i=0;i<len;i++)guessWord += "-";
    return guessWord;
}
void display(const string &secretWord, const string &guessWord, const int &badGuessWord)
{
    cout << "CorrectWord: " << secretWord << '\n';
}
void render(const string &guessWord, const string &secretWord, const int &badGuessWord)
{
    for(int i=0;i<=20;i++)cout << '\n';
    cout << "   ";
    for(int i=1;i<=13;i++)cout << "-";
    cout << '\n';
    cout << "   ";
    cout << "|";
    if(badGuessWord >= 1)
    {
        for(int i=1;i<=11;i++)cout << " ";
        cout << "|";
    }
    cout << '\n';
    cout << "   ";
    cout << "|";
    if(badGuessWord >= 2)
    {
        for(int i=1;i<=11;i++)cout << " ";
        cout << "0";
    }
    cout << '\n';
    cout << "   ";
    cout << "|";
    if(badGuessWord >= 3)
    {
        for(int i=1;i<=10;i++)cout << " ";
        cout << "/";
    }
    if(badGuessWord >= 4)
    {
        cout << "|";
    }
    if(badGuessWord >= 5)
    {
        cout <<"\\";
    }
    cout << '\n';
    cout << "   ";
    cout << "|";
    if(badGuessWord >= 6)
    {
        for(int i=1;i<=10;i++)cout << " ";
        cout << "/";
    }
    if(badGuessWord == 7)
    {
        cout << " \\";
    }
    cout << '\n';
    cout << "   |\n";
    cout << "-------";
    cout << '\n';
    cout << "CurrentWord: " << guessWord << "\t" << "CorrectWord: " << secretWord << "\t" << "BadGuessWord: " << badGuessWord << '\n';
}
bool contains(const char &input, const string &secretWord)
{
    return (secretWord.find_first_of(input) != string::npos);
}
void update(const char &input, const string &secretWord, string &guessWord)
{
    int len = guessWord.size();
    for(int i=0;i<len;i++)
    {
        if(secretWord[i] == input)
        {
            guessWord[i] = input;
        }
    }
}
bool gameOver(const string &secretWord, const string &guessWord, const int &badGuessWord)
{
    if(badGuessWord >= MAX_BAD_GUESSWORD)return true;
    if(secretWord == guessWord)return true;
    return false;
}
int main()
{
    srand(time(0));

    vector < string > wordList = InitWordList();
    string secretWord = getRandomWord(wordList);
    string guessWord = InitGuessWord(secretWord.size());
    int badGuessWord = 0;
    do
    {
        render(guessWord, secretWord, badGuessWord);
        char input;
        cout << "Character: ";
        cin >> input;
        cout << '\n';
        if(contains(input, secretWord))update(input, secretWord, guessWord);
        else badGuessWord++;
    } while(!gameOver(secretWord, guessWord, badGuessWord));
    render(guessWord, secretWord, badGuessWord);
    display(secretWord, guessWord, badGuessWord);
    if(badGuessWord >= 7)cout << "Game Over";
    else cout << "Congratulation !!!!";
    return 0;
}
