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

function move_to_beginplace!(r::Robot, X, Y)
    x = X
    y = Y
    
    while x != 0 || y != 0
        while x != 0 
            if x > 0
                if isborder(r, HorizonSide(1))
                    move!(r, HorizonSide(0))
                    y-=1
                end
                if !isborder(r, HorizonSide(1))
                    move!(r, HorizonSide(1))
                    x -= 1
                end
            elseif x < 0
                if isborder(r, HorizonSide(3))
                    move!(r, HorizonSide(0))
                    y-=1
                end
                if !isborder(r, HorizonSide(3))
                    move!(r, HorizonSide(3))
                    x += 1
                end
            end
        end
        while y != 0
            
            if y > 0
                if isborder(r, HorizonSide(0))
                    move!(r, HorizonSide(1))
                    x-=1
                end
                if !isborder(r, HorizonSide(0))
                    move!(r, HorizonSide(0))
                    y -= 1
                end
            elseif y < 0
                if isborder(r, HorizonSide(2))
                    move!(r, HorizonSide(1))
                    x-=1
                end
                if !isborder(r, HorizonSide(2))
                    move!(r, HorizonSide(2))
                    y += 1
                end
            end
        end
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
    move_to_startplace!(r)
    move_to_beginplace!(r, x, y)
end



