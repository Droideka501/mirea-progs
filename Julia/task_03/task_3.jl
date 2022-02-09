include("..\\libs\\FunctionsRobot.jl")


function zakrasit!(r::Robot)
    sides = moveAndReturnDirections!(r)
    marksArea!(r)
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
end



