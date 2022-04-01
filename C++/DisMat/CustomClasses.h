class Pair{
    private:
        int x;
        int y;
    public:
        Pair(){
            x = 0;
            y = 0;
        }

        Pair(int X, int Y){
            x = X;
            y = Y;
        }

        Pair(const Pair& P){
            x = P.x;
            y = P.y;
        }

        int getX(){ return x; }
        int getY(){ return y; }
        
        bool operator==(const Pair& P){
            if(x == P.x && y == P.y || x == P.y && y == P.x)
                return true;
            return false;
        }
};