function search_and_score!(r::Robot)
    score = 0
    count = 0
    side = Ost
    while true
        while !isborder(r, side)
            if ismarker(r)
                score+=temperature(r)
                count+=1
            end
            move!(r, side)
        end
        if ismarker(r)
            score+=temperature(r)
            count+=1
        end
        if isborder(r, Sud)
            break
        end
        move!(r, Sud)
        side = reversSide(side)
    end
    println("Average score: ", score/count, "\nQuantity: ", count)
end