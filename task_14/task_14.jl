include("..\\libs\\FunctionsRobot.jl")


function krestWithPartitions!(r, dx::Integer = 0, dy::Integer = 0)

    R = CrossRobot(r, Coords(0, 0), true, dx, dy)
    back_path = BackPath(R)
    marks!(R)
    BackPath(r)
    back!(R, back_path)
end