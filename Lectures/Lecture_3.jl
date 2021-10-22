using HorizonSideRobots

# num_markers = 0

function count_markers!(r::Robot)
    #УТВ: Робот - в юго-западном углу
    side = Ost

    num_markers = nextrow!(r,side)
    #num_markers=0 - так хуже было бы
    #num_markers = nextrow!(r, side, num_markers)
    while isborder(r,Nord)==false
        move!(r,Nord)
        side = inverse(side)
        num_markers += nextrow!(r,side)
        #num_markers = nextrow!(r,side,num_markers)
    end

end

"""
    nextrow!(r,side)

-- перемещает робота до упора в заданном направлении и ВОЗВРАЩАЕТ число встретившихся на пути  
маркеров
"""
function nextrow!(r,side)
    #movements!(r,side) # перемещает Робота в заданном направлении до упора (писали мы такую функцию)
    #num_markers = 0
    if ismarker(r)
        num_markers += 1
    end
    while !isborder(r,side)
        move!(r,side)
        if ismarker(r)
            num_markers += 1
        end    
    end
    return num_markers
end

# r - ccылка на созданный объект типа Robot
# r = Robot(...)

num_markers = count_markers!(r)
#println("Ответ: ", num_markers)