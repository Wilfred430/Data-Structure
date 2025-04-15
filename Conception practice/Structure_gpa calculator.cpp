#include<iostream>
#include<map>
#include<cstring>
#include<sstream>
#include<vector>
#include<iomanip>
using namespace std;

struct Gpa
{
    map<string,double> m{{"A+",4.3},{"A",4.0},{"A-",3.7},{"B+",3.3},{"B",3.0},{"B-",2.7},{"C+",2.3},{"C",2.0},{"C-",1.7},{"D",1.0},{"E",0},{"X",0}};
    double gpa = 0;
    double total_credit=0;
    vector<double> credit;
    vector<string> grade;
};
                                                                                         
int main()
{
    string line;
    Gpa mine;
    int tmp_credit;
    string tmp_grade;

    cout << "請輸入你的學分/等第，並用空格隔開每個部份(停止在學分為零) : ";
    while(cin >> tmp_credit)
    {
        if(tmp_credit == 0) break;
        cin >> tmp_grade;
        mine.credit.push_back(tmp_credit);
        mine.grade.push_back(tmp_grade);
    }
    for(int i=0;i<mine.credit.size();i++)
    {
        if(mine.m.find(mine.grade[i]) == mine.m.end())
        {
            cout << "有不合法的輸入(等第輸入錯誤)!" << endl;
            break;
        }else
        {
            mine.gpa += mine.credit[i] * mine.m[mine.grade[i]];
            mine.total_credit += mine.credit[i];
        }
    }

    cout << "您的GPA為 : " << fixed << setprecision(3) << mine.gpa/mine.total_credit << endl;

    return 0;
}