#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node
{
    string Stack_op;
    string Direction;
    int current_row;
    int current_col;
    Node *next;
};

class Stack
{
private:
    Node *path;
    int stack_size;

public:
    Stack() : path(nullptr), stack_size(0) {}
    ~Stack()
    {
        while (!Empty())
            Pop();
    }
    bool Empty() { return stack_size == 0; }
    void Push(string op, string direct, int row, int col)
    {
        Node *new_node = new Node{op, direct, row, col, path};
        path = new_node;
        stack_size++;
    }
    void Pop()
    {
        if (Empty())
            return;
        Node *temp = path;
        path = path->next;
        delete temp;
        stack_size--;
    }
    Node *Top() { return Empty() ? nullptr : path; }
    int get_row() { return Top() ? Top()->current_row : -1; }
    int get_col() { return Top() ? Top()->current_col : -1; }
    string get_direction() { return Top() ? Top()->Direction : ""; }
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: ./Lab3 <input> <output>" << endl;
        return 1;
    }

    ifstream in(argv[1]);
    ofstream out(argv[2]);
    if (in.fail())
    {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    int n;
    in >> n;
    char **maze = new char *[n];
    for (int i = 0; i < n; i++)
    {
        maze[i] = new char[n];
        for (int j = 0; j < n; j++)
        {
            in >> maze[i][j];
        }
    }
    in.close();

    Stack S;
    if(maze[0][2] == '.')
    {
        S.Push("Push", "down", 0, 1);
        out << "Push right " << 0 << " " << 1 << endl;
        maze[0][1] = '+'; 
    }else if(maze[1][1] == '.')
    {
        S.Push("Push", "down", 0, 1);
        out << "Push down " << 0 << " " << 1 << endl;
        maze[0][1] = '+'; 
    }
    while (S.get_row() != n - 1 || S.get_col() != n - 2)
    {
        if (S.Empty())
        {
            out << "path not found" << endl;
            break;
        }

        int row = S.get_row();
        int col = S.get_col();
        bool moved = false;

        // Check directions in priority order: right > down > left > up
        if (col + 1 < n && maze[row][col + 1] == '.')
        {
            S.Push("Push", "right", row, col + 1);
            maze[row][col + 1] = '+';
            out << "Push right " << row << " " << col + 1 << endl;
            moved = true;
        }
        else if (row + 1 < n && maze[row + 1][col] == '.')
        {
            S.Push("Push", "down", row + 1, col);
            maze[row + 1][col] = '+';
            out << "Push down " << row + 1 << " " << col << endl;
            moved = true;
        }
        else if (col - 1 >= 0 && maze[row][col - 1] == '.')
        {
            S.Push("Push", "left", row, col - 1);
            maze[row][col - 1] = '+';
            out << "Push left " << row << " " << col - 1 << endl;
            moved = true;
        }
        else if (row - 1 >= 0 && maze[row - 1][col] == '.')
        {
            S.Push("Push", "up", row - 1, col);
            maze[row - 1][col] = '+';
            out << "Push up " << row - 1 << " " << col << endl;
            moved = true;
        }
        else
        {
            if(S.get_direction() == "right")
            {
                maze[row][col] = '*';
                out << "Pop right " << row << " " << col-1 << endl;
            }else if(S.get_direction() == "down")
            {
                maze[row][col] = '*';
                out << "Pop down " << row-1 << " " << col << endl;
            }else if(S.get_direction() == "left")
            {
                maze[row][col] = '*';
                out << "Pop left " << row << " " << col+1 << endl;
            }else if(S.get_direction() == "up")
            {
                maze[row][col] = '*';
                out << "Pop up " << row+1 << " " << col << endl;
            }
            S.Pop();
        }
    }

    // Output the maze
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(maze[i][j] == '*')
            {
                out << '.';
            }else
            {
                out << maze[i][j];
            }
        }
        out << endl;
    }

    // Clean up
    for (int i = 0; i < n; i++)
    {
        delete[] maze[i];
    }
    delete[] maze;
    out.close();

    return 0;
}