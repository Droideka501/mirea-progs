include("D:\\Data\\Coding\\Julia\\mirea-progs\\lib\\librobot.jl")


function moveToAnother!(r::Robot, N)
    #for side in (Ost, West)
        moveWhileMarker!(r, Nord)
        moves!(r, Ost, N*2)
    #end
end


function modifyChess!(r::Robot, N::Integer)
    sides = moveAndReturnDirections!(r, West, Nord)
    marksArea!(r, N, Ost, Sud)
    move!(r, Nord)
    moveToAnother!(r, N)
    marksArea!(r, N, Ost, Sud)
    moves!(r, West, N)
    marksArea!(r, N, Ost, Sud)
    
    #moveToStartplace!(r, West, Nord)
    #moveToBeginplace!(r, sides)
end

        

