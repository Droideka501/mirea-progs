include("..\\libs\\FunctionsRobot.jl")


function putmarkersOpposite!(r::Robot, sides::Vector{HorizonSide})
    arr = deepcopy(sides)
    x, y = countingCoordinate(arr)
    sides = [HorizonSide(i) for i in 3:-1:0] #reversed enumerated HorizonSide

    for _ in 1:2
        for coord in (y, x)
            side = pop!(sides) 
            moves!(r, side, coord)
            putmarker!(r)
            n = movesAndCounting!(r, side)
            if coord == x
                x = n
            else
                y = n
            end
        end
    end
end


function naprotiv!(r::Robot)
    sides = moveAndReturnDirections!(r)
    putmarkersOpposite!(r, sides)
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
end

        

