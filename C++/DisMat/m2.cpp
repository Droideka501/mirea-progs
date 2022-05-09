#include <iostream>
#include <vector>
#include <queue>

template <class T>
void vectorMatrixPrint(const std::vector<std::vector<T>> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].size() == 0)
        {
            std::cout << "empty" << std::endl;
        }
        else
        {
            for (int j = 0; j < v[i].size(); j++)
            {
                std::cout << v[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

class Pair
{
private:
    int x;
    int y;

public:
    Pair(int X = 0, int Y = 0)
    {
        x = X;
        y = Y;
    }

    Pair(const Pair &P)
    {
        x = P.x;
        y = P.y;
    }

    int getX() { return x; }
    int getY() { return y; }
    bool operator==(const Pair &P) { return (x == P.x && y == P.y); }
    void printPair()
    {
        std::cout << x << " " << y << std::endl;
    }
};

void rewriter(std::vector<std::vector<char>> &v, int i, int j, int height, int width, char antitype, bool &flag)
{
    std::queue<Pair> q;
    Pair start = Pair(i, j);
    q.push(start);

    while (!q.empty())
    {
        Pair p = q.front();
        q.pop();
        v[p.getX()][p.getY()] = '-';
        if (p.getX() + 1 < height)
        {
            if (v[p.getX() + 1][p.getY()] != '-')
            {
                if (v[p.getX() + 1][p.getY()] == antitype)
                    flag = true;
                q.push(Pair(p.getX() + 1, p.getY()));
            }
        }
        if (p.getX() - 1 > 0)
        {
            if (v[p.getX() - 1][p.getY()] != '-')
            {
                if (v[p.getX() - 1][p.getY()] == antitype)
                    flag = true;
                q.push(Pair(p.getX() - 1, p.getY()));
            }
        }
        if (p.getY() + 1 < width)
        {
            if (v[p.getX()][p.getY() + 1] != '-')
            {
                if (v[p.getX()][p.getY() + 1] == antitype)
                    flag = true;
                q.push(Pair(p.getX(), p.getY() + 1));
            }
        }
        if (p.getY() - 1 > 0)
        {
            if (v[p.getX()][p.getY() - 1] != '-')
            {
                if (v[p.getX()][p.getY() - 1] == antitype)
                    flag = true;
                q.push(Pair(p.getX(), p.getY() - 1));
            }
        }
    }
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<char>> field(n, std::vector<char>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cin >> field[i][j];
        }
    }
    int count_S = 0;
    int count_XS = 0;
    int count_X = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (field[i][j] == 'S')
            {
                bool flag = false;
                count_S++;
                rewriter(field, i, j, n, m, 'X', flag);
                if (flag)
                {
                    count_S--;
                    count_XS++;
                }
            }
            if (field[i][j] == 'X')
            {
                bool flag = false;
                count_X++;
                rewriter(field, i, j, n, m, 'S', flag);
                if (flag)
                {
                    count_X--;
                    count_XS++;
                }
            }
        }
    }
    std::cout << count_S << " " << count_XS << " " << count_X;
}