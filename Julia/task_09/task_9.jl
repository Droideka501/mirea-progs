function moveAndSearch!(r::Robot, side::HorizonSide, num::Integer)
    for _ in 1:num
        if ismarker(r)
            return true
            break
        end
        move!(r, side)
    end
    return false
end


function search_marker!(r::Robot)
    side = West
    counter = 1
    checker = false
    
    while !ismarker(r)
        for _ in 1:2
            checker = moveAndSearch!(r, side, counter)
            if checker
                break
            end
            side = nextSideConterclockwise(side)
        end
        counter+=1
    end
end
