include("..\\libs\\FunctionsRobot.jl")

"""

"""
function anyKrest!(r, dx::Integer = 1, dy::Integer = 1)

    R = CrossRobot(r, Coords(0, 0), true, dx, dy)
    back_path = BackPath(R)
    marks!(R)
    BackPath(r)
    back!(R, back_path)
end