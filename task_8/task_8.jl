function search_out!(r::Robot)
    side = 3
    counter = 1

    while true
        if !isborder(r, HorizonSide(0))
            break
        end
        for _ in 1:counter
            move!(r, HorizonSide(side))
        end
        side = (side+2)%4
        counter += 1
    end
end