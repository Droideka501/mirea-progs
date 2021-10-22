include("..\\libs\\FunctionsRobot.jl")


function moveAroundAndPut!(r::Robot)#, side::HorizonSide)
    for side in instances(HorizonSide)
        putmarker!(r)
        marksLine!(r, side)
    end
end


function perimetr!(r::Robot)
    sides = moveAndReturnDirections!(r)
    moveAroundAndPut!(r)
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
end
