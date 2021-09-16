function move_to_startplace!(r::Robot)
    x = 0
    y = 0
    while !isborder(r, HorizonSide(0))
        move!(r, HorizonSide(0))
        y+=1
    end
    while !isborder(r, HorizonSide(1))
        move!(r, HorizonSide(1))
        x+=1
    end
    return (x, y)
end

function move_rigth!(r::Robot)
    while !isborder(r, HorizonSide(3))
        putmarker!(r)
        move!(r, HorizonSide(3))
    end
    if !isborder(r, HorizonSide(2))
        putmarker!(r)
        move!(r, HorizonSide(2))
    end
end

function move_left!(r::Robot)
    while !isborder(r, HorizonSide(1))
        putmarker!(r)
        move!(r, HorizonSide(1))
    end
    if !isborder(r, HorizonSide(2))
        putmarker!(r)
        move!(r, HorizonSide(2))
    end
end

function move_to_beginplace!(r::Robot, x, y)
    for i in 0:x
        move!(r, HorizonSide(3))
    end
    for j in 0:y
        move!(r, HorizonSide(2))
    end
end

function zakrasit!(r::Robot)
    x, y = move_to_startplace!(r)
    while !isborder(r, HorizonSide(3)) || !isborder(r, HorizonSide(1))
        move_rigth!(r)
        move_left!(r)

        if ismarker(r)
            break
        end
    end
    #a, b = move_to_startplace!(r)
    move_to_beginplace!(r, x, y)
end



