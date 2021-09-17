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

function move_to_wall!(r::Robot)
    c = 0
    while !isborder(r, HorizonSide(1))
        putmarker!(r)
        move!(r, HorizonSide(1))
        c+=1
    end
    putmarker!(r)
    return c
end

function lestniza!(r::Robot)
    x, y = move_to_startplace!(r)
    c = move_to_wall!(r)
    while c > 0
        if isborder(r, HorizonSide(0))
            break
        end
        move!(r, HorizonSide(0))
        for i in 1:c-1
            move!(r, HorizonSide(3))
        end
        c = move_to_wall!(r)
    end
    move_to_startplace!(r)
    move_to_beginplace!(r, x, y)
    
end