include("D:\\Data\\Coding\\Julia\\mirea-progs\\lib\\librobot.jl")

function moveToWall!(r::Robot)
    c = 0
    while !isborder(r, HorizonSide(1))
        putmarker!(r)
        move!(r, HorizonSide(1))
        c+=1
    end
    putmarker!(r)
    return c
end

function moveAndPut!(r)
    c = moveToWall!(r)
    while c > 0
        if isborder(r, HorizonSide(0))
            break
        end
        move!(r, HorizonSide(0))
        for i in 1:c-1
            move!(r, HorizonSide(3))
        end
        c = moveToWall!(r)
    end
end

function lestniza!(r::Robot)
    sides = moveAndReturnDirections!(r)
    moveAndPut!(r)
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
end