include("D:\\Data\\Coding\\Julia\\mirea-progs\\lib\\librobot.jl")


function krest!(r::Robot)
    for side in instances(HorizonSide)
        moveAndPut!(r, side)
        moveWhileMarker!(r, reversSide(side))
    end
    putmarker!(r)
end  
