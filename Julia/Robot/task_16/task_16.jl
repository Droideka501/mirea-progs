include("..\\libs\\FunctionsRobot.jl")


function zakrasitWithPartitions!(r::Robot)
    sides = moveAndReturnDirections!(r)
    marks!(r)
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
end



