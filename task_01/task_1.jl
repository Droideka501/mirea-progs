include("D:\\Data\\Coding\\Julia\\mirea-progs\\lib\\librobot.jl")


function moveAndPut!(r::Robot, side::HorizonSide)
    while !isborder(r, side)
        move!(r, side)
        putmarker!(r)
    end
end


function moveBackwardAlongMarkers!(r::Robot, side::HorizonSide)
    while ismarker(r)
        move!(r, reversSide(side))
    end
end


function krest!(r::Robot)
    for side in instances(HorizonSide)
        moveAndPut!(r, side)
        moveBackwardAlongMarkers!(r, side)
        if side == Ost
            putmarker!(r)
            break
        end
    end    
end  
