function move_to_startplace!(r::Robot)
    x = 0
    y = 0
    while !(isborder(r, HorizonSide(0)) && isborder(r, HorizonSide(1)))
        while !isborder(r, HorizonSide(0))
            move!(r, HorizonSide(0))
            y+=1
        end
        while !isborder(r, HorizonSide(1))
            move!(r, HorizonSide(1))
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
                if isborder(r, HorizonSide(3))
                    move!(r, HorizonSide(2))
                    y-=1
                end
                if !isborder(r, HorizonSide(3))
                    move!(r, HorizonSide(3))
                    x -= 1
                end
            elseif x < 0
                if isborder(r, HorizonSide(1))
                    move!(r, HorizonSide(0))
                    y-=1
                end
                if !isborder(r, HorizonSide(1))
                    move!(r, HorizonSide(1))
                    x += 1
                end
            end
        end
        while y != 0
            if y > 0
                if isborder(r, HorizonSide(2))
                    move!(r, HorizonSide(3))
                    x-=1
                end
                if !isborder(r, HorizonSide(2))
                    move!(r, HorizonSide(2))
                    y -= 1
                end
            elseif y < 0
                if isborder(r, HorizonSide(0))
                    move!(r, HorizonSide(3))
                    x-=1
                end
                if !isborder(r, HorizonSide(0))
                    move!(r, HorizonSide(0))
                    y += 1
                end
            end
        end
    end
end

function move_rigth!(r::Robot, N)
    n = N
    for i in 1:n
        if isborder(r, HorizonSide(3))
            putmarker!(r)
            if !isborder(r, HorizonSide(2))
                move!(r, HorizonSide(2))
            end
            return i
        end
        putmarker!(r)
        move!(r, HorizonSide(3))
    end
    if isborder(r, HorizonSide(2))
        putmarker!(r)
        return n
    end
    putmarker!(r)
    move!(r, HorizonSide(2))
    return n
end

function move_left!(r::Robot, N)
    n = N
    for i in 1:n
        if isborder(r, HorizonSide(1))
            putmarker!(r)
            if !isborder(r, HorizonSide(2))
                move!(r, HorizonSide(2))
            end
            return i
        end
        putmarker!(r)
        move!(r, HorizonSide(1))
        
    end
    if isborder(r, HorizonSide(2))
        putmarker!(r)
        return n
    end
    putmarker!(r)
    move!(r, HorizonSide(2))
    return n
end

function kletka!(r::Robot, N)
    n = N
    c = n-1 
    for i in 1:n
        if n%2 != 0
            c = move_rigth!(r, c)
        else
            c = move_left!(r, c)
        end

        if ismarker(r)
            break
        end
    end
end

function move_to_another!(r::Robot, N)
    n = N
    while n != 0
        if isborder(r, HorizonSide(3))
            break
        end
        if ismarker(r)
            move!(r, HorizonSide(3))
        end
        if !ismarker(r) && !isborder(r, HorizonSide(3))
            move!(r, HorizonSide(3))
            n-=1
        end
    end
end

function naprotiv!(r::Robot, N)
    n = N
    x, y = move_to_startplace!(r)
    while !isborder(r, HorizonSide(3)) || !isborder(r, HorizonSide(2))
        if !isborder(r, HorizonSide(3))
            kletka!(r, n)
            move_to_another!(r, n)
        end
        while !isborder(r, HorizonSide(1))
            move!(r, HorizonSide(1))
        end
    end

    #move_to_startplace!(r)
    #move_to_beginplace!(r, x, y)
end

        

