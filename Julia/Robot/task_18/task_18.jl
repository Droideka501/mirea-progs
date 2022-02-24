include("..\\libs\\FunctionsRobot.jl")


function putmarkerInCorner!(r::Robot)
    for side in instances(HorizonSide)
        putmarker!(r)
        while !isborder(r, side)
            move!(r, side)
        end
    end
end


function uglyWithPartitions!(r::Robot)
    sides = moveAndReturnDirections!(r)
    putmarkerInCorner!(r)
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
    
end

