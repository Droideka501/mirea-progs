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

function search_object!(r::Robot)
    x = 0
    y = 0
    i = 2
    check = false
    while !isborder(r, HorizonSide(0))
        move!(r, HorizonSide(0))
        y+=1
    end
    while !isborder(r, HorizonSide(1))
        move!(r, HorizonSide(1))
        x+=1
    end
    while !check
        if i % 2 == 0
            for _ in 1:(y-1)
                move!(r, HorizonSide(i))
                if isborder(r, HorizonSide((i+1)%4)) || isborder(r, HorizonSide(i))
                    check = true
                    return i
                end
            end
            y-=1
        end
        if i % 2 != 0
            for _ in 1:(x-1)
                move!(r, HorizonSide(i))
                if isborder(r, HorizonSide((i+1)%4)) || isborder(r, HorizonSide(i))
                    check = true
                    return i
                end
            end
            x-=1
        end
        i = (i + 1)%4
    end
    return ErrorException
end

function perimetr_around_object!(r::Robot, side)
    check = false

    while !check
        if ismarker(r)
            break
        end
        while isborder(r, HorizonSide((side+1)%4))
            putmarker!(r)
            move!(r, HorizonSide(side))
        end
        putmarker!(r)
        side = (side+1)%4
        move!(r, HorizonSide(side))
    end
end

function perimetr_of_object!(r::Robot)
    x, y = move_to_startplace!(r)
    side = search_object!(r)
    perimetr_around_object!(r, side)
    move_to_startplace!(r)
    move_to_beginplace!(r, x, y)
end