include("D:\\Data\\Coding\\Julia\\mirea-progs\\lib\\librobot.jl")


function moveAroundAndPut!(r::Robot)#, side::HorizonSide)
    for side in instances(HorizonSide)
        putmarker!(r)
        moveAndPut!(r, side)
    end
end


function perimetr!(r::Robot)
    sides = moveAndReturnDirections!(r)
    moveAroundAndPut!(r)
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
end
