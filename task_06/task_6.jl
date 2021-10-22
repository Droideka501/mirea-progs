include("..\\libs\\FunctionsRobot.jl")

function perimetrAroundObject!(r::Robot, side)
    check = false

    while !check
        if ismarker(r)
            break
        end
        while isborder(r, nextSideConterclockwise(side))
            putmarker!(r)
            move!(r, side)
        end
        putmarker!(r)
        side = nextSideConterclockwise(side)
        move!(r, side)
    end
end

function perimetr_of_object!(r::Robot)
    sides = moveAndReturnDirections!(r)
    perimetrAroundObject!(r, searchObject!(r))
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
end