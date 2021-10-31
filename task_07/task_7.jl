include("..\\libs\\FunctionsRobot.jl")

function chessDesk!(r)
    back_path = BackPath(r, (Nord, West))
    R = ChessRobot(r, iseven(numSteps(back_path)))
    marks!(R, (Sud, Ost))
    BackPath(R, (Nord, West))
    back!(R, back_path)
    
end