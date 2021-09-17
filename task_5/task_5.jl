function move_to_startplace!(r::Robot)
    x = 0
    y = 0
    while !isborder(r, HorizonSide(2))
        move!(r, HorizonSide(2))
        y+=1
    end
    while !isborder(r, HorizonSide(3))
        move!(r, HorizonSide(3))
        x+=1
    end
    return (x, y)
end

function move_to_beginplace!(r::Robot, x, y)
    for i in 0:x-1
        move!(r, HorizonSide(1))
    end
    for j in 0:y-1
        move!(r, HorizonSide(0))
    end
end

function move_and_put!(r::Robot)
    for i in 0:3
        while !isborder(r, HorizonSide(i))
            move!(r, HorizonSide(i))
        end
        putmarker!(r)
    end
end

function ugly!(r::Robot)
    x, y = move_to_startplace!(r)
    move_and_put!(r)
    move_to_startplace!(r)
    move_to_beginplace!(r, x, y)
end

