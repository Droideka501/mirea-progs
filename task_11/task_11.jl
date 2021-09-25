function move_to_startplace!(r::Robot)
    x = 0
    y = 0
    while !(isborder(r, HorizonSide(2)) && isborder(r, HorizonSide(3)))
        while !isborder(r, HorizonSide(2))
            move!(r, HorizonSide(2))
            y+=1
        end
        while !isborder(r, HorizonSide(3))
            move!(r, HorizonSide(3))
            x+=1
        end
    end
    return (x, y)
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
                move!(r, HorizonSide(1))
                x -= 1
            elseif x < 0
                
                move!(r, HorizonSide(3))
                x += 1
            end
        end
        while y != 0
            if isborder(r, HorizonSide(0))
                move!(r, HorizonSide(1))
                x-=1
            elseif y > 0
                move!(r, HorizonSide(0))
                y -= 1
            elseif y < 0
                move!(r, HorizonSide(2))
                y += 1
            end
        end
    end
end

function move_and_put!(r::Robot, X, Y)
    x = X
    y = Y
    
    for side in 0:3
        while !isborder(r, HorizonSide(side))
            while y > 0
                move!(r, HorizonSide(side))
                y-=1
            if y == 0
                putmarker!(r)
            end
            y-=1
        
    end
end

function naprotiv!(r::Robot)
    x, y = move_to_startplace!(r)
    move_and_put!(r, x, y)
    move_to_startplace!(r)
    move_to_beginplace!(r, x, y)
end

        

