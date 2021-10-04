include("D:\\Data\\Coding\\Julia\\mirea-progs\\lib\\librobot.jl")

function move_rigth!(r::Robot, N)
    n = N
    for i in 1:n
        if isborder(r, HorizonSide(3))
            putmarker!(r)
            if !isborder(r, HorizonSide(2))
                move!(r, HorizonSide(2))
            end
            return i-1, true
        end
        putmarker!(r)
        move!(r, HorizonSide(3))
    end
    if isborder(r, HorizonSide(2))
        putmarker!(r)
        return n, true
    end
    putmarker!(r)
    move!(r, HorizonSide(2))
    return n, false
end

function move_left!(r::Robot, N)
    n = N
    for i in 1:n
        if isborder(r, HorizonSide(1))
            putmarker!(r)
            if !isborder(r, HorizonSide(2))
                move!(r, HorizonSide(2))
            end
            return i-1, true
        end
        putmarker!(r)
        move!(r, HorizonSide(1))
        
    end
    if isborder(r, HorizonSide(2))
        putmarker!(r)
        return n, true
    end
    putmarker!(r)
    move!(r, HorizonSide(2))
    return n, false
end

function kletka!(r::Robot, N)
    n = N
    c = n-1 
    check = false
    for i in 1:n
        if i%2 != 0
            c, check = move_rigth!(r, c)
        else
            c, check = move_left!(r, c)
        end

        if ismarker(r)
            break
        end
    end
    return check
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
    

end

        

