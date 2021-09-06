#using HorizonSideRobots

function krest!(r::Robot)
    dic = [Nord, Ost, Sud, West]
    
    for i in 0:3
        #c = i
        while !isborder(r, HorizonSide(i))
            move!(r, HorizonSide(i))
            putmarker!(r)
        end
        while ismarker(r)
            move!(r, HorizonSide((i+2)%4))
        end
        if i == 3
            putmarker!(r)
            break
        end
    end    
end  
#krest!(r)