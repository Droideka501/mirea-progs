include("D:\\Data\\Coding\\Julia\\mirea-progs\\lib\\librobot.jl")


function moveAndPut!(r::Robot)
    for i in 0:3
        putmarker!(r)
        while !isborder(r, HorizonSide(i))
            move!(r, HorizonSide(i))
            
        end
    end
end


function ugly!(r::Robot)
    sides = moveAndReturnDirections!(r)
    moveAndPut!(r)
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
    
end

