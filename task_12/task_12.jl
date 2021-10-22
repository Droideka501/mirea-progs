include("..\\libs\\FunctionsRobot.jl")

robot = Robot(10, 10, animate = true)

function modifyChess!(r::Robot, N::Integer)
    back_path = BackPath(r, (Nord, West))
    R = NChessRobot(r, Coords(0, 0), N)
    marks!(R, (Sud, Ost))

    back!(r, back_path)
end

modifyChess!(robot, 3)        

