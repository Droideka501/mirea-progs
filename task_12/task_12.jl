include("..\\libs\\FunctionsRobot.jl")

function modifyChess!(r, N::Integer)
    back_path = BackPath(r, (Nord, West))
    R = NChessRobot(r, Coords(0, 0), N)
    marks!(R, (Sud, Ost))
    back!(R, back_path)
end
     

