function search_and_score!(r::Robot)
    score = 0
    count = 0
    side = 3
    while true
        while !isborder(r, HorizonSide(side))
            if ismarker(r)
                score+=temperature(r)
                count+=1
            end
            move!(r, HorizonSide(side))
        end
        if ismarker(r)
            score+=temperature(r)
            count+=1
        end
        if isborder(r, HorizonSide(2))
            break
        end
        move!(r, HorizonSide(2))
        #println(side)
        side = (side+2) % 4
    end
    println(score/count, " ", count)
end