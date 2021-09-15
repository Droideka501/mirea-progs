function move_to_beginplace!(r::Robot)
    c = 0
    while !isborder(r, HorizonSide(0))
        move!(r, HorizonSide(0))
        c+=1
    end
    return c
end