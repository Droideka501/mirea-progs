include("..\\libs\\FunctionsRobot.jl")

function putmarker!(robot::CoordsRobot)
    x, y = get_xy(get_coords(robot))
    if x - y <= 0
        putmarker!(get_robot(robot))
    end
end


function lestnizaWithPartitions!(r::Robot)
    back_path = BackPath(r)
    R = CoordsRobot(r)
    marks!(R)
    BackPath(R)
    back!(R, back_path)
end