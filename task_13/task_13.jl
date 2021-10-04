function kosoykrest!(r::Robot)
    for side in instances(HorizonSide)
        while !isborder(r, side) && !isborder(r, nextSideConterclockwise(side))
            move!(r, side)
            move!(r, nextSideConterclockwise(side))
            putmarker!(r)
        end

        while ismarker(r)
            move!(r, reversSide(side))
            move!(r, nextSideConterclockwise(reversSide(side)))
        end
    end    
end  
