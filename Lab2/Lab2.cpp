#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

// 定義多項式節點結構，包含係數、次數和指向下一個節點的指針
class Poly
{
public:
    int coefficient; // 多項式項的係數
    int degree;      // 多項式項的次數
    Poly *next;      // 指向下一個多項式項的指針
};

// 找到鏈結串列的中點（使用快慢指針法）
Poly* findMiddle(Poly* head) {
    // 如果鏈結串列為空或只有一個節點，直接返回
    if (!head || !head->next) return head;
    Poly* slow = head;      // 慢指針，每次走一步
    Poly* fast = head->next; // 快指針，每次走兩步
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; // 返回中點節點
}

// 合併兩個已排序的鏈結串列（按 degree 遞減排序）
Poly* merge(Poly* left, Poly* right) {
    Poly dummy;         // 虛擬頭節點，用於構建結果鏈結串列
    Poly* tail = &dummy; // 尾指針，用於追加節點

    // 當左右兩邊都有節點時，比較 degree 並按遞減順序合併
    while (left && right) {
        if (left->degree >= right->degree) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    // 將剩餘的節點接到結果鏈結串列
    tail->next = left ? left : right;
    return dummy.next; // 返回合併後的鏈結串列頭
}

// 合併排序主函數（對鏈結串列按 degree 遞減排序）
Poly* mergeSort(Poly* head) {
    // 如果鏈結串列為空或只有一個節點，無需排序，直接返回
    if (!head || !head->next) return head;

    // 找到中點並分割鏈結串列
    Poly* mid = findMiddle(head);
    Poly* right = mid->next;
    mid->next = NULL; // 斷開鏈結串列，分成左右兩部分

    // 遞迴排序左右兩半
    Poly* leftSorted = mergeSort(head);
    Poly* rightSorted = mergeSort(right);

    // 合併排序結果
    return merge(leftSorted, rightSorted);
}

int main(int argc, char *argv[])
{
    ifstream in;
    in.open(argv[1]); // 打開輸入檔案
    if (in.fail())
    {
        cout << "Can't open the file" << endl;
        exit(1); // 檔案打開失敗則退出
    }
    string str;
    int co, deg;
    int value;
    int header = 0; // 用於控制多項式項輸出時的符號格式

    // 讀取第一行（通常是 "Poly1"）
    getline(in, str);

    // 創建第一個多項式鏈結串列的頭節點（此處僅分配空間，後續會覆蓋）
    Poly *head = new Poly();
    Poly *current = head;
    while (getline(in, str))
    {
        // 如果遇到 "Poly2"，停止讀取 Poly1
        if (str[0] == 'P')
        {
            break;
        }
        stringstream ss(str);
        ss >> co >> deg; // 從每一行讀取係數和次數

        current->next = new Poly(); // 創建新節點
        current = current->next;
        current->coefficient = co;
        current->degree = deg;
        current->next = NULL;
    }

    string tmp;

    // 創建第二個多項式鏈結串列的頭節點（此處僅分配空間，後續會覆蓋）
    Poly *head1 = new Poly();    
    Poly *current1 = head1;
    while (getline(in, str))
    {
        stringstream ss(str);
        ss >> tmp >> deg; // 讀取一行，可能是係數和次數，或 "x 值"
        if (tmp == "x")
        {
            value = deg; // 讀到 "x 值"，記錄值並停止讀取
            break;
        }
        else
        {
            co = stoi(tmp); // 將係數從字串轉為整數
        }
        current1->next = new Poly(); // 創建新節點
        current1 = current1->next;
        current1->coefficient = co;
        current1->degree = deg;
        current1->next = NULL;
    }

    // 對兩個多項式按次數（degree）遞減排序
    head = mergeSort(head);
    head1 = mergeSort(head1);

    // 輸出第一個多項式
    cout << "Polynomial 1:";
    current = head;
    header = 0;
    while (current != NULL)
    {
        if (current->coefficient != 0) // 忽略係數為 0 的項
        {
            // 根據 header 控制符號：首項正數無符號，負數加 " - "，非首項正數加 " + "，負數加 " - "
            if (header == 0 && current->coefficient < 0)
                cout << " -";
            else if (header == 0 && current->coefficient > 0)
                cout << " ";
            else if (header != 0 && current->coefficient > 0)
                cout << " + ";
            else if (header != 0 && current->coefficient < 0)
                cout << " - ";
            cout << abs(current->coefficient) << "x^" << current->degree;
            header++;
        }
        current = current->next;
    }
    cout << endl;

    // 輸出第二個多項式
    cout << "Polynomial 2:";
    current1 = head1;
    header = 0;
    while (current1 != NULL)
    {
        if (current1->coefficient != 0)
        {
            if (header == 0 && current1->coefficient < 0)
                cout << " -";
            else if (header == 0 && current1->coefficient > 0)
                cout << " ";
            else if (header != 0 && current1->coefficient > 0)
                cout << " + ";
            else if (header != 0 && current1->coefficient < 0)
                cout << " - ";
            cout << abs(current1->coefficient) << "x^" << current1->degree;
            header++;
        }
        current1 = current1->next;
    }
    cout << endl;

    // 加法：將兩個多項式相加
    cout << "Addition:";
    current = head;
    current1 = head1;
    header = 0;
    while (true)
    {
        int signdeter = 0; // 用於記錄當前項的係數

        // 當 Poly2 結束，處理 Poly1 剩餘項
        if (current1 == NULL && current != NULL)
        {
            signdeter = current->coefficient;
            if (signdeter != 0)
            {
                if (header == 0 && signdeter < 0)
                    cout << " -";
                else if (header == 0 && signdeter > 0)
                    cout << " ";
                else if (header != 0 && signdeter > 0)
                    cout << " + ";
                else if (header != 0 && signdeter < 0)
                    cout << " - ";
                cout << abs(current->coefficient) << "x^" << current->degree;
                header++;
            }
            current = current->next;
        }
        // 當 Poly1 結束，處理 Poly2 剩餘項
        else if (current == NULL && current1 != NULL)
        {
            signdeter = current1->coefficient;
            if (signdeter != 0)
            {
                if (header == 0 && signdeter < 0)
                    cout << " -";
                else if (header == 0 && signdeter > 0)
                    cout << " ";
                else if (header != 0 && signdeter > 0)
                    cout << " + ";
                else if (header != 0 && signdeter < 0)
                    cout << " - ";
                cout << abs(current1->coefficient) << "x^" << current1->degree;
                header++;
            }
            current1 = current1->next;
        }
        // 當兩個多項式都有項時，比較次數
        else if (current != NULL && current1 != NULL)
        {
            if (current1->degree == current->degree) // 次數相同，係數相加
            {
                signdeter = current->coefficient + current1->coefficient;
                if (signdeter != 0)
                {
                    if (header == 0 && signdeter < 0)
                        cout << " -";
                    else if (header == 0 && signdeter > 0)
                        cout << " ";
                    else if (header != 0 && signdeter > 0)
                        cout << " + ";
                    else if (header != 0 && signdeter < 0)
                        cout << " - ";
                    cout << abs(current->coefficient + current1->coefficient) << "x^" << current->degree;
                    header++;
                }
                current1 = current1->next;
                current = current->next;
            }
            else if (current1->degree > current->degree) // Poly2 次數較大，優先輸出
            {
                signdeter = current1->coefficient;
                if (signdeter != 0)
                {
                    if (header == 0 && signdeter < 0)
                        cout << " -";
                    else if (header == 0 && signdeter > 0)
                        cout << " ";
                    else if (header != 0 && signdeter > 0)
                        cout << " + ";
                    else if (header != 0 && signdeter < 0)
                        cout << " - ";
                    cout << abs(current1->coefficient) << "x^" << current1->degree;
                    header++;
                }
                current1 = current1->next;
            }
            else if (current1->degree < current->degree) // Poly1 次數較大，優先輸出
            {
                signdeter = current->coefficient;
                if (signdeter != 0)
                {
                    if (header == 0 && signdeter < 0)
                        cout << " -";
                    else if (header == 0 && signdeter > 0)
                        cout << " ";
                    else if (header != 0 && signdeter > 0)
                        cout << " + ";
                    else if (header != 0 && signdeter < 0)
                        cout << " - ";
                    cout << abs(current->coefficient) << "x^" << current->degree;
                    header++;
                }
                current = current->next;
            }
        }
        // 當兩個多項式都處理完畢，退出迴圈
        if (current1 == NULL && current == NULL)
            break;
    }
    cout << endl;

    // 減法：Poly1 減去 Poly2
    cout << "Subtraction:";
    current = head;
    current1 = head1;
    header = 0;
    while (true)
    {
        int signdeter = 0;

        if (current1 == NULL && current != NULL)
        {
            signdeter = current->coefficient;
            if (signdeter != 0)
            {
                if (header == 0 && signdeter < 0)
                    cout << " -";
                else if (header == 0 && signdeter > 0)
                    cout << " ";
                else if (header != 0 && signdeter > 0)
                    cout << " + ";
                else if (header != 0 && signdeter < 0)
                    cout << " - ";
                cout << abs(current->coefficient) << "x^" << current->degree;
                header++;
            }
            current = current->next;
        }
        else if (current == NULL && current1 != NULL)
        {
            signdeter = -current1->coefficient; // 減法時，Poly2 的係數取負
            if (signdeter != 0)
            {
                if (header == 0 && signdeter < 0)
                    cout << " -";
                else if (header == 0 && signdeter > 0)
                    cout << " ";
                else if (header != 0 && signdeter > 0)
                    cout << " + ";
                else if (header != 0 && signdeter < 0)
                    cout << " - ";
                cout << abs(current1->coefficient) << "x^" << current1->degree;
                header++;
            }
            current1 = current1->next;
        }
        else if (current != NULL && current1 != NULL)
        {
            if (current1->degree == current->degree)
            {
                signdeter = current->coefficient - current1->coefficient;
                if (signdeter != 0)
                {
                    if (header == 0 && signdeter < 0)
                        cout << " -";
                    else if (header == 0 && signdeter > 0)
                        cout << " ";
                    else if (header != 0 && signdeter > 0)
                        cout << " + ";
                    else if (header != 0 && signdeter < 0)
                        cout << " - ";
                    cout << abs(current->coefficient - current1->coefficient) << "x^" << current->degree;
                    header++;
                }
                current1 = current1->next;
                current = current->next;
            }
            else if (current1->degree > current->degree)
            {
                signdeter = -current1->coefficient;
                if (signdeter != 0)
                {
                    if (header == 0 && signdeter < 0)
                        cout << " -";
                    else if (header == 0 && signdeter > 0)
                        cout << " ";
                    else if (header != 0 && signdeter > 0)
                        cout << " + ";
                    else if (header != 0 && signdeter < 0)
                        cout << " - ";
                    cout << abs(current1->coefficient) << "x^" << current1->degree;
                    header++;
                }
                current1 = current1->next;
            }
            else if (current1->degree < current->degree)
            {
                signdeter = current->coefficient;
                if (signdeter != 0)
                {
                    if (header == 0 && signdeter < 0)
                        cout << " -";
                    else if (header == 0 && signdeter > 0)
                        cout << " ";
                    else if (header != 0 && signdeter > 0)
                        cout << " + ";
                    else if (header != 0 && signdeter < 0)
                        cout << " - ";
                    cout << abs(current->coefficient) << "x^" << current->degree;
                    header++;
                }
                current = current->next;
            }
        }
        if (current1 == NULL && current == NULL)
            break;
    }
    cout << endl;

    // 乘法：計算 Poly1 和 Poly2 的乘積
    cout << "Multiplication:";
    Poly *result = NULL;
    Poly *tail = NULL;

    // 遍歷 Poly1 和 Poly2 的每一項，計算乘積
    for (Poly *p1 = head; p1 != NULL; p1 = p1->next)
    {
        for (Poly *p2 = head1; p2 != NULL; p2 = p2->next)
        {
            int new_coef = p1->coefficient * p2->coefficient; // 係數相乘
            int new_deg = p1->degree + p2->degree;           // 次數相加

            // 將新項插入結果鏈結串列，按次數遞減排序
            Poly *curr = result;
            Poly *prev = NULL;
            while (curr != NULL && curr->degree > new_deg)
            {
                prev = curr;
                curr = curr->next;
            }
            if (curr != NULL && curr->degree == new_deg)
            {
                curr->coefficient += new_coef; // 同次數項係數相加
            }
            else
            {
                Poly *new_node = new Poly();
                new_node->coefficient = new_coef;
                new_node->degree = new_deg;
                new_node->next = curr;
                if (prev == NULL)
                    result = new_node;
                else
                    prev->next = new_node;
            }
        }
    }

    // 輸出乘法結果
    header = 0;
    Poly *curr = result;
    while (true)
    {
        if (curr != NULL)
        {
            int signdeter = curr->coefficient;
            if (signdeter != 0)
            {
                if (header == 0)
                {
                    if (signdeter > 0)
                        cout << " ";
                    else
                        cout << " -";
                    header++;
                }
                else
                {
                    if (signdeter > 0)
                        cout << " + ";
                    else
                        cout << " - ";
                }
                cout << abs(curr->coefficient) << "x^" << curr->degree;
            }
            curr = curr->next;
        }
        if (curr == NULL)
            break;
    }
    cout << endl;

    // 計算 Poly1 在 x = value 時的值
    cout << "Evaluation of Polynomial 1 at x = " << value << " is: ";
    int sum = 0;
    current = head;
    while (current != NULL)
    {
        sum += current->coefficient * pow(value, current->degree); // 計算每一項的值並累加
        current = current->next;
    }
    cout << sum << endl;

    // 計算 Poly2 在 x = value 時的值
    sum = 0;
    cout << "Evaluation of Polynomial 2 at x = " << value << " is: ";
    current1 = head1;
    while (current1 != NULL)
    {
        sum += current1->coefficient * pow(value, current1->degree);
        current1 = current1->next;
    }
    cout << sum << endl;

    // 關閉檔案
    in.close();

    return 0;
}