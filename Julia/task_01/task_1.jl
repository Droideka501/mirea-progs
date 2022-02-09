include("..\\libs\\FunctionsRobot.jl")


function krest!(r::Robot)
    for side in instances(HorizonSide)
        if isborder(r, side)
            continue
        end
        move!(r, side)
        marksLine!(r, side)
        moveWhileMarker!(r, reversSide(side))
    end
    putmarker!(r)
end  
