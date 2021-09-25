
function move_to_border!(r::Robot)
    c = 0
    while !isborder(r, HorizonSide(0))
        move!(r, HorizonSide(0))
        c+=1
    end
    return c
end

function move_backward!(r::Robot, c)
    for i in 1:c
        move!(r, HorizonSide(2))
    end
end

function move_around!(r::Robot)
    i = 1
    while true
        i = i%4
        if ismarker(r)
            break
        end
        while !isborder(r, HorizonSide(i%4))
            if ismarker(r)
                break
            end
            putmarker!(r)
            move!(r, HorizonSide(i%4))
        end
        i += 1
    end
end


function perimetr!(r::Robot)
    count = move_to_border!(r)
    move_around!(r)
    move_backward!(r, count)
end
