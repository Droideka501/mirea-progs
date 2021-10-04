#include("D:\\Data\\Coding\\Julia\\mirea-progs\\fordebug.jl")
include("D:\\Data\\Coding\\Julia\\mirea-progs\\lib\\librobot.jl")


function zakrasit!(r::Robot)
    sides = moveAndReturnDirections!(r)
    marksArea!(r)
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
end



