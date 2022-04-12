

class Pair{
    private:
        int x;
        int y;
    public:
        Pair(int X = 0, int Y = 0){
            x = X;
            y = Y;
        }

        Pair(const Pair& P){
            x = P.x;
            y = P.y;
        }

        int getX(){ return x; }
        int getY(){ return y; }
        bool operator==(const Pair& P){ return (x == P.x && y == P.y || x == P.y && y == P.x); }
};