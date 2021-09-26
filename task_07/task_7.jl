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

function chess_markers!(r::Robot, X, Y)
    x = X
    y = Y
    counter = 0
    
    while true
        if (x+y)%2 == 0
            while !isborder(r, HorizonSide(1))
                if counter % 2 == 0
                    putmarker!(r)
                end
                move!(r, HorizonSide(1))
                counter+=1
            end
            if counter % 2 == 0
                putmarker!(r)
            end
            if isborder(r, HorizonSide(0))
                break
            end
            move!(r, HorizonSide(0))
            while !isborder(r, HorizonSide(3))
                move!(r, HorizonSide(3))
            end
            y-=1
            counter = 0
        end
        if (x+y)%2 != 0
            while !isborder(r, HorizonSide(1))
                move!(r, HorizonSide(1))
                if counter % 2 == 0
                    putmarker!(r)
                end
                counter+=1
            end
            if isborder(r, HorizonSide(0))
                break
            end
            move!(r, HorizonSide(0))
            while !isborder(r, HorizonSide(3))
                move!(r, HorizonSide(3))
            end
            y-=1
            counter = 0
        end
    end
end

function shess_desk!(r)
    x, y = move_to_startplace!(r)
    chess_markers!(r, x, y)
    move_to_startplace!(r)
    move_to_beginplace!(r, x, y)
end