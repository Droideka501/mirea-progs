include("..\\libs\\FunctionsRobot.jl")

function moveToWall!(r::Robot)
    c = 0
    while !isborder(r, West)
        putmarker!(r)
        move!(r, West)
        c+=1
    end
    putmarker!(r)
    return c
end

function moveAndPuting!(r)
    c = moveToWall!(r)
    while c > 0
        if isborder(r, Nord)
            break
        end
        move!(r, Nord)
        for i in 1:c-1
            move!(r, Ost)
        end
        c = moveToWall!(r)
    end
end

function lestniza!(r::Robot)
    sides = moveAndReturnDirections!(r)
    moveAndPuting!(r)
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
end